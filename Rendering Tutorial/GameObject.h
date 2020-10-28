#pragma once
#include "Entity.h"
#include "Shape.h"



class GameObject : public Entity
{
public:
	GameObject(glm::vec3 Pos, glm::vec3 Scale, Model* model, const char* Vertexshader = nullptr, const char* FragmentShader = nullptr, const char* GeometryShader = nullptr, const char* texture = nullptr);


	void Draw();

	glm::vec3 GetPos() { return m_Pos; }
	glm::vec3 GetScalse() { return m_Scale; }

	unsigned int loadTexture(char const* path);

private:

	glm::vec3 m_Pos;
	glm::vec3 m_Scale;

	glm::mat4 m_ModelMat = glm::mat4(1.0f);

	Model* m_Model;

	Shader m_Shader;

protected:

};

