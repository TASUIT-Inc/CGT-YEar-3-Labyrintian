#pragma once
#include "Shape.h"
class Sphere :public Shape
{
public:
	Sphere(float vertices[], int Devisions);
private:
	void Draw(glm::vec3 pos, glm::vec3 scale);

	int m_Devisions;
protected:
};

