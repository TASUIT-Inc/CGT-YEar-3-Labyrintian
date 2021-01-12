#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Light.h"

#include <iostream>
#include <random>
// Function Definitions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void Clear();

//Global Variables
std::vector<GameObject*> m_Objects;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(8.5f, 1.0f, -1.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//wireframe
bool Wireframe = false;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
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
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	//Instance Renderer
	//-----------------
	Renderer renderer = Renderer(&camera, SCR_WIDTH, SCR_HEIGHT, &m_Objects);

	// build and compile shaders
	// -------------------------
	Shader Default("VS-Default.txt", "FS-Default.txt");
	Shader Lighting("VS-LightingShader.txt", "FS-LightingShader.txt");

	//Create Basic Shapes
	//-------------------
	LoaderParams Cube = LoaderParams(glm::vec3(0.0f, 1.5f, 0.0f), glm::vec3(25.0f, 1.0f, 25.0f), 'C');
	/*LoaderParams Pyramid = LoaderParams(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.5f), 'P');
	LoaderParams Circle = LoaderParams(glm::vec3(5.0f, 1.5f, -5.0f), glm::vec3(1.5f), glm::vec2(25));
	LoaderParams Plane = LoaderParams(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.5f));*/
	LoaderParams ModelParams = LoaderParams(glm::vec3(0.0f), glm::vec3(1.0f));
	//LoaderParams ScreenQuad = LoaderParams();
	Model Tutorial = Model("Models/TestMap2.obj");

	//Create GameObjects
	//------------------
	GameObject* Map = new GameObject(&ModelParams, &Tutorial, &Default);
	GameObject* Roof = new GameObject(&Cube, &Default, "Textures/Dev.png");
	

	//Create Lights
	//-------------
	Light* SkyLight = new Light(glm::vec3(1.0f), glm::vec3(-0.2f, -1.0f, -0.3f));
	Light* RoomLight1 = new Light(glm::vec3(8.5f, 1.5f, -1.0f), glm::vec3(1.0f), 0.8f, 1.5f);
	Light* RoomLight2 = new Light(glm::vec3(3.2f, 1.5f, -1.0f), glm::vec3(1.0f), 0.8f, 1.5f);
	Light* RoomLight3 = new Light(glm::vec3(3.2f, 1.5f,  3.8f), glm::vec3(1.0f), 0.8f, 1.5f);
	Light* RoomLight4 = new Light(glm::vec3(-2.0f, 1.5f, 3.8f), glm::vec3(1.0f), 0.8f, 1.5f);
	Light* RoomLight5 = new Light(glm::vec3(-2.0f, 1.5f,-1.0f), glm::vec3(1.0f), 0.8f, 1.5f);
	Light* RoomLight6 = new Light(glm::vec3(-6.2f, 1.5f, 3.8f), glm::vec3(1.0f), 0.8f, 1.5f);
	Light* RoomLight7 = new Light(glm::vec3(-6.2f, 1.5f,-1.0f), glm::vec3(1.0f), 0.8f, 1.5f);
	Light* RoomLight8 = new Light(glm::vec3(3.2f, 1.5f, -5.8f), glm::vec3(1.0f), 0.8f, 1.5f);

	//Fill Object Vector
	//------------------
	m_Objects.push_back(Map);
	m_Objects.push_back(Roof);

	//set Renderer Variables
	//----------------------
	renderer.InitShaderSamples(&Lighting);
	renderer.AddLight(SkyLight);
	renderer.AddLight(RoomLight1);
	renderer.AddLight(RoomLight2);
	renderer.AddLight(RoomLight3);
	renderer.AddLight(RoomLight4);
	renderer.AddLight(RoomLight5);
	renderer.AddLight(RoomLight6);
	renderer.AddLight(RoomLight7);
	renderer.AddLight(RoomLight8);

	for (int i = 0; i < m_Objects.size(); i++) {
		m_Objects[i]->SetWidth(SCR_WIDTH);
		m_Objects[i]->SetHeight(SCR_HEIGHT);
	}

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------


		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);


		// render
		// ------


		// make sure we clear the framebuffer's content
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw
		//----
		renderer.GeometryPass(&Default);
		renderer.LightingPass(&Lighting);
		renderer.RenderQuad();
		renderer.BindFrameBuffers();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	Clear();

	glfwTerminate();
	return 0;
}

void Clear() {

	for (int i = 0; i < m_Objects.size(); i++) {
		delete m_Objects[i];
	}

}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		switch (Wireframe) {
		case false:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			Wireframe = true;
			break;
		case true:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			Wireframe = false;
			break;
		}


}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
/*unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}*/