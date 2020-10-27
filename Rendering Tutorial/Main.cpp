#include "Game.h"

Game* m_Game = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput();
unsigned int loadTexture(const char* path);


bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;



int main()
{
	if (Game::Instance()->init("Game Engine Test", 800, 600)) 
	{
		GLFWwindow* window = Game::Instance()->GetWindow();
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		while (!glfwWindowShouldClose(window))
			{

			processInput();

			Game::Instance()->Update();

			Game::Instance()->Draw();
				// per-frame time logic
				// --------------------
				//float currentFrame = glfwGetTime();
				//deltaTime = currentFrame - lastFrame;
				//lastFrame = currentFrame;

				//// input
				//// -----
				//processInput(window);

				//// render
				//// ------
				//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
				//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				

				//shader.Use();
				//glm::mat4 model = glm::mat4(1.0f);
				//glm::mat4 view = camera.GetViewMatrix();
				//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
				//shader.SetMat4("view", view);
				//shader.SetMat4("projection", projection);

				//// floor
				//glBindVertexArray(planeVAO);
				//glBindTexture(GL_TEXTURE_2D, floorTexture);
				//shader.SetMat4("model", glm::mat4(1.0f));
				//glDrawArrays(GL_TRIANGLES, 0, 6);
				//glBindVertexArray(0);

				//// cubes
				//glBindVertexArray(cubeVAO);
				//glActiveTexture(GL_TEXTURE0);
				//glBindTexture(GL_TEXTURE_2D, cubeTexture);
				//model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
				//shader.SetMat4("model", model);
				//glDrawArrays(GL_TRIANGLES, 0, 36);
				//model = glm::mat4(1.0f);
				//model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
				//shader.SetMat4("model", model);
				//glDrawArrays(GL_TRIANGLES, 0, 36);


				//// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				//// -------------------------------------------------------------------------------
				//glfwSwapBuffers(window);
				//glfwPollEvents();
			}
		Game::Instance()->Clean();
		glfwTerminate();
		return 0;
	}
	
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Game::Instance()->framebuffer_size_callback(width, height);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput()
{
	Game::Instance()->processInput();
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Game::Instance()->mouse_callback(xpos, ypos);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game::Instance()->scroll_callback(xoffset, yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
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
}

