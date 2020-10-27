#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <btBulletDynamicsCommon.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Player.h"

#include <iostream>



class Game
{
public:
	Game();

	int init(const char* title, int Width, int Height);
	void Update();
	void Draw();
	void Clean();

	void framebuffer_size_callback(int width, int height);
	void mouse_callback(double xpos, double ypos);
	void scroll_callback(double xoffset, double yoffset);
	void processInput();

	GLFWwindow* GetWindow() { return m_Window; }
	Camera* GetCamera() { return m_Camera; }

	static Game* Instance() {
		if(m_Instance == 0) {
			m_Instance = new Game();
			return m_Instance;
		}
		return m_Instance;
	}

	Camera* m_Camera;
	Player* m_Player;
	GLFWwindow* m_Window;
private:
	virtual ~Game(){}
	bool firstMouse = true;

	float lastX;
	float lastY;

	unsigned int SCR_WIDTH = 0;
	
	unsigned int SCR_HEIGHT = 0;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	static Game* m_Instance;
protected:

};

