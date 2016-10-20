#include "Render/Texture.h"


Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}



Texture::Texture(const std::string& f, string _type):Resource(f)
{
	filePath = f;
	isLoaded = false;
	surface = NULL;
	type = _type;

	//Default value
	wrapHorizontal = GL_REPEAT;
	wrapVertical = GL_REPEAT;
	magnifiFilter = GL_LINEAR;
	minifiFilter = GL_LINEAR_MIPMAP_LINEAR;
	generateMipMap = false;
	Load();
}

Texture::Texture(const std::string &file) :Resource(file)
{
	filePath = file;
	isLoaded = false;
	surface = NULL;
	//type = _type;

	//Default value
	wrapHorizontal = GL_REPEAT;
	wrapVertical = GL_REPEAT;
	magnifiFilter = GL_LINEAR;
	minifiFilter = GL_LINEAR_MIPMAP_LINEAR;
	generateMipMap = true;
	Load();
}

bool Texture::Load()
{
	//glEnable(GL_TEXTURE0 + textureUnit);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	

	if (surface == NULL) { //If it failed, say why and don't continue loading the texture
		qDebug() << "Error:" << SDL_GetError();
		return 0;
	}

	width = surface->w;
	height = surface->h;
	bpp = surface->pitch;

	// work out what format to tell glTexImage2D to use...
	if (surface->format->BytesPerPixel == 3) { // RGB 24bit
		mode = GL_RGB;
	}
	else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit
		mode = GL_RGBA;
	}
	else {
		SDL_FreeSurface(surface);
		return false;
	}

	//glBindTexture(textureTarget, textureObj);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	if(generateMipMap)
		glGenerateMipmap(GL_TEXTURE_2D);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapHorizontal);    // Note that we set our container wrapping method to GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapVertical);    // Note that we set our container wrapping method to GL_CLAMP_TO_EDGE

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minifiFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifiFilter);

	if (surface) SDL_FreeSurface(surface);
	isLoaded = true;

	return true;
}

// Sets magnification and minification texture filter.

void Texture::SetFiltering(int _magnification, int _minification)
{
	magnifiFilter = _magnification;
	minifiFilter = _minification;
}

void Texture::DeleteTexture()
{
	if (surface) SDL_FreeSurface(surface);
}


int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}

int Texture::GetBPP()
{
	return bpp;
}

std::string Texture::GetPath()
{
	return filePath;
}

void Texture::SetPath(std::string& path)
{
	filePath = path;
}

void Texture::SetPath(const char * path)
{
	filePath = path;
}

bool Texture::HasLoaded()
{
	return isLoaded;
}

void Texture::SetWrap(int _wrapS, int _wrapT)
{
	wrapHorizontal = _wrapS;
	wrapVertical = _wrapT;
}

void Texture::SetMipMapActive(bool enable)
{
	generateMipMap = enable;
}

GLuint Texture::GetTextureID()
{
	return textureID;
}


/*
void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

*/
