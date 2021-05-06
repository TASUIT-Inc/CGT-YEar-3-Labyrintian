#ifndef __Renderer__
#define __Renderer__


#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Objects/GameObject/GameObject.h"
#include "CodeMeat_Core/Graphics/Camera/Camera.h"
#include "CodeMeat_Core/Deps/Commons.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat_Core/Graphics/FrameBuffers/GBuffer.h"

#include "CodeMeat_Core/Graphics/UI/UIContext.h"
#include "CodeMeat_Core/Graphics/UI/UIElements.h"


class GameObject;
class Camera;
class UIContext;
		
class Renderer
{
public:
	bool Init();
	void Draw();
	void Clean();

	void ComputeShaders();

	void Submit(GameObject* Object);
	void Submit(Light* light);		//Submit functions for GameObjects, Lights and Shaders
	void Submit(Shader* shader);

	static Renderer* Instance() {

		if (m_Instance == 0) {
			m_Instance = new Renderer();
			return m_Instance;
		}
		return m_Instance;
	}

	//Public Getters
	Camera* GetCamera() { return m_Camera; }
	GLFWwindow* GetWindow() { return m_Window; }
	std::vector<GameObject*>& GetObjectListRef() { return m_Objects; }
	UIContext* GetContext() const { return m_UiContext; }


	GameObject* FindObjectWithTag(const char* tag) 
	{
		for (auto* G : m_Objects)
		{
			if (G->GetTag() == tag) {	//For each gameobject if and Objects tag == desired tag return that object, else return a nullptr
				return G;
			}

		}
		return nullptr;
	}

	void Input(float dt);
private:
	GLFWwindow* m_Window;	//Game Window
	Camera* m_Camera = new Camera(glm::vec3(0.0f, 0.5f, 0.0f));		//The camera
	UIContext* m_UiContext;	//Context for managing Ui Elements

	bool m_KeyPressed = false;	//KeyPressed State

	std::vector<GameObject*> m_Objects;
	std::vector<Shader*> m_Shaders;		//Object Vectors for Drawing
	std::vector<Light*> m_Lights;
	GBuffer* m_GBuffer;


	bool firstMouse = true;
	double lastX = 0.0f, lastY = 0.0f;

	static Renderer* m_Instance;

	Renderer() {}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);			//Callback functions
	void centerWindow(GLFWwindow* window, GLFWmonitor* monitor);
			

	virtual ~Renderer() {}
};
typedef Renderer REngine;
#endif //!__Renderer__