#pragma once

#include <glm\vec3.hpp>

class CAABB
{
public:
	CAABB();
	~CAABB();

	glm::vec3 GetMax();
	glm::vec3 GetMin();

	bool IntersectsWith(class CAABB& aabb);

	
private:
	glm::vec3 m_vecMax, m_vecMin;

};

