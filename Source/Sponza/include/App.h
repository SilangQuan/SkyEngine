#pragma once
#include "../../LibAppFramework/include/application.h"


class App : public Application
{
public:
	//bool Initialize();
	bool CreateWorld();
	void DestroyWorld();

	void FrameMove();
	void RenderWorld();

private:
	GameObject* sponza;
	ShaderProgram* shaderProgram;
	Scene* scene;
	Material* mat;
	Model* bunny;
	Camera* camera;
	Light* light;
	void UpdateCamera();
};