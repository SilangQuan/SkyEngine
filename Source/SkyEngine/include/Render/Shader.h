#pragma once
#include "Base.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Shader : public Resource
{
public:
	enum ShaderType
	{
		VERTEX_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,

		NUM_SHADER_TYPES
	};
	Shader(const std::string &file);
	Shader(const string& filePath, ShaderType type);
	~Shader();

	GLuint shaderID;
	ShaderType type;
	
	void Init(const string& filePath);
	void Create();
	static string LoadShaderSource(const string& filePath);
	void CompileShaderFromSource(const string& source);
	void Destroy();

	inline bool EndsWith(std::string const & value, std::string const & ending)
	{
		if (ending.size() > value.size()) return false;
		return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
	}
};

