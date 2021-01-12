#pragma once
#include "Camera.h"
class Light
{
public:

	Light(glm::vec3 color, glm::vec3 Direction);

	Light(glm::vec3 pos, glm::vec3 color, float Linear, float Quadratic); //Point Light

	Light(glm::vec3 pos, glm::vec3 color, glm::vec3 direction, float CTheta); //Spot Light

	glm::vec3 GetPos() { return m_Pos; }

	glm::vec3 GetColour() { return m_Colour; }

	glm::vec3 GetDir() { return m_Direction; }


	float GetLinear() { return m_Linear; }

	float GetQuadratic() { return m_Quadratic; }

	float GetTheta() { return m_Theta; }

	void Draw() {}

	void Update() {}

	int GetType() { return type; }

private:

	glm::vec3 m_Direction, m_Pos, m_Colour;

	float m_Linear, m_Quadratic, m_Theta;

	int const type;

};

