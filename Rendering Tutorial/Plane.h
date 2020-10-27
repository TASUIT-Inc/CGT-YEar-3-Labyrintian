#pragma once
#include "Shape.h"
#include "Shader.h"
class Plane :public Shape
{
public:
	Plane()
	{
		float m_vertices[] = {
		  5.0f, -0.5f,  5.0f,
		 -5.0f, -0.5f,  5.0f,
		 -5.0f, -0.5f, -5.0f,

		  5.0f, -0.5f,  5.0f,
		 -5.0f, -0.5f, -5.0f,
		  5.0f, -0.5f, -5.0f,
		};

		(*m_Vertices) = m_vertices;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), &m_Vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glBindVertexArray(0);
	}
private:
	void Draw(glm::vec3 scale, Shader shader, unsigned int Texture =0);
	float* m_Vertices[18];

	unsigned int VAO, VBO;
protected:

};

