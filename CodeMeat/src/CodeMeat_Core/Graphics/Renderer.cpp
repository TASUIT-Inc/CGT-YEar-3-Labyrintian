#include "Renderer.h"



bool Renderer::Init() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		//init OpenGl versions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// glfw window creation
	// --------------------
	m_Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);	//Create window and check to see if it was sucessfully made
	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 0;
	}
			
	glfwMakeContextCurrent(m_Window);
	
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
	glfwSetCursorPosCallback(m_Window, mouse_callback);			//Set callbacks
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

	m_UiContext = new UIContext(m_Window);	//Create UiContext

	glEnable(GL_DEPTH_TEST);
	m_GBuffer = new GBuffer();	//Create GBuffer Object

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

	Instance()->m_Camera->ProcessMouseMovement(xoffset, yoffset);
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

void Renderer::Clean() 
{
	for (auto* G : m_Objects) 
	{
		G->~GameObject();	//Call the Destructor for each game object when cleaning
	}
	
	delete m_Window, m_Camera, m_UiContext, m_GBuffer;	//delete renderer specific variables
}


void Renderer::Draw() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ComputeShaders();	//Pre Render Shader Compile
	m_GBuffer->FirstPass(m_Camera, &m_Objects);		//PreLighting Object Mesh Render
	m_GBuffer->SecondPass(m_Camera, &m_Lights);		//Lighting Render
	m_GBuffer->RenderQuad();		//Render Screen Quad
	m_GBuffer->Bind();				//Draw Screen Quad to the window
	
	m_UiContext->Draw();			//Draw any Ui elements

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}


void Renderer::Input(float dt)
{
		//Basic Movement Controls
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(FORWARD, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(BACKWARD, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(LEFT, dt);
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(RIGHT, dt);

	//Controls for Opening both the Pause menu and Puzzle UI
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		m_KeyPressed = true;
		glfwSetCursorPosCallback(m_Window, nullptr);	//Tell the window to ignore all mouse movements whilst Ui is Open
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //Tell GLFW to show the Cursor on the Window
		m_UiContext->SetUIContext(&UIElements::PauseMenu);	//Set the Current Ui element to the Pause menu
	}
	if (glfwGetKey(m_Window, GLFW_KEY_I) == GLFW_PRESS) {
		m_KeyPressed = true;
		glfwSetCursorPosCallback(m_Window, nullptr);	//Tell the window to ignore all mouse movements whilst Ui is Open
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);	//Tell GLFW to show the Cursor on the Window
		m_UiContext->SetUIContext(&UIElements::PuzzleTest);		//Set the Current Ui element to the Puzzle board
		
	} 
	if (glfwGetKey(m_Window, GLFW_KEY_I) == GLFW_RELEASE && glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && m_KeyPressed == true) {
		m_KeyPressed = false;
		glfwSetCursorPosCallback(m_Window, mouse_callback);		//Once Ui has Been dealt with close the Ui, tell GLFW to pay attention to mouse movements and hide the cursor
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_UiContext->SetUIContext(nullptr);		//set current Ui element to a nullptr
	}
	if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS) 
	{
		m_Camera->m_Ray = new Ray(m_Camera->GetPos(), m_Camera->Front);	//experiamental Raycasting from camera pos
	}



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
		v->Use();		//Compute camera variables for shaders
		v->SetMat4("Projection", m_Projection);
		v->SetMat4("View", m_View);
	}
}