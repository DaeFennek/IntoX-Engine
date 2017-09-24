#include "Loader.h"
#include <GL\glew.h>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

Loader::Loader()
{
}


Loader::~Loader()
{
}

// todo remove and use Assimp
/*Model* Loader::LoadObj(std::string filePath)
{	
	float* pUVList = NULL;
	float* pNormalList = NULL;

	std::vector<unsigned int> vertexIndices;	

	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2> temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	std::ifstream fileStream(filePath, std::ios::in);

	if (fileStream.is_open())
	{
		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);			
			std::vector<std::string> lineTokens;
			boost::split(lineTokens, line, boost::is_any_of(" "));

			if (lineTokens[0] == "#")
			{
				continue;
			}
			else if (lineTokens[0] == "v")
			{
				glm::vec3 vertex(std::stof(lineTokens[1]), std::stof(lineTokens[2]), std::stof(lineTokens[3]));
				temp_vertices.push_back(vertex);				
			} 
			else if (lineTokens[0] == "vt")
			{
				glm::vec2 uv(std::stof(lineTokens[1]), std::stof(lineTokens[2]));
				temp_uvs.push_back(uv);
			}
			else if (lineTokens[0] == "vn")
			{
				glm::vec3 normal(std::stof(lineTokens[1]), std::stof(lineTokens[2]), std::stof(lineTokens[3]));
				temp_normals.push_back(normal);
			}
			else if (lineTokens[0] == "f")
			{
				if (!pUVList && !pUVList)
				{
					pUVList = new float[temp_vertices.size() * 2];
					pNormalList = new float[temp_vertices.size() * 3];
				}

				for (unsigned int i = 1; i < lineTokens.size(); i++)
				{
					std::vector<std::string> fTokens;
					boost::split(fTokens, lineTokens[i], boost::is_any_of("/"));
					if (fTokens[0] == "")
					{
						continue;
					}

					unsigned int cVertexIndex = std::stoi(fTokens[0]) - 1;
					vertexIndices.push_back(cVertexIndex);

					glm::vec2 cUV = temp_uvs[std::stoi(fTokens[1]) - 1];					
					pUVList[cVertexIndex * 2] = cUV.x;
					pUVList[cVertexIndex * 2 + 1] = 1 - cUV.y;

					glm::vec3 cNormal = temp_normals[std::stoi(fTokens[2]) - 1];
					pNormalList[cVertexIndex * 3] = cNormal.x;
					pNormalList[cVertexIndex * 3 + 1] = cNormal.y;
					pNormalList[cVertexIndex * 3 + 2] = cNormal.z;
				}
			}			
		}

		fileStream.close();

		std::vector<float> vertices;	
		for (auto vertex : temp_vertices)
		{			
			vertices.push_back(vertex.x);
			vertices.push_back(vertex.y);
			vertices.push_back(vertex.z);
		}

		std::vector<float> textureCoords;
		int a = temp_vertices.size() * 2;
		for (unsigned int i = 0; i < temp_vertices.size() * 2; i++)
		{
			textureCoords.push_back(pUVList[i]);
		}

		delete pUVList;
		delete pNormalList;

		return &CreateModel(vertices, textureCoords, vertexIndices);
	}

	return NULL;
}*/

Model& Loader::CreateModel(const std::vector<float>& vertices, const std::vector<float>& textureCoords, const std::vector<unsigned int>& indices)
{
	unsigned int vao = CreateVao();	
	BindIndicesVbo(indices);
	StoreDataIntoVbo(0, vertices, 3);		
	StoreDataIntoVbo(1, textureCoords, 2);
	UnbindVao();
	Model* model = new Model(vao, indices.size());
	m_models.push_back(model);
	return *model;
}

unsigned int Loader::CreateVao()
{	
	unsigned int vao;
	glGenVertexArrays(1, &vao);	
	m_vaos.push_back(vao);
	glBindVertexArray(vao);
	return vao;
}

void Loader::UnbindVao()
{
	glBindVertexArray(0);
}

void Loader::BindIndicesVbo(const std::vector<unsigned int>& indices)
{
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	m_vbos.push_back(vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
}


void Loader::StoreDataIntoVbo(unsigned int attribute, const std::vector<float>& data, int size)
{
	unsigned int vbo;
	glGenBuffers(1, &vbo); 
	m_vbos.push_back(vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW);	
	glVertexAttribPointer(attribute, size, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::Clean()
{
	for (auto vao : m_vaos)
	{
		glDeleteVertexArrays(1, &vao);
	}

	for (auto vbo : m_vbos)
	{
		glDeleteBuffers(1, &vbo);
	}

	for (auto model : m_models)
	{
		delete model;
	}

	m_models.clear();
}