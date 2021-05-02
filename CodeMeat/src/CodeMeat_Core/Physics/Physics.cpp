#include "Physics.h"

bool Physics::Init() 
{
	m_Solver = new EulerSolver();
	m_Resolver = new ContactSolver();
	return true;
}

void Physics::Update(Camera* camera, std::vector<GameObject*> &Objs,float dt)
{
	m_Solver->Integrate(Objs, dt);
	for (std::vector<GameObject*>::iterator i = Objs.begin(); i < Objs.end(); i++) 
	{
		(*i)->Update();
	}
	GetCollisionData(camera, Objs);
	/*while (!m_CollisionData.empty()) 
	{
		std::unique_ptr<CollisionData>& data = m_CollisionData.back();
		m_Resolver->SetMaxIterations(data->m_MaxContatcs - data->m_ContactAmount);
		if (data->m_Contacts != nullptr) 
		{
			m_Resolver->ResolveContacts(data->m_Contacts, data->m_MaxContatcs, dt);
			m_CollisionData.pop_back();
		}
	}*/
}

void Physics::GetCollisionData(Camera* camera, std::vector<GameObject*> &Objs) 
{
	for (std::vector<GameObject*>::iterator i = Objs.begin(); i < Objs.end(); i++) 
	{
		CollisionData* data = CollisionManager::CheckCollisions(camera, (*i));
		if (data != nullptr) 
		{
			m_CollisionData.push_back(std::unique_ptr<CollisionData>(data));
		}
	}
}
