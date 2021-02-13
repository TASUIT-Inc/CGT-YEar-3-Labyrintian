#ifndef __Physics__
#define __Physics__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Physics
{
public:

	bool Init() { return true; }

	static Physics* Instance() {
		if (m_Instance == 0) {
			m_Instance = new Physics();
			return m_Instance;
		}
		return m_Instance;
	}

private:

	static Physics* m_Instance;
	Physics() {}
	virtual ~Physics() {}

};
typedef Physics PEngine;
#endif //!__Renderer__
