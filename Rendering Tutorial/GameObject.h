#pragma once
#include "Entity.h"
#include "Shape.h"



class GameObject : public Entity
{
public:
	GameObject(glm::vec3 Pos, glm::vec3 Scale, Model* model, std::string Vertexshader = 0, std::string FragmentShader = 0, std::string GeometryShader = 0);

	GameObject(glm::vec3 Pos, glm::vec3 Scale, Shape* shape, std::string Vertexshader = 0, std::string FragmentShader = 0, std::string GeometryShader = 0);

	glm::vec3 GetPos() { return m_Pos; }
	glm::vec3 GetScalse() { return m_Scale; }

private:
	
	Shape* m_Shape;

	glm::vec3 m_Pos;
	glm::vec3 m_Scale;

	glm::mat4 m_ModelMat = glm::mat4(1.0f);

	Model* m_Model;

	unsigned int VAO, VBO;

protected:

};

