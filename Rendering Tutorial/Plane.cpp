#include "Plane.h"

void Plane::Draw(glm::vec3 scale, Shader shader, unsigned int Texture = 0) {
	glBindVertexArray(VAO);
	if (Texture != 0) {
		glBindTexture(GL_TEXTURE_2D, Texture);
	}
	shader.SetMat4("model", glm::mat4(1.0f));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
