#pragma once
#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Deps/Output.h"

#include"CodeMeat_Core/Objects/GameObject/GameObject.h"
#include "CodeMeat_Core/Graphics/Camera/Camera.h"

class GameObject;

class Contacts 
{
public:
	Contacts() : m_Restitution(0), m_Depth(0) {}

	//Setters
	void SetContactNorm(glm::vec3 ContactNorm) { m_CNorm = ContactNorm; }
	void SetDepth(int Depth) 
	{ 
		if(Depth <0)
		{
			m_Depth = Depth;
		}
		else 
		{
			Depth = 0;
		}
	}
	void SetRestitution(int Restitution) { m_Restitution = Restitution; }

	//Getters
	glm::vec3 GetContactNorrmal() const { return m_CNorm; }


	//Adders
	void AddObjects(std::vector<GameObject*> Objs) { m_Objects = Objs; }

	//computers
	float ComputeSeperatingVel() const;
	
	//resolvers
	void ResolveInterPenetration(float dt);
	void ResolveContacts(float dt);
	
	virtual ~Contacts() {}

private:

	
	std::vector<GameObject*> m_Objects;

	glm::vec3 m_CPos, m_CNorm;

	int m_Restitution, m_Depth;
	
	//computers
	glm::vec3 ComputeImpulse(float dt);
	void ApplyImpulse(glm::vec3 impulse);

	//resolvers
	void ResolveVelocity(float dt) { ApplyImpulse(ComputeImpulse(dt)); }
	float ResolveRestingContact(float dt);

};

