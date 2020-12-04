#pragma once
#include "LoaderParams.h"
class Object {
private:

	virtual void Draw() = 0;
	virtual void Update() = 0;

protected:
	Object(LoaderParams Params) {}
	virtual ~Object() {}
};
