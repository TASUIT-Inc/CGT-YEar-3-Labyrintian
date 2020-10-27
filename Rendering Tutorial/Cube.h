#pragma once
#include "Shape.h"

class Cube :public Shape
{
public:
	Cube(float vertices[]);
private:
	void Draw(glm::vec3 pos, glm::vec3 scale);
protected:

};

