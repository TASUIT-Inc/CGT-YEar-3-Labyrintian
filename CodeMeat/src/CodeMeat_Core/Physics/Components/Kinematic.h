#pragma once
#include "Component.h"

#define FRICTION 0.8
#define GRAVITY glm::vec3(0.0f, -9.8f, 0.0f)

class Kinematic : public Component {
public:

	//Getters
	glm::vec3 GetVel() { return m_Vel; }
	glm::vec3 GetVel() { return m_Acc; }

	float GetMomentum() { return m_Mass * m_Vel.length(); }
	float GetMass() { return m_Mass; }
	//Setters
	void SetVel(glm::vec3 newvel) { m_Vel = newvel; }
	void SetAccel(glm::vec3 newacc) { m_Acc = newacc; }
	void SetMass(float newmass) { m_Mass = newmass; }
	//pushers
	void PushVel(glm::vec3 VelAdd) { m_Vel += VelAdd; }
	void PushAccel(glm::vec3 AccelAdd) { m_Acc += AccelAdd; }

private:
	glm::vec3 m_Vel, m_Acc;
	float m_Mass; //using Pm for momentum becauses momentum is too long for a variable name IMO, also not shortening it to m_Mom

};

