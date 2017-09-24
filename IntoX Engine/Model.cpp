#include "Model.h"


Model::Model(unsigned int vaoId, unsigned int verticesCount) : m_vaoId(vaoId), m_verticesCount(verticesCount)
{
}


Model::~Model()
{
}


unsigned int Model::GetVao()
{
	return m_vaoId;
}


unsigned int Model::GetVerticesCount()
{
	return m_verticesCount;
}

bool Model::HasTexture()
{
	return m_texture;
}

unsigned int Model::GetTextureID()
{
	if (m_texture)
	{
		return m_texture->GetID();
	}

	return 0;
}

void Model::SetTexture(class Texture* texture)
{
	m_texture = texture;
}