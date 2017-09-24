#pragma once

#include <map>
#include <vector>
#include <glm\mat4x4.hpp>
#include "Model.h"
#include "Entity.h"
#include "ShaderProgram.h"
#include "IntoXWindow.h"
#include "OpenGLRenderContext.h"

#define FOV 45.f
#define NEAR .1f
#define FAR 500.0f

class OpenGLMasterRenderer
{
public:
	OpenGLMasterRenderer(const class OpenGLRenderContext* openGLRenderContext);
	~OpenGLMasterRenderer();
	
	void AddEntity(class Entity& entity);
	void ClearRenderList();
	void Render(class ShaderProgram& shader);
	void ClearBuffers();

	glm::mat4& GetProjectionMatrix() const;

private:
	void PrepareRenderList(class ShaderProgram& shader);
	void PrepareModel(class Model& model);
	void FinishModel();

private:
	std::map<class Model*, std::vector<class Entity*>> m_RenderList;
	glm::mat4 m_ProjectionMatrix;	
	const class OpenGLRenderContext* m_OpenGLRenderContextPtr;

};

