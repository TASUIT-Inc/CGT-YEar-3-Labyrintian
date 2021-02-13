#ifndef __Engine__
#define __Engine__

#include "CodeMeat.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Engine
{
public:
	bool init();
	void Render();
	void Draw();
	void Update();
	void Clean();

	bool GetState() { return EngineState; }

	static Engine* Instance() {
		if (m_Instance == 0) {
			m_Instance = new Engine();
			return m_Instance;
		}
		return m_Instance;
	}

private:
	bool EngineState;

	static Engine* m_Instance;
};
typedef Engine GameEngine;
#endif //!__Engine__
