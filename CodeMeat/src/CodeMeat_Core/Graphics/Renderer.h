#ifndef __Renderer__
#define __Renderer__


#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Objects/GameObject/GameObject.h"
#include "CodeMeat_Core/Graphics/Camera/Camera.h"
#include "CodeMeat_Core/Deps/Commons.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat_Core/Graphics/FrameBuffers/GBuffer.h"
#include "CodeMeat_Core/Graphics/UI/imgui.h"
#include "CodeMeat_Core/Graphics/UI/imgui_impl_glfw.h"
#include "CodeMeat_Core/Graphics/UI/imgui_impl_opengl3.h"
#include "CodeMeat_Core/Graphics/UI/UIHandler.h"


class GameObject;
class Camera;

class Renderer
{
public:
	bool Init();
	void Draw();

	void Submit(GameObject* Object);
	void Submit(Light* light);

	void processInput(float DT);
	
	static Renderer* Instance() {

		if (m_Instance == 0) {
			m_Instance = new Renderer();
			return m_Instance;
		}
		return m_Instance;
	}

	Camera* GetCamera() { return &m_Camera; }
	GLFWwindow* GetWindow() { return m_Window; }
private:
	GLFWwindow* m_Window;
	Camera m_Camera = Camera(glm::vec3(0.0f, 2.0f, 0.0f));

	std::vector<GameObject*> m_Objects;
	std::vector<Light*> m_Lights;
	GBuffer* m_GBuffer;
	
	bool* isOpen = NULL;
	UIHandler* UIManager;
	//const char* glsl_version = "#version 130";


	bool firstMouse;
	double lastX, lastY;
	
	static Renderer* m_Instance;

	Renderer() {}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	virtual ~Renderer() {}
};
typedef Renderer REngine;
#endif //!__Renderer__