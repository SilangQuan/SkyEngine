#include "Render/Material.h"
#include "Render/ShaderProgram.h"
#include "Render/Texture.h"
#include "Render/TextureVariable.h"
#include "Lighting/Light.h"

Material::Material(ShaderProgram* _shaderProgram)
{
	shaderProgram = new ShaderProgram(*_shaderProgram);
}

void Material::Bind(RenderContext* renderContext)
{
	/*for (vector<TextureVariable*>::iterator iter = textureVariables.begin(); iter < textureVariables.end(); iter++)
	{
		shaderProgram->SetUniform((*iter)->GetUniformName(), **iter);
	}*/

	if (shaderProgram != 0)
	{
		shaderProgram->Bind(renderContext);
	}
}

ShaderProgram* Material::GetShaderProgram()
{
	return shaderProgram;
}

/*
Texture& Material::GetTexture(int index)
{
	return textures[index];
}
*/

void Material::SetShader(ShaderProgram* shader)
{
	shader = shader;
}

/*
void Material::AddTexture(Texture& texture)
{
	textures.push_back(texture);
}*/
void Material::SetTextureVariable(string shaderRefName, Texture* texture)
{
	if (shaderProgram->HasUniform(shaderRefName))
	{
		TextureVariable* tmpTextureVariable = new TextureVariable(texture, textureVariables.size(), shaderRefName);
		textureVariables.push_back(tmpTextureVariable);
		shaderProgram->SetUniform(shaderRefName, *tmpTextureVariable);
	}else
	{
		qDebug() << "No such shaderRefName " << shaderRefName;
	}
}

void Material::SetFloat(string shaderRefName, float value)
{
	if (shaderProgram->HasUniform(shaderRefName))
	{
		shaderProgram->SetUniform(shaderRefName, value);
	}
	else
	{
		qDebug() << "No such shaderRefName " << shaderRefName;
	}
}
void Material::SetVector3(string shaderRefName, Vector3 value)
{
	if (shaderProgram->HasUniform(shaderRefName))
	{
		shaderProgram->SetUniform(shaderRefName, value);
	}
	else
	{
		qDebug() << "No such shaderRefName " << shaderRefName;
	}
}

void Material::SetDirectionLight(Light& light)
{
	if (light.type != kLightDirectional)
	{
		qDebug() << "Cannot Set DirectionLight. Wrong light type. ";
	}

	if (shaderProgram->HasUniform("dirLight.direction"))
	{
		shaderProgram->SetUniform("dirLight.direction", light.direction);
	}
	else
	{
		qDebug() << "No such shaderRefName dirLight.direction";
	}

	if (shaderProgram->HasUniform("dirLight.ambient"))
	{
		shaderProgram->SetUniform("dirLight.ambient", light.ambient);
	}
	else
	{
		qDebug() << "No such shaderRefName dirLight.ambient";
	}

	if (shaderProgram->HasUniform("dirLight.diffuse"))
	{
		shaderProgram->SetUniform("dirLight.diffuse", light.diffuse);
	}
	else
	{
		qDebug() << "No such shaderRefName dirLight.diffuse";
	}

	if (shaderProgram->HasUniform("dirLight.specular"))
	{
		shaderProgram->SetUniform("dirLight.specular", light.specular);
	}
	else
	{
		qDebug() << "No such shaderRefName dirLight.specular";
	}
}

void Material::SetPointLight(vector<Light>& lights)
{
	int count = 0;

	bool isArray = false;
	if (lights.size() > 1)
	{
		isArray = true;
	}

	for (vector<Light>::const_iterator lightIter = lights.begin(); lightIter != lights.end(); lightIter++)
	{
		if (lightIter->type != kLightPoint)
		{
			qDebug() << "Cannot Set DirectionLight. Wrong light type. ";
		}
		string lightName = "pointLights";

		if(isArray)
		{
			lightName += "[" + std::to_string(count++) + "]";
		}

		if (shaderProgram->HasUniform(lightName + ".position"))
		{
			shaderProgram->SetUniform(lightName + ".position", lightIter->position);
		}
		else
		{
			qDebug() << "No such position "<< lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".ambient"))
		{
			shaderProgram->SetUniform(lightName + ".ambient", lightIter->ambient);
		}
		else
		{
			qDebug() << "No such ambient" << lightName;
		} 

		if (shaderProgram->HasUniform(lightName + ".diffuse"))
		{
			shaderProgram->SetUniform(lightName + ".diffuse", lightIter->diffuse);
		}
		else
		{
			qDebug() << "No such diffuse" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".specular"))
		{
			shaderProgram->SetUniform(lightName + ".specular", lightIter->specular);
		}
		else
		{
			qDebug() << "No such specular " << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".constant"))
		{
			shaderProgram->SetUniform(lightName + ".constant", lightIter->constant);
		}
		else
		{
			qDebug() << "No such constant" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".linear"))
		{
			shaderProgram->SetUniform(lightName + ".linear", lightIter->linear);
		}
		else
		{
			qDebug() << "No such linear" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".quadratic"))
		{
			shaderProgram->SetUniform(lightName + ".quadratic", lightIter->quadratic);
		}
		else
		{
			qDebug() << "No such quadratic" << lightName;
		}
	}
}

void Material::SetSpotLight(vector<Light>& lights)
{
	bool isArray = false;
	if(lights.size() > 1)
	{
		isArray = true;
	}

	int count = 0;

	for (vector<Light>::const_iterator lightIter = lights.begin(); lightIter != lights.end(); lightIter++)
	{
		if (lightIter->type != kLightSpot)
		{
			qDebug() << "Cannot Set DirectionLight. Wrong light type. ";
		}
		string lightName = "spotLight";

		if(isArray)
			lightName += "[" + std::to_string(count++) +"]";


		if (shaderProgram->HasUniform(lightName + ".position"))
		{
			shaderProgram->SetUniform(lightName + ".position", lightIter->position);
		}
		else
		{
			qDebug() << "No such position " << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".direction"))
		{
			shaderProgram->SetUniform(lightName + ".direction", lightIter->position);
		}
		else
		{
			qDebug() << "No such direction " << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".ambient"))
		{
			shaderProgram->SetUniform(lightName + ".ambient", lightIter->ambient);
		}
		else
		{
			qDebug() << "No such ambient" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".diffuse"))
		{
			shaderProgram->SetUniform(lightName + ".diffuse", lightIter->diffuse);
		}
		else
		{
			qDebug() << "No such diffuse" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".specular"))
		{
			shaderProgram->SetUniform(lightName + ".specular", lightIter->specular);
		}
		else
		{
			qDebug() << "No such specular " << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".cutOff"))
		{
			shaderProgram->SetUniform(lightName + ".cutOff", lightIter->cutOff);
		}
		else
		{
			qDebug() << "No such cutOff" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".outerCutOff"))
		{
			shaderProgram->SetUniform(lightName + ".outerCutOff", lightIter->outerCutOff);
		}
		else
		{
			qDebug() << "No such outerCutOff" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".constant"))
		{
			shaderProgram->SetUniform(lightName + ".constant", lightIter->constant);
		}
		else
		{
			qDebug() << "No such constant" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".linear"))
		{
			shaderProgram->SetUniform(lightName + ".linear", lightIter->linear);
		}
		else
		{
			qDebug() << "No such linear" << lightName;
		}

		if (shaderProgram->HasUniform(lightName + ".quadratic"))
		{
			shaderProgram->SetUniform(lightName + ".quadratic", lightIter->quadratic);
		}
		else
		{
			qDebug() << "No such quadratic" << lightName;
		}
	}
}

Material::~Material() {}