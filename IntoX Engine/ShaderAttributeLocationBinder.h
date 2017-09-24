#pragma once

#include "stdfax.h"
#include <map>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

#define DEFAULT_PROJECTION_MATRIX "projectionMatrix"
#define DEFAULT_VIEW_MATRIX "viewMatrix"
#define DEFAULT_TRANSFORMATION_MATRIX "transformationMatrix"

class ShaderAttributeLocationBinder
{
public:
	ShaderAttributeLocationBinder(bool bUseDefaultMVPUniforms);
	ShaderAttributeLocationBinder();
	~ShaderAttributeLocationBinder();

	void BindAttributes(unsigned int programId);
	void AddAttribute(unsigned int attribute, std::string variableName);
	

	void AddUniform(std::string uniform);
	void LoadAllUniformLocations(unsigned int programId);	
	void LoadUniformMatrix(const std::string& uniform, const glm::mat4& matrix);
	void LoadUniformVector3(const std::string& uniform, const glm::vec3& vector);

private:
	std::map<unsigned int, std::string> m_attributeLocationMap;
	std::map<std::string, int> m_uniformMap;

	int GetUniformLocation(const std::string& uniform);
};

