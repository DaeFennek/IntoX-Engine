#pragma once

#include <vector>
#include "stdfax.h"
#include "Model.h"

class Loader
{
public:
	Loader();
	~Loader();

	Model& CreateModel(const std::vector<float>& vertices, const std::vector<float>& textureCoords, const  std::vector<unsigned int>& indices);
	Model* LoadObj(std::string filePath);
	void Clean();

private:
	unsigned int CreateVao();	
	void UnbindVao();
	void BindIndicesVbo(const std::vector<unsigned int>& indices);
	void StoreDataIntoVbo(unsigned int attribute, const std::vector<float>& data, int size);

private:
	std::vector<const unsigned int> m_vaos;
	std::vector<const unsigned int> m_vbos;
	std::vector<const Model*> m_models;
};

