#pragma once
#include "stdfax.h"

class Texture
{
public:	
	~Texture();

	static Texture* LoadTexture(std::string path);

	unsigned int GetID();

private:
	Texture(unsigned int textureID);

	unsigned int m_textureId;
};

