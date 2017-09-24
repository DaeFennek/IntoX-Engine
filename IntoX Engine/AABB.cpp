#include "AABB.h"


CAABB::CAABB()
{
}


CAABB::~CAABB()
{
}


glm::vec3 CAABB::GetMax()
{
	return m_vecMax;
}

glm::vec3 CAABB::GetMin()
{
	return m_vecMin;
}

bool CAABB::IntersectsWith(class CAABB& aabb)
{
	return( m_vecMax.x > aabb.GetMin().x &&
		m_vecMin.x < aabb.GetMax().x &&
		m_vecMax.y > aabb.GetMin().y &&
		m_vecMin.y < aabb.GetMax().y &&
		m_vecMax.z > aabb.GetMin().z &&
		m_vecMin.z < aabb.GetMax().z );
}
