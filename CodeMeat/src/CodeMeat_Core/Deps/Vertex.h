#pragma once
#include "CodeMeat_Core/Deps/Math.h"

struct Vertex {		//a simple vertex class used throught the engine
	glm::vec3 m_Pos;

	glm::vec3 m_Norm;

	glm::vec2 m_TexCoords;

	glm::vec3 m_Tangent{0,0,0};

	glm::vec3 m_Bitangent{0,0,0};
};
