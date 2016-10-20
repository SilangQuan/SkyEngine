#include "Render/Shader.h"

Shader::Shader(const string& filePath, ShaderType type):shaderID(0),type(type),Resource(filePath)
{
	Init(filePath);
}

Shader::Shader(const std::string &filePath): Resource(filePath)
{
	if (EndsWith(filePath, ".vert"))
	{
		type = ShaderType::VERTEX_SHADER;
	}
	else if (EndsWith(filePath, ".frag"))
	{
		type = ShaderType::FRAGMENT_SHADER;
	}
	Init(filePath);
}

Shader::~Shader()
{
	Destroy();
}

void Shader::Init(const string& filePath)
{
	Create();
	string shaderSource = LoadShaderSource(filePath);
	CompileShaderFromSource(shaderSource);
}
void Shader::Create()
{
	switch (type)
	{
	case VERTEX_SHADER:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;

	case TESS_CONTROL_SHADER:
		shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;

	case TESS_EVALUATION_SHADER:
		shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;

	case GEOMETRY_SHADER:
		shaderID = glCreateShader(GL_GEOMETRY_SHADER);
		break;

	case FRAGMENT_SHADER:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;

	default:
		shaderID = -1;
		break;
	}

	if (shaderID == -1)
	{
		qDebug() << "Shader create Error";
	}
}
string Shader::LoadShaderSource(const string& filePath)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::ifstream fileStream;
	// ensures ifstream objects can throw exceptions:
	fileStream.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		fileStream.open(filePath);
		std::stringstream stringStream;
		// Read file's buffer contents into streams
		stringStream << fileStream.rdbuf();
		// close file handlers
		fileStream.close();
		// Convert stream into string
		shaderCode = stringStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderCode;
}

void Shader::CompileShaderFromSource(const string& source)
{
	GLchar infoLog[512];

	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, 0);
	glCompileShader(shaderID);

	//Throw exception if compilation failed
	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus != GL_TRUE)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR:: Compile Shader FromSource failed!" << infoLog << std::endl;
	}else
	{
		std::cout << shaderID <<" shader compile success!"<< std::endl;
	}
}
void Shader::Destroy()
{
	glDeleteShader(shaderID);
}