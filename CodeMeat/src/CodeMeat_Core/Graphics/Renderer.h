#ifndef __Renderer__
#define __Renderer__


#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Objects/GameObject/GameObject.h"
#include "CodeMeat_Core/Graphics/Camera/Camera.h"
#include "CodeMeat_Core/Deps/Commons.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat_Core/Graphics/FrameBuffers/GBuffer.h"
#include "CodeMeat_Core/Objects/Player.h"


class GameObject;
class Camera;
		
	class Renderer
		{
		public:
			bool Init();
			void Draw();

			void ComputeShaders();

			void Submit(GameObject* Object);
			void Submit(Light* light);
			void Submit(Shader* shader);

			static Renderer* Instance() {

				if (m_Instance == 0) {
					m_Instance = new Renderer();
					return m_Instance;
				}
				return m_Instance;
			}

			Camera* GetCamera() { return m_Camera; }
			GLFWwindow* GetWindow() { return m_Window; }
			std::vector<GameObject*>& GetObjectListRef() { return m_Objects; }

			void Input(float dt);
		private:
			GLFWwindow* m_Window;
			Camera* m_Camera = new Camera(glm::vec3(0.0f, 0.5f, 0.0f));

			std::vector<GameObject*> m_Objects;
			std::vector<Shader*> m_Shaders;
			std::vector<Light*> m_Lights;
			GBuffer* m_GBuffer;


			bool firstMouse = true;
			double lastX = 0.0f, lastY = 0.0f;

			static Renderer* m_Instance;

			Renderer() {}

			static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
			static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
			void centerWindow(GLFWwindow* window, GLFWmonitor* monitor);
			

			virtual ~Renderer() {}
		};
		typedef Renderer REngine;
#endif //!__Renderer__