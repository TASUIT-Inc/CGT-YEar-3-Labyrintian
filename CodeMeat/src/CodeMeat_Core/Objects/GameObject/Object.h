#pragma once
#include "CodeMeat_Core/Graphics/Shaders/Shader.h"

class Shader;

class Object {	//base class for all objects
private:

	virtual void Draw(Shader *shader) = 0;
	virtual void Update() = 0;

protected:
	Object() {}
	virtual ~Object() {}
};
