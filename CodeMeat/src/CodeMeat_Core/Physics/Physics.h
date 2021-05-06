#ifndef __Physics__
#define __Physics__

#include "CodeMeat_Core/Graphics/Renderer.h"
#include "CodeMeat_Core/Physics/Newtonians/EulerSolver.h"
#include "CodeMeat_Core/Physics/Collisions/ContactSolver.h"
#include "CodeMeat_Core/Physics/Collisions/CollisionData.h"
#include "CodeMeat_Core/Physics/Collisions/CollisionManager.h"

class Physics
{
public:

	bool Init();
	void Update(Camera* camera, std::vector<GameObject*> &Objs, float dt);
	void Clean() { delete m_Solver, m_Resolver; }
	void GetCollisionData(Camera* camera, std::vector<GameObject*> &Objs);

	static Physics* Instance() {
		if (m_Instance == 0) {
			m_Instance = new Physics();
			return m_Instance;
		}
		return m_Instance;
	}

private:

	static Physics* m_Instance;
	Solver* m_Solver;
	ContactSolver* m_Resolver;
	std::vector<std::unique_ptr<CollisionData>> m_CollisionData;


	Physics() {}
	virtual ~Physics() {}

};
typedef Physics PEngine;
#endif //!__Renderer__
