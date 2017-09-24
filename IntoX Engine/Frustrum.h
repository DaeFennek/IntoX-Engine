#pragma once

#include "MathHelper.h"

class CFrustrum
{
public:
	CFrustrum();
	~CFrustrum();

	void CreateFrustrum(glm::mat4 &projectionMtx, glm::mat4 &modelViewMtx);
	bool CubeInFrustum(float x1, float y1, float z1, float x2, float y2, float z2);
	bool PointInFrustum(float x, float y, float z);

private:
	float m_Frustum[6][4];
};

