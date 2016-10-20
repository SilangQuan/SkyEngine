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
	GLuint boxVBO, boxVAO;

	GLuint lightVAO;

	Texture* diffuseMap;
	Texture* specularMap;

	Shader* lampShader;
	Shader* lightingShader;

	Vector3* cubePositions;
	Vector3* pointlightPositions;
	Vector3* pointlightDiffuses;
	Camera* camera;

	Vector3 lightPos;
	float mixValue;

	void UpdateCamera();

	ShaderProgram* lampProgram;
	ShaderProgram* lightingProgram;

	Scene* scene;
	GameObject* box;
	GameObject* boxes;
	GameObject* lightObj;
	GameObject tmpBox;

	Material* boxMat;
	Material* lampMat;
	Mesh* boxMesh;

	Light* light;
};