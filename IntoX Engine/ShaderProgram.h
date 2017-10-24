#pragma once

#include "stdfax.h"
#include "ShaderAttributeLocationBinder.h"
#include <glm\mat4x4.hpp>
#include <memory>

class ShaderProgram
{
public:	
	~ShaderProgram();

	void Start();
	void Stop();

	void LoadUniformVector3f(std::string uniform, glm::vec3 vector);
	void LoadUniformMatrix4f(std::string uniform, glm::mat4 matrix);

	static std::unique_ptr<ShaderProgram> Create(std::string vertexFile, std::string fragmentFile, ShaderAttributeLocationBinder shaderAttributeLocationBinder);

protected:
	unsigned int m_programID;
	unsigned int m_vertexShaderID;
	unsigned int m_fragmentShaderID;
	ShaderAttributeLocationBinder m_shaderVarBinder;

	void LoadAllAttributes();
	void LoadAllUniformLocations();

private:
	ShaderProgram(unsigned int programID, unsigned int vertexShaderID, unsigned int fragmentShaderID, ShaderAttributeLocationBinder shaderAttributeLocationBinder);
	static unsigned int LoadShader(const std::string& file, unsigned int shaderType);	

	
};

