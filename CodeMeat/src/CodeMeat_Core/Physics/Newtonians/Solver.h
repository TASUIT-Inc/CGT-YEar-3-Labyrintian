#pragma once
#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "Kinematics.h"
#include "CodeMeat_Core/Objects/GameObject/GameObject.h"
#include "CodeMeat_Core/Graphics/Camera/Camera.h"

class Solver 
{
public:
	void Integrate(std::vector<GameObject*>& Objs, float dt);
private:
	virtual void solver(Kinematics* obj, float dt) = 0;
protected:
	Solver() {}
	virtual ~Solver() {}

};

