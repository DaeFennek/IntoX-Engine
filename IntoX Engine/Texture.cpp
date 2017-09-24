#include "Texture.h"
#include "stdfax.h"

Texture::Texture(unsigned int textureID) : m_textureId(textureID)
{	
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_textureId);
}

Texture* Texture::LoadTexture(std::string path)
{
	SDL_Surface* pTextureSurface = IMG_Load(path.c_str());
	if (!pTextureSurface)
	{
		DebugLog::Print("Could not load texture '" + path + "' - " + SDL_GetError(), DebugLog::WARNING_LOG);
		return nullptr;
	}

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pTextureSurface->w, pTextureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, pTextureSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.0f);	
	
	SDL_FreeSurface(pTextureSurface);

	return new Texture(textureID);
}

unsigned int Texture::GetID()
{
	return m_textureId;
}