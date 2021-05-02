#include "EulerSolver.h"

void EulerSolver::solver(Kinematics* Params, float dt) 
{
	glm::vec3 newpos = dt * Params->m_Vel;
	Params->m_Transform.Translate(newpos);

	Params->m_Vel += dt * Params->m_Accel;

	Params->m_Accel = Params->GetResultant() * Params->GetInverseMass();

}