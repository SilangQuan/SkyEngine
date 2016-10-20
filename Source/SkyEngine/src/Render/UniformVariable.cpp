
#include "Render/UniformVariable.h"
#include "Render/TextureVariable.h"
#include "Render/Texture.h"

template<>
void UniformVariable<int>::bind()
{
	glUniform1i(m_uniformLocation, m_uniformData);
}

template<>
void UniformVariable<float>::bind()
{
	glUniform1f(m_uniformLocation, m_uniformData);
}

template<>
void UniformVariable<double>::bind()
{
	glUniform1d(m_uniformLocation, m_uniformData);
}

template<>
void UniformVariable<unsigned int>::bind()
{
	glUniform1ui(m_uniformLocation, m_uniformData);
}

template<>
void UniformVariable<bool>::bind()
{
	glUniform1i(m_uniformLocation, m_uniformData);
}

template<>
void UniformVariable<Vector2>::bind()
{
	glUniform2f(m_uniformLocation,
		m_uniformData.x,
		m_uniformData.y);
}

template<>
void UniformVariable<Vector3>::bind()
{
	glUniform3f(m_uniformLocation,
		m_uniformData.x,
		m_uniformData.y,
		m_uniformData.z);
}

template<>
void UniformVariable<Vector4>::bind()
{
	glUniform4f(m_uniformLocation,
		m_uniformData.x,
		m_uniformData.y,
		m_uniformData.z,
		m_uniformData.w);
}

template<>
void UniformVariable<Matrix2>::bind()
{
	glUniformMatrix2fv(m_uniformLocation,
		1, false,
		&(m_uniformData[0]));
}

template<>
void UniformVariable<Matrix3>::bind()
{
	glUniformMatrix3fv(m_uniformLocation,
		1, false,
		&(m_uniformData[0]));
}

template<>
void UniformVariable<Matrix4x4>::bind()
{
	glUniformMatrix4fv(m_uniformLocation,
		1, false,
		&(m_uniformData[0]));
}

template<>
void UniformVariable<TextureVariable>::bind()
{
	//if (m_uniformData != NULL)
	//{
	if (hasBeenSettle)
	{
		m_uniformData.bind();
		glUniform1i(m_uniformLocation, m_uniformData.GetTextureUnit());
	}
		
	//}
}