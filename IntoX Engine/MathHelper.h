#pragma once

#include <glm\mat4x4.hpp>
#include "Camera.h"

class CMathHelper
{
public:
	CMathHelper();
	~CMathHelper();

	static glm::mat4 GetIdentityMatrix();
	static glm::mat4 CreateViewMatrix(const class Camera& camera);
	static glm::mat4 CreateModelMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
	static glm::mat4 CreateProjectionMatrix(float rFov, float width, float height, float nearPlane, float farPlane);

};

