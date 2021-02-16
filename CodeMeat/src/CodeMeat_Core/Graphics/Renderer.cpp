#include "Renderer.h"

bool Renderer::Init(){
	m_Camera = Camera();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 0;
	}

	GenBuffer();
	return 1;
}

void Renderer::GenBuffer() {
	m_GBuffer = new GBuffer();
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

void Renderer::AddShader(const char* Identifier, const char* VertexPath, const char* FragmentPath, const char* GeometryPath) {
	if (GeometryPath == nullptr) {
		m_Shaders[Identifier] = Shader(VertexPath, FragmentPath);
	}
	else {
		m_Shaders[Identifier] = Shader(VertexPath, FragmentPath, GeometryPath);
	}
}

void Renderer::Begin() {
	m_GBuffer->FirstPass();
	glm::mat4 m_Projection = glm::perspective(glm::radians(m_Camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 m_View = m_Camera.GetViewMatrix();
	for (std::map<const char*, Shader>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); it++) {
		it->second.Use();
		it->second.SetMat4("Projection", m_Projection);
		it->second.SetMat4("View", m_View);

	}
	for (GameObject* object : m_RenderQueue) {
		object->Draw();
	}
}

void Renderer::Submit(GameObject* Object) {
	m_RenderQueue.push_back(Object);
}

void Renderer::Flush() {
	m_GBuffer->Bind();

}

void Renderer::End() {
	
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}
