#pragma once
#include "Collider.h"

class BoundingBox : public Collider {	
public:
	BoundingBox(glm::vec3 pos, glm::vec3 extents) : Collider() // constructor for bounding box, BB's are expressed with center + extents
	{
		m_Pos = pos;
		m_Extents = extents;

	}

	void Update(Transform &transform);
	void SetExtents(glm::vec3 newExtents) { m_Extents = newExtents; }
	glm::vec3 m_Pos, m_Extents;
};

