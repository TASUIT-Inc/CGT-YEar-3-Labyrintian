#include "Renderer.h"

bool Renderer::Init(){
	
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

	// tell GLFW to capture our mouse
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 0;
	}

	glEnable(GL_DEPTH_TEST);

	m_GBuffer = new GBuffer(&m_Camera);
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


void Renderer::Draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_GBuffer->FirstPass(&m_Objects);
	m_GBuffer->SecondPass(&m_Lights);
	m_GBuffer->RenderQuad();
	m_GBuffer->Bind();
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Renderer::processInput(float DT)
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);

	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		m_Camera.ProcessKeyboard(FORWARD, DT);
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		m_Camera.ProcessKeyboard(BACKWARD, DT);
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		m_Camera.ProcessKeyboard(LEFT, DT);
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		m_Camera.ProcessKeyboard(RIGHT, DT);

}

