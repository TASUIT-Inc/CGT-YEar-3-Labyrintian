#pragma once

class Object {
private:

	virtual void Draw() = 0;
	virtual void Update() = 0;

protected:
	Object() {}
	virtual ~Object() {}
};
