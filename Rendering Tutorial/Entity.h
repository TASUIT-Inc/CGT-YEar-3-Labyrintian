#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <btBulletDynamicsCommon.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Model.h"


class Entity
{
public:

private:
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	Entity() {}
	virtual ~Entity() {}
};

