#include "Render/Texture.h"
#include "Render/TextureVariable.h"

TextureVariable::TextureVariable()
{

}

TextureVariable::TextureVariable(Texture* _texture, GLenum _textureUnit, string _uniformRefname)
{
	textureUnit = _textureUnit;
	texture = _texture;
	uniformRefname = _uniformRefname;
	//qDebug() << "new TextureVariable" << (int)_texture->GetTextureID();
}

TextureVariable::~TextureVariable()
{

}


void  TextureVariable::SetTextureUnit(GLenum _textureUnit)
{
	textureUnit = _textureUnit;
}

GLenum TextureVariable::GetTextureUnit() const
{
	return textureUnit;
}

GLuint TextureVariable::GetTextureID() const
{
	return texture->GetTextureID();
}

std::string TextureVariable::GetUniformName() const
{
	return uniformRefname;
}

Texture* TextureVariable::GetTexture()
{
	return texture;
}

void TextureVariable::bind()
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
}
