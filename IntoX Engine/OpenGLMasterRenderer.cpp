#include "OpenGLMasterRenderer.h"
#include <GL/glew.h>
#include "MathHelper.h"

OpenGLMasterRenderer::OpenGLMasterRenderer(const class OpenGLRenderContext* openGLRenderContextPtr) : m_OpenGLRenderContextPtr(openGLRenderContextPtr)
{
}


OpenGLMasterRenderer::~OpenGLMasterRenderer()
{
	
}

void OpenGLMasterRenderer::AddEntity(Entity& entity)
{
	Model* pModel = entity.GetModel();
	if (pModel)
	{
		auto mapIterator = m_RenderList.find(pModel);
		if (mapIterator == m_RenderList.end())
		{
			std::vector<Entity*> entityVector = { &entity };
			m_RenderList.insert(std::make_pair(pModel, entityVector));
		}
		else
		{
			mapIterator->second.push_back(&entity);
		}
	}	
}

void OpenGLMasterRenderer::ClearRenderList()
{
	// we only clear the list. The entities itself should be destroyed in the entity manager!
	m_RenderList.clear();
}

void OpenGLMasterRenderer::Render(class ShaderProgram& shader)
{
	PrepareRenderList(shader);
			
	for (auto& entry : m_RenderList)
	{
		auto modelPtr = entry.first;
		PrepareModel(*modelPtr);		
		for (auto entity : entry.second)
		{
			shader.LoadUniformMatrix4f("transformationMatrix", entity->GetModelMatrix());
			glDrawElements(GL_TRIANGLES, modelPtr->GetVerticesCount(), GL_UNSIGNED_INT, 0);
		}
		FinishModel();
	}	
}

void OpenGLMasterRenderer::PrepareRenderList(class ShaderProgram& shader)
{
	m_ProjectionMatrix = CMathHelper::CreateProjectionMatrix(FOV, m_OpenGLRenderContextPtr->GetWidth(), m_OpenGLRenderContextPtr->GetHeight(), NEAR, FAR);
	shader.LoadUniformMatrix4f("projectionMatrix", m_ProjectionMatrix);

	glEnable(GL_DEPTH_TEST);	
}

void OpenGLMasterRenderer::PrepareModel(class Model& model)
{
	glBindVertexArray(model.GetVao());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	if (model.HasTexture())
	{
		glBindTexture(GL_TEXTURE_2D, model.GetTextureID());
	}
}

void OpenGLMasterRenderer::FinishModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}


void OpenGLMasterRenderer::ClearBuffers()
{
	glClearColor(0.0f, 0.f, 0.f, 0.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

glm::mat4& OpenGLMasterRenderer::GetProjectionMatrix() const
{
	return CMathHelper::CreateProjectionMatrix(FOV, m_OpenGLRenderContextPtr->GetWidth(), m_OpenGLRenderContextPtr->GetHeight(), NEAR, FAR);
}
