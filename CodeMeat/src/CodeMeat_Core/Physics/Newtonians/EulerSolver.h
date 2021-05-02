#pragma once
#include "Solver.h"

class EulerSolver : public Solver 
{
private:
	virtual void solver(Kinematics* params, float dt);
};

