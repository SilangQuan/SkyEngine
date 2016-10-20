#include "../include/Renderer.h"
#include "../../SkyEngine/include/SkyEngine.h"
#include "../../SkyEngine/include/Render/RenderContext.h"
#include "../include/application.h"
#include "../include/Time.h"


Renderer::Renderer(Application * _parent)
{
	parent = _parent;
	engine = NULL;
	renderContext = new RenderContext();
}

Renderer::~Renderer()
{

}

bool Renderer::Initialize(const struct CreationFlags &creationFlags)
{
	glContext = SDL_GL_CreateContext(parent->GetWindow()->GetSDLWindow());
	ResizeGL(creationFlags.width, creationFlags.height);
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	else cout << "GLEW init successful!" << endl;
	
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(0);

	qDebug() << "----------Renderer Initialize----------";

	/* Enable smooth shading */
	glShadeModel(GL_SMOOTH);
	/* Set the background black */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/* Depth buffer setup */
	glClearDepth(1.0f);
	/* Enables Depth Testing */
	glEnable(GL_DEPTH_TEST);
	/* The Type Of Depth Test To Do */
	glDepthFunc(GL_LEQUAL);
	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Init character
	TTF_Init();
	font = TTF_OpenFont("../../Assets/consola.ttf", 24);

	SDL_Color color = { 255, 0, 0 };
	SDL_Surface *face = NULL;
	//14 is a magic number...
	for (GLubyte c = 14; c < 128; c++)
	{
		char tmpChar = /*'a' +*/ c;
		string tmp(1,tmpChar);

		face = TTF_RenderText_Blended(font, tmp.c_str(), color);

		int mode;
		if (face->format->BytesPerPixel == 3) { // RGB 24bit
			mode = GL_RGB;
		}
		else if (face->format->BytesPerPixel == 4) { // RGBA 32bit
			mode = GL_RGBA;
		}
		else {
			SDL_FreeSurface(face);
			return false;
		}

		GLuint texture = 0;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, mode, face->w, face->h, 0, mode, GL_UNSIGNED_BYTE, face->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int minx, maxx, miny, maxy, advance;
		if (TTF_GlyphMetrics(font, *(tmp.c_str()), &minx, &maxx, &miny, &maxy, &advance) == -1)
		{
			printf("%s\n", TTF_GetError());
		}

		Character character = {
			texture,
			Vector2(face->w, face->h),
			Vector2(minx, maxy),
			advance
		};
		Characters.insert(std::pair<GLchar, Character>(tmpChar, character));
	}

	characterShader = new ShaderProgram("../../Assets/shader/character.vert", "../../Assets/shader/character.frag");
	Matrix4x4 projection = Transform::OrthoFrustum(0.0f, static_cast<GLfloat>(creationFlags.width), 0.0f, static_cast<GLfloat>(creationFlags.height), -1000, 1000);
	characterShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(characterShader->GetProgramID(), "projection"), 1, GL_FALSE, &projection[0]);

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &characterVAO);
	glGenBuffers(1, &characterVBO);
	glBindVertexArray(characterVAO);
	glBindBuffer(GL_ARRAY_BUFFER, characterVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return true;
}


void Renderer :: ResizeGL(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	//Reset View
	glViewport(0, 0, (GLint)width, (GLint)height);
	//Choose the Matrix mode
	glMatrixMode(GL_PROJECTION);
	//reset projection
	glLoadIdentity();
	//set perspection
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 1000.0);
	//choose Matrix mode
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
}


Application* Renderer::GetParent()
{
	return parent;
}

void Renderer::Render(Scene* scene, Camera* camera)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//parent->GetWindow()->RenderText(255, 0, 0, 0, 0, 0, "Fuck");

	if(scene != NULL)
	{
		renderContext->projectionMatrix = camera->projectionMaxtrix;
		renderContext->viewMatrix = camera->GetViewMatrix();
		renderContext->viewProjectionMatrix = camera->GetViewMatrix() * camera->GetProjectionMatrix();
		renderContext->viewPos = camera->transform.position;
		RenderGameObject(scene->GetRoot(), renderContext);
	}
	glClear(GL_DEPTH_BUFFER_BIT);
	std::ostringstream ss;
	ss << "Fps: ";
	float tmp = parent->GetFPS();
	ss << tmp;
	//qDebug() << ss.str();
	RenderText(ss.str(), - 0.5f * parent->GetWindowWidth(), 0.5f * parent->GetWindowHeight() - 100, 1, Color(1, 1, 1, 1));
}

void Renderer::RenderGameObject(GameObject* gameObject, RenderContext* renderContext)
{
	//Get a RenderingComponent from gameObject and invoke render() on it
	MeshRenderer* rc = gameObject->GetComponent<MeshRenderer>();

	if (rc != 0)
	{
		rc->Render(renderContext);
	}

	//For all of gameObject's children, call render() on them
	uint32 numChildren = gameObject->GetNumChildren();
	for (uint32 i = 0; i < numChildren; i++)
	{
		RenderGameObject(gameObject->GetChild(i), renderContext);
	}
}

void Renderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, Color color)
{
	characterShader->Use();
	glUniform3f(glGetUniformLocation(characterShader->GetProgramID(), "textColor"), color.r, color.g, color.b);
	//glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.r, color.g, color.b);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(characterVAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		//GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		GLfloat ypos = y;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// VBO
		GLfloat vertices[6][4] = {
			{ xpos,     ypos,   0.0, 1.0 },
			{ xpos,     ypos + h,       0.0, 0.0 },
			{ xpos + w, ypos + h,       1.0, 0.0 },

			{ xpos,     ypos,   0.0, 1.0 },
			{ xpos + w, ypos + h,       1.0, 0.0 },
			{ xpos + w, ypos,   1.0, 1.0 }
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, characterVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += ch.Advance  * scale; 
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

