#pragma once

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	float GetPitch() const;
	float GetYaw() const;
	float GetRoll() const;

	glm::vec3 GetPosition() const;
	glm::mat4 GetViewMatrix() const;

	void UpdatePosition(glm::vec3 position);
	void SetPosition(glm::vec3 position);

	void SetYaw(float value);
	void SetPitch(float value);

	void UpdateYaw(float value);
	void UpdatePitch(float value);

private:
	float m_pitch = 0.0f, m_yaw = 0.0f, m_roll = 0.0f;
	glm::vec3 m_position;
};

