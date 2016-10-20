#pragma once
#include "Base.h"
class ShaderProgram;
class TextureVariable;
class Texture;
class Light;
class Camera;
class RenderContext;

class Material
{
	ShaderProgram* shaderProgram;

public:
	Material(ShaderProgram* shader);
	virtual ~Material();

	void Bind(RenderContext* renderContext);

	ShaderProgram* GetShaderProgram();

	void SetShader(ShaderProgram* shader);
	//void AddTexture(Texture& texture);
	void SetTextureVariable(string shaderRefName, Texture* texture);

	void SetFloat(string shaderRefName, float value);
	void SetVector3(string shaderRefName, Vector3 value);

	void SetDirectionLight(Light& light);
	void SetPointLight(vector<Light>& light);
	void SetSpotLight(vector<Light>& light);

	vector<TextureVariable*> textureVariables;
};