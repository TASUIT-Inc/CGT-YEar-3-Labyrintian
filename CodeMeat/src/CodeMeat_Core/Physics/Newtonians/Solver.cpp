#include "Solver.h"

void Solver::Integrate(std::vector<GameObject*> &Objs, float dt) 
{
	for (std::vector<GameObject*>::iterator i = Objs.begin(); i < Objs.end(); i++) 
	{
		Kinematics* params = (*i)->GetKinematics();
		solver(params, dt);
	}
}



