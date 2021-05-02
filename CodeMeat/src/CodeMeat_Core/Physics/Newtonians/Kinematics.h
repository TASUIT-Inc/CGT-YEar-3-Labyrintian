#pragma once
#include "CodeMeat_Core/Deps/Math.h"
#include "Transform.h"

class Kinematics
{
public:

	Kinematics(float Mass, glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f, 0.0f, 0.0f), float restit = 0) : m_Vel(vel), m_Restitution(restit), m_ResultantForce(glm::vec3(0)), m_Accel(glm::vec3(0)), m_InverseMass(INFINITY) 
	{
		SetInverseMass(Mass);
		m_Transform =Transform();
		m_Transform.Translate(pos);
	}
	glm::vec3 m_Vel, m_Accel;

	Transform m_Transform;

	virtual ~Kinematics() {}

	//Getters
	float GetMass() const { return 1.0f / m_InverseMass; }
	float GetInverseMass() const { return m_InverseMass; }
	float GetRestitution() const { return m_Restitution; }
	glm::vec3 GetResultant() const { return m_ResultantForce; }
	//Setters
	void SetInverseMass(float mass) { m_InverseMass = 1.0f / mass; }
	void SetRestitution(float restit) { m_Restitution = Math::Clamp(restit); }

	//Adders
	void AddForce(glm::vec3& force) { m_ResultantForce += force; }

	void ClearForce() { m_ResultantForce = glm::vec3(0); }

private:
	float m_InverseMass;
	glm::vec3 m_ResultantForce;
	float m_Restitution;
};

