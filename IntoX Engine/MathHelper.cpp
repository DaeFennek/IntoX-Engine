#include "MathHelper.h"
#include <glm\gtc\matrix_transform.hpp>

CMathHelper::CMathHelper()
{
}


CMathHelper::~CMathHelper()
{
}

glm::mat4 CMathHelper::GetIdentityMatrix()
{
	return glm::mat4(1.0f);
}

glm::mat4 CMathHelper::CreateViewMatrix(const class Camera& camera)
{
	glm::mat4 viewMatrix(1.0f);
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.GetPitch()), glm::vec3(1.0f, .0f, .0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.GetYaw()), glm::vec3(.0f, 1.0f, .0f));
	glm::vec3 cameraPosition = camera.GetPosition();
	glm::vec3 negativeCameraPosition(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z);
	viewMatrix = glm::translate(viewMatrix, negativeCameraPosition);
	return viewMatrix;
}

glm::mat4 CMathHelper::CreateModelMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 modelMatrix(1.0f);
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, .0f, .0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(.0f, 1.0f, .0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(.0f, 0.f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, scale);
	return modelMatrix;
}

glm::mat4 CMathHelper::CreateProjectionMatrix(float rFov, float width, float height, float nearPlane, float farPlane)
{
	return glm::perspective(glm::radians(rFov), width / height, nearPlane, farPlane);
}