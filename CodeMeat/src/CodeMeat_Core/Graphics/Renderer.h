#ifndef __Renderer__
#define __Renderer__

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <map>
#include <vector>

#include "CodeMeat_Core/Objects/GameObject/GameObject.h"

#define RENDER_MAX_VERTICES		50000
#define RENDER_VERTEX_STRIDE	sizeof(Vertex)
#define RENDER_BUFFER_SIZE		RENDER_MAX_VERTICES * RENDER_VERTEX_STRIDE

class Renderer
{
public:
	bool Init();
	bool Render();
	void GenBuffer();

	void Begin();
	void Submit(GameObject* Object);
	void End();
	void Flush();
	
	static Renderer* Instance() {
		if (m_Instance == 0) {
			m_Instance = new Renderer();
			return m_Instance;
		}
		return m_Instance;
	}

	Camera* GetCamera() { return &m_Camera; }
	void AddShader(const char* Identifier, const char* VertexPath, const char* FragmentPath, const char* GeometryPath = nullptr);


private:
	GLFWwindow* m_Window;
	Camera m_Camera;
	VertexData* m_Buffer;

	glm::mat4 m_Projection, m_View;

	std::map<const char*, Shader > m_Shaders;


	bool firstMouse;
	double lastX, lastY;

	unsigned int m_VAO, m_VBO;
	
	static Renderer* m_Instance;

	Renderer() {}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	virtual ~Renderer() {}

};
typedef Renderer REngine;
#endif //!__Renderer__