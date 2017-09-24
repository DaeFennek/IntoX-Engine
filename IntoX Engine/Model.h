#pragma once
#include "Texture.h"

class Model
{
public:
	Model(unsigned int vaoId, unsigned int verticesCount);
	~Model();

	unsigned int GetVao();
	unsigned int GetVerticesCount();
	bool HasTexture();
	unsigned int GetTextureID();
	void SetTexture(class Texture* texture);

private:
	unsigned int m_vaoId;
	unsigned int m_verticesCount;
	class Texture* m_texture = NULL;

};

