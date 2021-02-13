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
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, RENDER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, RENDER_VERTEX_STRIDE, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, RENDER_VERTEX_STRIDE, (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, RENDER_VERTEX_STRIDE, (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Renderer::Submit(GameObject* Object) {
	m_Buffer->m_Pos = Object->GetPos();
}

void Renderer::Flush() {

}

void Renderer::End() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
}
