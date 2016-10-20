#pragma once

#include "Base.h"
#include "TextureVariable.h"

class IUniform
{
protected:
	string m_uniformName;
	GLuint m_uniformLocation;

public:
	IUniform(string uniformName) : m_uniformName(uniformName), m_uniformLocation(-1) {}
	virtual ~IUniform() {}

	virtual void bind() = 0;

	//inline void attachToShader(GLuint programID);

	inline const string& getName() const { return m_uniformName; }
	inline GLuint getLocation() const { return m_uniformLocation; }

	//For IUniform

	inline void IUniform::attachToShader(GLuint programID)
	{
		m_uniformLocation = glGetUniformLocation(programID, m_uniformName.c_str());
	}

	inline bool operator<(const IUniform& right) { return m_uniformName < right.getName(); }
};

template<typename T>
class UniformVariable : public IUniform
{
	T m_uniformData;

public:
	UniformVariable(string uniformName) : IUniform(uniformName), m_uniformData() {}
	virtual ~UniformVariable() {}

	inline void setData(const T& data);
	inline T& getData();

	virtual void bind();

	bool hasBeenSettle;
};

/*
//A specialization for UniformVariable<Texture>
template<>
class UniformVariable<TextureVariable> : public UniformVariable<TextureVariable*>
{
public:
	UniformVariable(const string& uniformName) : UniformVariable<TextureVariable*>(uniformName) {}
};
*/

template<typename T>
void UniformVariable<T>::setData(const T& data)
{
	hasBeenSettle = true;
	m_uniformData = data;
}

template<typename T>
T& UniformVariable<T>::getData()
{
	return m_uniformData;
}

//Template Instantiations for bind() (instantiations only, see .cpp for definitions)

template<> void UniformVariable<int>::bind();
template<> void UniformVariable<float>::bind();
template<> void UniformVariable<double>::bind();
template<> void UniformVariable<unsigned int>::bind();
template<> void UniformVariable<bool>::bind();
template<> void UniformVariable<Vector2>::bind();
template<> void UniformVariable<Vector3>::bind();
template<> void UniformVariable<Vector4>::bind();
template<> void UniformVariable<Matrix2>::bind();
template<> void UniformVariable<Matrix3>::bind();
template<> void UniformVariable<Matrix4x4>::bind();
template<> void UniformVariable<TextureVariable>::bind();
