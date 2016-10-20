#pragma once
#pragma comment( lib, "..\\3rdParty\\lib\\SDL\\x86\\SDL2_image.lib" )

#include "../../3rdParty/include/SDL/SDL_image.h"
#include "Base.h"

/********************************
Class:		Texture
Purpose:	Wraps OpenGL texture object and performs their loading.
********************************/
class Texture;

class TextureVariable
{
public:
	TextureVariable();
	~TextureVariable();
	TextureVariable(Texture* texture, GLenum textureUnit, string uniformRefname);

	void SetTextureUnit(GLenum textureUnit);
	GLenum GetTextureUnit() const;
	GLuint GetTextureID() const;
	string GetUniformName() const;
	Texture* GetTexture();
	void bind();

private:
	GLenum textureUnit;
	Texture* texture;
	std::string uniformRefname;

};