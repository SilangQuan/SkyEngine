#include "Core/Scene.h"
#include "Core/Camera.h"
#include "Core/GameObject.h"
#include "Render/ShaderProgram.h"

Scene::Scene() : /*resourceManager(),*/ defaultCamera(new Camera), activeCamera(0)
{
	rootObject = new GameObject();
}

void Scene::Initialize()
{
	//defaultCamera->setAspectRatio(getGame()->getRenderer()->getAspectRatio());
	if (activeCamera == 0)
	{
		activeCamera = defaultCamera;
	}

	this->Start();
}

void Scene::Start()
{
	//Start the root object (the root object will start all of its children)
	this->GetRoot()->Start();
}

void Scene::Update()
{
	//cout << "Scene Update!" << endl;

	//Update the root object (the root object will update all of its children)
	this->GetRoot()->Update();

	//Update the view and projection matrices with the active camera
	/*ShaderProgram* currentShader = Rendering::getCurrentShader();
	if (currentShader != 0)
	{
		if (currentShader->HasUniform("view"))
		{
			currentShader->SetUniform("view", activeCamera->GetViewMatrix());
		}
		if (currentShader->HasUniform("projection"))
		{
			currentShader->SetUniform("projection", activeCamera->GetProjectionMatrix());
		}
		if (currentShader->HasUniform("viewProjection"))
		{
			currentShader->SetUniform("viewProjection", activeCamera->GetViewMatrix() * activeCamera->GetProjectionMatrix());
		}
	}*/
}

GameObject* Scene::GetRoot()
{
	return rootObject;
}

void Scene::AddGameObject(GameObject* gameObject)
{
	rootObject->AddChild(gameObject);
}

/*
ResourceManager* Scene::getResourceManager()
{
	return &resourceManager;
}*/

Camera* Scene::GetActiveCamera()
{
	return activeCamera;
}

Camera* Scene::GetDefaultCamera()
{
	return defaultCamera;
}

void Scene::SetActiveCamera(Camera* camera)
{
	activeCamera = camera;
}

void Scene::Shutdown()
{
	//resourceManager.freeAllResources();
	delete defaultCamera;
	delete rootObject;
}

Scene::~Scene()
{
	this->Shutdown();
}