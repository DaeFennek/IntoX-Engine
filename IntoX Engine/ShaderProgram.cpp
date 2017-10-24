#include "ShaderProgram.h"
#include <GL\glew.h>
#include "FileHelper.h"

ShaderProgram::ShaderProgram(unsigned int programID, unsigned int vertexShaderID, unsigned int fragmentShaderID, ShaderAttributeLocationBinder shaderAttributeLocationBinder) : m_programID(programID), m_vertexShaderID(vertexShaderID), m_fragmentShaderID(fragmentShaderID), m_shaderVarBinder(shaderAttributeLocationBinder)
{

}

std::unique_ptr<ShaderProgram> ShaderProgram::Create(std::string vertexFile, std::string fragmentFile, ShaderAttributeLocationBinder shaderAttributeLocationBinder)
{	
	unsigned int programID, vertexShaderID, fragmentShaderID;

	vertexShaderID = LoadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = LoadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();


	std::unique_ptr<ShaderProgram> pShaderProgram(new ShaderProgram(programID, vertexShaderID, fragmentShaderID, shaderAttributeLocationBinder));

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);	

	pShaderProgram->LoadAllAttributes();	

	glLinkProgram(programID);
	glValidateProgram(programID);	

	int compileResult;
	int logLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &compileResult);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

	if (compileResult == GL_FALSE)
	{
		char* log = new char[logLength];
		glGetProgramInfoLog(programID, logLength, 0, log);
		DebugLog::Print(log, DebugLog::ERROR_LOG);
		delete log;		
		return nullptr;
	}
	else
	{
		pShaderProgram->LoadAllUniformLocations();
		return pShaderProgram;
	}
}

ShaderProgram::~ShaderProgram()
{
	Stop();
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteProgram(m_programID);
}

void ShaderProgram::Start()
{
	glUseProgram(m_programID);
}


void ShaderProgram::Stop()
{
	glUseProgram(0);
}


unsigned int ShaderProgram::LoadShader(const std::string& file, unsigned int shaderType)
{
	unsigned int shaderID = 0;
	std::string fileContent;

	if (FileHelper::LoadFile(file, fileContent))
	{
		shaderID = glCreateShader(shaderType);
		if (shaderID > 0)
		{
			DebugLog::Print("Loaded Shader File: " + file, DebugLog::DEFAULT_LOG);
			const char* pfileContent = fileContent.c_str();
			glShaderSource(shaderID, 1, &pfileContent, 0);
			glCompileShader(shaderID);

			int compileResult;
			int logLength;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
			if (compileResult == GL_FALSE)
			{
				char* compileLog = new char[logLength];
				glGetShaderInfoLog(shaderID, logLength, 0, compileLog);
				std::string errorLog = "Shader Compiler error: ";
				DebugLog::Print(errorLog + compileLog, DebugLog::ERROR_LOG);
				delete compileLog;
				glDeleteShader(shaderID);
				shaderID = 0;
			}				
		}
		else
		{
			DebugLog::Print("Shader: Could not create Shader (glCreateShader).", DebugLog::ERROR_LOG);
		}		
	}	

	return shaderID;
}


void ShaderProgram::LoadAllAttributes()
{	
	m_shaderVarBinder.BindAttributes(m_programID);		
}

void ShaderProgram::LoadAllUniformLocations()
{	
	m_shaderVarBinder.LoadAllUniformLocations(m_programID);	
}

void ShaderProgram::LoadUniformVector3f(std::string uniform, glm::vec3 vector)
{	
	m_shaderVarBinder.LoadUniformVector3(uniform, vector);		
}

void ShaderProgram::LoadUniformMatrix4f(std::string uniform, glm::mat4 matrix)
{	
	m_shaderVarBinder.LoadUniformMatrix(uniform, matrix);		
}
