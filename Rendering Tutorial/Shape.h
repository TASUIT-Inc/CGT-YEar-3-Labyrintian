#pragma once
#include <glm/glm.hpp>
class Shape
{
private:
	virtual void Draw() = 0;
protected:
	Shape() {}
	virtual ~Shape() {}
};

