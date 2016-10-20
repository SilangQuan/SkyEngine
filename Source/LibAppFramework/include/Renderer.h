#pragma once
#pragma once
#include <stack>
#include <map>
#include "application.h"
#include "../../3rdParty/include/SDL/SDL_ttf.h"

class Application;
class SkyEngine;
class RenderContext;

struct Character {
	GLuint		TextureID;
	Vector2		Size;
	Vector2		Bearing;
	GLuint		Advance;    //Offset to advance to next glyph
};

class Renderer
{
public:
	Renderer(Application * parent);
	~Renderer();
	Application* GetParent();
	bool Initialize(const struct CreationFlags &creationFlags);
	void ResizeGL(int width, int height);
	void Render(Scene* scene, Camera* camera);

	void RenderGameObject(GameObject* gameObject, RenderContext* renderContext);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, Color color);

private:
	//result BindAndLink();
	Application* parent;
	SkyEngine* engine;
	SDL_GLContext glContext;
	TTF_Font *font;
	std::map<GLchar, Character> Characters;
	GLuint characterVAO, characterVBO;
	ShaderProgram *characterShader;
	RenderContext* renderContext;
};
