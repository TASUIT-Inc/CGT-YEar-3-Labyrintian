#include "Contacts.h"

glm::vec3 Contacts::ComputeImpulse(float dt) 
{
	float seperatingVel = ComputeSeperatingVel();

	if (seperatingVel > 0) 
	{
		return glm::vec3(0);
	}

	float NewSepVel = -seperatingVel * (1 + m_Restitution) - ResolveRestingContact(dt);
	if (NewSepVel < 0) 
	{
		NewSepVel = 0;
	}

	float totalInvMass = m_Objects[0]->GetKinematics()->GetInverseMass();
	if (m_Objects[1]) 
	{
		totalInvMass += m_Objects[1]->GetKinematics()->GetInverseMass();
	}
	if (totalInvMass < 0) 
	{
		return glm::vec3(0);
	}

	float ImpulseLength = NewSepVel / totalInvMass;

	return ImpulseLength * m_CNorm;

}

void Contacts::ApplyImpulse(glm::vec3 impulse) 
{
	if (glm::length(impulse) != 0) 
	{
		m_Objects[0]->GetKinematics()->m_Vel += impulse * m_Objects[0]->GetKinematics()->GetInverseMass();
		if (m_Objects[1]) 
		{
			m_Objects[1]->GetKinematics()->m_Vel -= impulse * m_Objects[1]->GetKinematics()->GetInverseMass();
		}
	}
}

float Contacts::ResolveRestingContact(float dt) 
{
	glm::vec3 TotalAccel = m_Objects[0]->GetKinematics()->m_Accel;

	if (m_Objects[1]) 
	{
		TotalAccel += m_Objects[1]->GetKinematics()->m_Accel;
	}

	float AccelSepVel = glm::dot(TotalAccel, m_CNorm) * dt;

	if (AccelSepVel < 0) 
	{
		return AccelSepVel;
	}
	else 
	{
		return 0;
	}
}

void Contacts::ResolveInterPenetration(float dt) 
{
	if (m_Depth < 0) 
	{
		return;
	}

	float totalInvMass = m_Objects[0]->GetKinematics()->GetInverseMass();
	if (m_Objects[1])
	{
		totalInvMass += m_Objects[1]->GetKinematics()->GetInverseMass();
	}
	if (totalInvMass < 0)
	{
		return;
	}

	glm::vec3 MovePerUnitMass = m_CNorm * (-m_Depth / totalInvMass);

	glm::vec3 translation = 0.5f * MovePerUnitMass * m_Objects[0]->GetKinematics()->GetInverseMass();

	m_Objects[0]->GetKinematics()->m_Transform.Translate(translation);
	m_Objects[0]->GetKinematics()->m_Vel += 0.5f * glm::dot((MovePerUnitMass * m_Objects[0]->GetKinematics()->GetInverseMass()) / dt, m_CNorm);

	if (m_Objects[1]) 
	{
		translation = 0.5f * MovePerUnitMass * m_Objects[1]->GetKinematics()->GetInverseMass();
		m_Objects[1]->GetKinematics()->m_Transform.Translate(translation);
		m_Objects[1]->GetKinematics()->m_Vel += 0.5f * glm::dot((MovePerUnitMass * m_Objects[1]->GetKinematics()->GetInverseMass()) / dt, m_CNorm);
	}

}

float Contacts::ComputeSeperatingVel() const 
{
	glm::vec3 RelVel = m_Objects[0]->GetKinematics()->m_Vel;
	if (m_Objects[1]) 
	{
		RelVel -= m_Objects[1]->GetKinematics()->m_Vel;
	}
	return glm::dot(RelVel, m_CNorm);
}

void Contacts::ResolveContacts(float dt) 
{
	ResolveVelocity(dt);
	ResolveInterPenetration(dt);
}