#pragma once
#include "Collider.h"

class Ray : public Collider {	//experimental ray class defined by a pos and a direction
public:
	Ray(glm::vec3 const& pos, glm::vec3 const& Direction) : Collider()
	{
		m_Pos = pos;
		m_Normal = glm::normalize(Direction);

	}
	glm::vec3 m_Pos, m_Normal;
};

