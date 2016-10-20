#pragma once
#include "Base.h"
#include "Shader.h"
#include "Lighting/Light.h"
#include "UniformVariable.h"
class RenderContext;
class ShaderProgram
{
	GLuint m_programID;
	Shader* shaders[Shader::NUM_SHADER_TYPES]; //ShaderProgram has ownership of its shaders
	map<const string, IUniform*> uniformsMap;
	vector<IUniform*> m_uniforms;	//ShaderProgram does not have ownership of its UniformVariables

public:
	ShaderProgram(const std::string& vsFile, const std::string& fsFile);
	ShaderProgram(ShaderProgram& shaderProgram);
	virtual ~ShaderProgram();

	template<typename T> inline void AddUniform(const string& uniformName, const T& uniformData);
	template<typename T> inline void SetUniform(const string& uniformName, const T& uniformData);
	//template<typename T> inline void SetTestUniform(const string& uniformName, const T& uniformData);
	template<typename T> inline UniformVariable<T>* TryGetUniform(const string& uniformName);

	void Bind(RenderContext* renderContext);
	void Use();
	GLuint GetProgramID() const;
	uint32 GetNumUniforms() const;
	uint32 FindUniform(const string& uniformName) const;
	bool HasUniform(const string& uniformName) const;
	IUniform* GetUniform(const string& uniformName);

	void SetDirectionLightUniform(Light& light);
	void SetPointLightsUniform(vector<Light>& light);

	UniformVariable<Matrix4x4>* modelUniform;
	UniformVariable<Matrix4x4>* viewUniform;
	UniformVariable<Vector3>* viewPosUniform;
	UniformVariable<Matrix4x4>* projectionUniform;
	UniformVariable<Matrix4x4>* viewProjectionUniform;

protected:
	virtual void init(const std::string& vsFile, const std::string& fsFile);
	Shader* addShader(Shader* shader);
	void create();
	void link();
	void validate();
	void detectUniforms();
	template<typename T> inline void AddUniform(const string& uniformName);
	void destroy();

private:
	bool hasViewPosUniform;
	bool hasViewUniform;
	bool hasModelUniform;
	bool hasProjectionUniform;
	bool hasViewProjectionUniform;
};


template<typename T>
void ShaderProgram::AddUniform(const string& uniformName)
{
	UniformVariable<T>* uniform = new UniformVariable<T>(uniformName);
	uniform->attachToShader(this->GetProgramID());
	m_uniforms.push_back(uniform);
	uniformsMap.insert(make_pair(uniformName, uniform));
}

template<typename T>
void ShaderProgram::AddUniform(const string& uniformName, const T& uniformData)
{
	UniformVariable<T>* uniform = new UniformVariable<T>(uniformName);
	uniform->attachToShader(this->GetProgramID());
	uniform->setData(uniformData);

	m_uniforms.push_back(uniform);
	uniformsMap.insert(make_pair(uniformName, uniform));
}


template<typename T>
void ShaderProgram::SetUniform(const string& uniformName, const T& uniformData)
{
	IUniform* iuniform = this->GetUniform(uniformName);

	if (iuniform == 0)
	{
		string message = " Error:This ShaderProgram does not have an IUniform with name '";
		message += uniformName;
		message += "'.";
		qDebug()<<message;
	}

	UniformVariable<T>* uniform = dynamic_cast<UniformVariable<T>*>(iuniform);

	if (uniform == 0)
	{
		string message = "Invalid type conversion for UniformVariable<T> with name '";
		message += uniformName;
		message += "'.";
		qDebug() << message;
	}

	uniform->setData(uniformData);
}

template<typename T>
UniformVariable<T>* ShaderProgram::TryGetUniform(const string& uniformName)
{
	IUniform* iuniform = this->GetUniform(uniformName);

	if (iuniform == 0)
	{
		string message = "Info:This ShaderProgram does not have an IUniform with name '";
		message += uniformName;
		message += "'.";
		qDebug() << message;
		return NULL;
	}

	UniformVariable<T>* uniform = dynamic_cast<UniformVariable<T>*>(iuniform);

	if (uniform == 0)
	{
		string message = "Info :Invalid type conversion for UniformVariable<T> with name '";
		message += uniformName;
		message += "'.";
		qDebug() << message;
	}

	return uniform;
}

