#include "Entity.h"
#include "MathHelper.h"

Entity::Entity(class Model* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : m_model(model), m_position(position), m_rotation(rotation), m_scale(scale) {}


Entity::~Entity()
{
}

std::string Entity::GetPositionAsString()
{
	auto position = GetPosition();
	return std::string("X: " + std::to_string(position.x) + " Y: " + std::to_string(position.y) + " Z: " + std::to_string(position.z));
}

class Model* Entity::GetModel() const
{
	return m_model;
}

glm::vec3 Entity::GetPosition() const
{
	return m_position;
}

glm::vec3 Entity::GetRotation() const
{
	return m_rotation;
}

glm::vec3 Entity::GetScale() const
{
	return m_scale;
}

glm::mat4 Entity::GetModelMatrix() const
{
	return CMathHelper::CreateModelMatrix(m_position, m_rotation, m_scale);
}

void Entity::UpdatePosition(glm::vec3 position)
{
	m_position += position;
}

void Entity::SetPosition(glm::vec3 position)
{
	m_position = position;
}

void Entity::UpdateRotation(glm::vec3 rotation)
{
	m_rotation += rotation;
}

void Entity::SetRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}