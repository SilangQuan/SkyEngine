#ifdef _DEBUG
#pragma comment( lib, "..\\..\\Lib\\Win32\\Debug\\AppFramework.lib" )
#else
#pragma comment( lib, "..\\..\\Lib\\Win32\\Release\\AppFramework.lib" )
#endif


#include "../include/App.h"
#include "../../SkyEngine/include/SkyEngine.h"

bool App::CreateWorld()
{
	camera = new Camera(Vector3(0, 0, -100), Vector3::zero, Vector3::up);
	camera->SetFrustrum(-1.778f, 1.778f, -1.0f, 1.0f, 1, 2000, true);


	//bunny = new Model("./assets/Model/Bonny/bunny.obj", true);
	//bunny = new Model("./assets/Model/sponza/sponza3.obj", true);
	bunny = new Model("./assets/Model/sponza2/sponza.obj", true);
	//bunny = new Model("./assets/Model/rock/rock.obj", true);
	bunny->CreateBufferData();

	sponza = new GameObject();
	vector<Mesh>* meshes = bunny->GetMeshes();
	shaderProgram = new ShaderProgram("./assets/lighting.vert", "./assets/texture2.frag");
	light = new Light(kLightDirectional);
	light->direction = Vector3(-0.2f, -1.0f, -0.3f);
	light->ambient = Vector3(0.1f, 0.1f, 0.1f);
	light->diffuse = Vector3(1.4f, 1.4f, 1.4f);
	light->specular = Vector3(0.5f, 0.5f, 0.5f);
	light->AddToManager();
	delete(light);

	for (int i = 0; i < meshes->size(); i++)
	{
		GameObject *tmp = new GameObject();
		mat = new Material(shaderProgram);
		mat->SetDirectionLight(GetLightManager().GetDirectionLight());
		//boxMat->SetTexture("material.diffuse", diffuseMap);
		//boxMat->SetTexture("material.specular", specularMap);
		//boxMat->SetFloat("material.shininess", 32.0f);

		for (int j = 0; j < (*meshes)[i].textures.size(); j++)
		{
			//qDebug() << (int)(*meshes)[i].textures[i].GetTextureID();
			//std::stringstream ss;
			//ss << (*meshes)[i].textures[j]->type;
			//ss << j;
			mat->SetTextureVariable((*meshes)[i].textures[j]->GetUniformName(), (*meshes)[i].textures[j]->GetTexture());
			mat->SetFloat("material.shininess", 32.0f);
			//mat->SetTexture(ss.str(), (*meshes)[i].textures[i]);
		}
		
		MeshRenderer* meshRenderer = new MeshRenderer(&(*meshes)[i], mat);
		tmp->AddComponent(meshRenderer);
		sponza->AddChild(tmp);
	}
	scene = new Scene();
	scene->AddGameObject(sponza);
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
}

void App::FrameMove()
{

}
