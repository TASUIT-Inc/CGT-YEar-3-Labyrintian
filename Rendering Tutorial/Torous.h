#pragma once
#include "Shape.h"
class Torous :public Shape
{
public:
	Torous(float vertices[], glm::vec2 devisions);
private:
	void Draw(glm::vec3 pos, glm::vec3 scale);
	glm::vec2 m_Devisions;
protected:
};

