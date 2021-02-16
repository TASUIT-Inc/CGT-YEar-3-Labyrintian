#ifndef __Renderer__
#define __Renderer__


#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Objects/GameObject/GameObject.h"
#include "CodeMeat_Core/Graphics/Camera/Camera.h"
#include "CodeMeat_Core/Deps/Commons.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat_Core/Graphics/FrameBuffers/GBuffer.h"


class GameObject;
class Camera;

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
	Shader* GetShader(const char* Tag) { return &m_Shaders[Tag]; }


private:
	GLFWwindow* m_Window;
	Camera m_Camera;
	VertexData* m_Buffer;

	glm::mat4 m_Projection, m_View;

	std::map<const char*, Shader > m_Shaders;

	std::deque<GameObject*> m_RenderQueue;
	GBuffer* m_GBuffer;


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