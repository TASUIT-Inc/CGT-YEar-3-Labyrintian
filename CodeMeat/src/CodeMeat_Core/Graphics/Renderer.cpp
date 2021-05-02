#include "Renderer.h"



bool Renderer::Init() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// glfw window creation
	// --------------------
	m_Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 0;
	}
			
	glfwMakeContextCurrent(m_Window);
	
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	centerWindow(m_Window, glfwGetPrimaryMonitor());
	// tell GLFW to capture our mouse
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 0;
	}
	//Imgui stuffs

	m_UiContext = new UIContext(m_Window);
	//m_UiContext->SetUIContext(&UIElements::PauseMenu);

	glEnable(GL_DEPTH_TEST);
	m_GBuffer = new GBuffer();

	return 1;
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Renderer::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (Instance()->firstMouse)
	{
		Instance()->lastX = xpos;
		Instance()->lastY = ypos;
		Instance()->firstMouse = false;
	}

	float xoffset = xpos - Instance()->lastX;
	float yoffset = Instance()->lastY - ypos; // reversed since y-coordinates go from bottom to top

	Instance()->lastX = xpos;
	Instance()->lastY = ypos;

	Instance()->m_Camera.ProcessMouseMovement(xoffset, yoffset);
}

void Renderer::Submit(GameObject* Object) {
	m_Objects.push_back(Object);
}

void Renderer::Submit(Light* light) {
	m_Lights.push_back(light);
}

void Renderer::Submit(Shader* shader) 
{
	m_Shaders.push_back(shader);
}


void Renderer::Draw() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ComputeShaders();
	m_GBuffer->FirstPass(m_Camera, &m_Objects);
	m_GBuffer->SecondPass(m_Camera, &m_Lights);
	m_GBuffer->RenderQuad();
	m_GBuffer->Bind();
	
	m_UiContext->Draw();

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Renderer::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (m_Instance->firstMouse)
	{
		m_Instance->lastX = xpos;
		m_Instance->lastY = ypos;
		m_Instance->firstMouse = false;
	}

	float xoffset = xpos - m_Instance->lastX;
	float yoffset = m_Instance->lastY - ypos; // reversed since y-coordinates go from bottom to top

	m_Instance->lastX = xpos;
	m_Instance->lastY = ypos;

	m_Instance->m_Camera->ProcessMouseMovement(xoffset, yoffset);
}

void Renderer::Input(float dt)
{

	if (glfwGetKey(m_Window, GLFW_KEY_P) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(FORWARD, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(BACKWARD, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(LEFT, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(RIGHT, DT);
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_RELEASE)
		m_UiContext->SetUIContext(&UIElements::PauseMenu);
	if (glfwGetKey(m_Window, GLFW_KEY_I) != GLFW_PRESS)
		m_UiContext->SetUIContext(&UIElements::PuzzleTest);



}

void Renderer::centerWindow(GLFWwindow* window, GLFWmonitor* monitor)
{
	if (!monitor)
		return;

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (!mode)
		return;

	int monitorX, monitorY;
	glfwGetMonitorPos(monitor, &monitorX, &monitorY);

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	glfwSetWindowPos(window,
		monitorX + (mode->width - windowWidth) / 2,
		monitorY + (mode->height - windowHeight) / 2);
}

void Renderer::ComputeShaders() 
{

	for (auto& v : m_Shaders) 
	{
		glm::mat4 m_Projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.001f, 100.0f);
		glm::mat4 m_View = m_Camera->GetViewMatrix();
		v->Use();
		v->SetMat4("Projection", m_Projection);
		v->SetMat4("View", m_View);
	}
}