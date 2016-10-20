#pragma comment( lib, "..\\..\\Lib\\Win32\\Debug\\AppFramework.lib" )

#include "../include/App.h"
#include "../../SkyEngine/include/SkyEngine.h"

bool App::CreateWorld()
{
	mixValue = 0.5f;
	glDisable(GL_CULL_FACE);

	lampProgram = new ShaderProgram("./assets/lamp.vert", "./assets/lamp.frag");
	lightingProgram = new ShaderProgram("./assets/lighting.vert", "./assets/lighting.frag");

	//diffuseMap = new Texture(0, "./assets/crate.jpg");
	//specularMap = new Texture(1, "./assets/crate_specular.jpg");

	diffuseMap = ResourceManager::GetInstance()->TryGetResource<Texture>("./assets/crate.jpg");
	specularMap = ResourceManager::GetInstance()->TryGetResource<Texture>("./assets/crate_specular.jpg");

	scene = new Scene();
	box = new GameObject();
	lightObj = new GameObject();

	light = new Light(kLightDirectional);
	light->direction = Vector3(-0.2f, -1.0f, -0.3f);
	light->ambient = Vector3(0.05f, 0.05f, 0.05f);
	light->diffuse = Vector3(0.4f, 0.4f, 0.4f);
	light->specular = Vector3(0.5f, 0.5f, 0.5f);
	light->AddToManager();
	delete(light);

	light = new Light(kLightPoint);
	light->position = Vector3(7.0f, 2.0f, 2.0f);
	light->ambient = Vector3(0.05f, 0.05f, 0.05f);
	light->diffuse = Vector3(0.0f, 0.8f, 0.0f);
	light->specular = Vector3(0.5f, 0.5f, 0.5f);
	light->constant = 1.0f;
	light->linear = 0.09f;
	light->quadratic = 0.032;
	light->AddToManager();
	delete(light);

	light = new Light(kLightPoint);
	light->position = Vector3(-4.0f, 2.0f, 2.0f);
	light->ambient = Vector3(0.05f, 0.05f, 0.05f);
	light->diffuse = Vector3(0.8f, 0.0f, 1.0f);
	light->specular = Vector3(0.2f, 0.2f, 0.2f);
	light->constant = 1.0f;
	light->linear = 0.09f;
	light->quadratic = 0.032;
	light->AddToManager();
	delete(light);

	light = new Light(kLightPoint);
	light->position = Vector3(12.3f, -3.3f, -4.0f);
	light->ambient = Vector3(0.05f, 0.05f, 0.05f);
	light->diffuse = Vector3(0.0f, 0.0f, 1.8f);
	light->specular = Vector3(0.5f, 0.5f, 0.5f);
	light->constant = 1.0f;
	light->linear = 0.09f;
	light->quadratic = 0.032;
	light->AddToManager();
	delete(light);

	light = new Light(kLightPoint);
	light->position = Vector3(-4.0f, 2.0f, 2.0f);
	light->ambient = Vector3(0.05f, 0.05f, 0.05f);
	light->diffuse = Vector3(1.8f, 0.0f, 0.0f);
	light->specular = Vector3(0.5f, 0.5f, 0.5f);
	light->constant = 1.0f;
	light->linear = 0.09f;
	light->quadratic = 0.032;
	light->AddToManager();
	delete(light);

	light = new Light(kLightSpot);
	light->position = Vector3(4.0f, -4.0f, -3.0f);
	light->ambient = Vector3(0.0f, 0.0f, 0.0f);
	light->diffuse = Vector3(1.0f, 1.0f, 0.0f);
	light->specular = Vector3(1.0f, 1.0f, 1.0f);
	light->constant = 1.0f;
	light->linear = 0.09f;
	light->quadratic = 0.032;
	light->cutOff = Mathf::Cos(Mathf::Deg2Rad *10.0f);
	light->outerCutOff = Mathf::Cos(Mathf::Deg2Rad *10.0f);
	light->AddToManager();
	delete(light);

	boxMat = new Material(lightingProgram);
	boxMat->SetTextureVariable("material.diffuse", diffuseMap);
	boxMat->SetTextureVariable("material.specular", specularMap);
	boxMat->SetFloat("material.shininess", 32.0f);

	boxMat->SetDirectionLight(GetLightManager().GetDirectionLight());
	boxMat->SetPointLight(GetLightManager().GetPointLights());
	boxMat->SetSpotLight(GetLightManager().GetSpotLights());

	lampMat = new Material(lampProgram);
	lampMat->SetVector3("lampColor", Vector3(0.0f, 0.8f, 0.0f));
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat verticesData[] = {
		// Positions      // Normals     // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Vector2> uvs;
	int vertexLength = 36;
	for (int i = 0; i < vertexLength; i++)
	{
		vertices.push_back(Vector3(verticesData[8 * i + 0], verticesData[8 * i + 1], verticesData[8 * i + 2]));
		normals.push_back(Vector3(verticesData[8 * i + 3], verticesData[8 * i + 4], verticesData[8 * i + 5]));
		uvs.push_back(Vector2(verticesData[8 * i + 6], verticesData[8 * i + 7]));
	}

	boxMesh = new Mesh();
	
	vector<Color> colors;
	colors.push_back(Color(1.0f, 0.0f, 0.0f, 1.0f));
	colors.push_back(Color(0.0f, 1.0f, 0.0f, 1.0f));
	colors.push_back(Color(0.0f, 0.0f, 1.0f, 1.0f));
	colors.push_back(Color(1.0f, 1.0f, 0.0f, 1.0f));

	boxMesh->positions = vertices;
	boxMesh->colors = colors;
	boxMesh->uv = uvs;
	boxMesh->positions = vertices;
	boxMesh->normals = normals;
	//boxMesh->triangles = triangles;
	boxMesh->CreateBufferData();

	MeshRenderer* boxMeshRenderer = new MeshRenderer(boxMesh, boxMat);

	MeshRenderer* lampMeshRenderer = new MeshRenderer(boxMesh, lampMat);
	box->AddComponent(boxMeshRenderer);

	scene->AddGameObject(box);
	scene->AddGameObject(lightObj);

	boxes = new GameObject[10];

	for (int i = 0; i < 10; i++)
	{
		MeshRenderer* box2MeshRenderer = new MeshRenderer(boxMesh, boxMat);
		boxes[i].transform.Translate(Vector3(Random::Range(-5.0f, 5.0f), Random::Range(-5.0f, 5.0f), Random::Range(-5.0f, 5.0f)));
		boxes[i].transform.Scale(Random::Range(3.1f, 6.5f) * Vector3::one);
		boxes[i].transform.Rotate(Random::Range(0, 360), Random::Range(0, 360), Random::Range(0, 360));
		boxes[i].AddComponent(box2MeshRenderer);
		scene->AddGameObject(&boxes[i]);
	}

	lightObj->AddComponent(lampMeshRenderer);
	lightObj->GetTransform()->Translate(Vector3(7.0f, 2.0f, 2.0f));

	//camera = new Camera(Vector3(0, 0, -2.5f), Vector3::zero, Vector3::up);
	//camera->SetFrustrum(-1.778f, 1.778f, -1.0f, 1.0f, 1, 10, true);

	camera = new Camera(Vector3(0, 0, 1), Vector3::zero, Vector3::up);
	camera->SetFrustrum(-1.778f, 1.778f, -1.0f, 1.0f, 1, 10, true);

	scene->SetActiveCamera(camera);

	return true;
}

void  App::UpdateCamera()
{
	float moveSpeed = 40.0f;
	float move = Time::deltaTime * moveSpeed;
	float xoffset =  pInput->GetMouseDeltaX();
	float yoffset = pInput->GetMouseDeltaY();

	float sensitivity = 1;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	float currentYaw = camera->transform.rotation.EulerAngle().y;
	float currentPitch = camera->transform.rotation.EulerAngle().x;

	currentYaw += yoffset;
	currentPitch += xoffset;

	currentPitch = Mathf::Clamp(-89, 89, currentPitch);

	camera->transform.Rotate(yoffset, xoffset, 0);

	//camera->transform.rotation = Quaternion::Euler(-currentYaw, currentPitch, 0);

	if (pInput->GetKeyDown(KEY_W))
	{
		camera->transform.position += move * camera->transform.GetForward();
	}

	if (pInput->GetKeyDown(KEY_S))
	{
		camera->transform.position += -move * camera->transform.GetForward();
	}

	if (pInput->GetKeyDown(KEY_A))
	{
		camera->transform.position += -move * camera->transform.GetRight();
	}

	if (pInput->GetKeyDown(KEY_D))
	{
		camera->transform.position += move * camera->transform.GetRight();
	}

}

void App::RenderWorld()
{
	UpdateCamera();
	pRenderer->Render(scene, scene->GetActiveCamera());
	SDL_GL_SwapWindow(GetWindow()->GetSDLWindow());
}

void App::DestroyWorld()
{
	glDeleteVertexArrays(1, &boxVAO);
	glDeleteBuffers(1, &boxVBO);
}

void App::FrameMove()
{

}
