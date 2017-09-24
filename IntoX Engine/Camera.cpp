#include "Camera.h"
#include "MathHelper.h"

Camera::Camera()
{
	
}


Camera::~Camera()
{
}

float Camera::GetPitch() const
{
	return m_pitch;
}

float Camera::GetYaw() const
{
	return m_yaw;
}

float Camera::GetRoll() const
{
	return m_roll;
}

glm::vec3 Camera::GetPosition() const
{
	return m_position;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return CMathHelper::CreateViewMatrix(*this);
}

void Camera::UpdatePosition(glm::vec3 position)
{
	m_position += position;
}

void Camera::SetPosition(glm::vec3 position)
{
	m_position = position;
}

void Camera::SetYaw(float value)
{
	m_yaw = value;
}

void Camera::SetPitch(float value)
{
	m_pitch = value;
}

void Camera::UpdateYaw(float value)
{
	m_yaw += value;
}

void Camera::UpdatePitch(float value)
{
	m_pitch += value;
}
