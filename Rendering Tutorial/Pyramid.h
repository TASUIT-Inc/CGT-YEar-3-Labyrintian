#pragma once
#include "Shape.h"
class Pyramid :public Shape
{
public:
	Pyramid(float vertices[]);
private:
	void Draw(glm::vec3 pos, glm::vec3 scale);
protected:
};

