#include "ShaderAttributeLocationBinder.h"
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>


ShaderAttributeLocationBinder::ShaderAttributeLocationBinder()
{
	
}

ShaderAttributeLocationBinder::~ShaderAttributeLocationBinder()
{

}

void ShaderAttributeLocationBinder::BindAttributes(unsigned int programId)
{
	for (auto attributes : m_attributeLocationMap)
	{
		glBindAttribLocation(programId, attributes.first, attributes.second.c_str());
	}
}

void ShaderAttributeLocationBinder::AddAttribute(unsigned int attribute, std::string variableName)
{
	m_attributeLocationMap.insert(std::pair<unsigned int, std::string>(attribute, variableName));
}

void ShaderAttributeLocationBinder::AddUniform(std::string uniform)
{	
	if ( !m_uniformMap.insert(std::pair<std::string, int>(uniform, -2)).second)
	{
		DebugLog::Print("Could not add uniform '" + uniform + "'!", DebugLog::WARNING_LOG);
	}
}

void ShaderAttributeLocationBinder::LoadAllUniformLocations(unsigned int programId)
{
	for (auto& uniform : m_uniformMap)
	{
		auto location = glGetUniformLocation(programId, uniform.first.c_str());
		if (location >= 0)
		{
			uniform.second = location;			
		}
		else
		{
			DebugLog::Print("Couldn't initialize uniform '" + uniform.first + "'!", DebugLog::WARNING_LOG);
		}		
	}
}


void ShaderAttributeLocationBinder::LoadUniformMatrix(const std::string& uniform, const glm::mat4& matrix)
{
	auto uniformLocation = GetUniformLocation(uniform);
	if (uniformLocation >= 0)
	{
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix)); 
	}
}

void ShaderAttributeLocationBinder::LoadUniformVector3(const std::string& uniform, const glm::vec3& vector)
{
	auto uniformLocation = GetUniformLocation(uniform);
	if (uniformLocation >= 0)
	{
		glUniform3fv(uniformLocation, 1, glm::value_ptr(vector));
	}
}

int ShaderAttributeLocationBinder::GetUniformLocation(const std::string& uniform)
{
	unsigned int uniformLocation = -1;
	auto mapIterator = m_uniformMap.find(uniform);
	if (mapIterator != m_uniformMap.end() && mapIterator->second >= 0)
	{
		uniformLocation = mapIterator->second;
	}
	else
	{
		DebugLog::Print("Could not locate uniform '" + uniform + "' or uniform location isn't initialized!", DebugLog::WARNING_LOG);
	}

	return uniformLocation;
}
