#include "Renderer.h"

bool Renderer::Init(){
	m_Camera = Camera(glm::vec3(0.0f,0.0f,5.0f));
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

	GenBuffer();
	return 1;
}

void Renderer::GenBuffer() {
	m_GBuffer = new GBuffer(&m_Camera);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_GBuffer->FirstPass(m_Objects);
	m_GBuffer->SecondPass(m_Lights);
}

void Renderer::Submit(GameObject* Object) {
	m_Objects.push_back(Object);
}

void Renderer::Submit(Light* light) {
	m_Lights.push_back(light);
}

void Renderer::Flush() {
	m_GBuffer->Bind();

}

void Renderer::End() {
	
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}
