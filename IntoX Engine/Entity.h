#pragma once
#include "Model.h"
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class Entity
{
public:
	Entity(class Model* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Entity();

	class Model* GetModel() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	glm::mat4 GetModelMatrix() const;

	void UpdatePosition(glm::vec3 position);
	void SetPosition(glm::vec3 position);

	void UpdateRotation(glm::vec3 rotation);
	void SetRotation(glm::vec3 rotation);

	std::string GetPositionAsString();

protected:
	class Model* m_model = NULL;
	glm::vec3 m_position, m_rotation, m_scale;
};

