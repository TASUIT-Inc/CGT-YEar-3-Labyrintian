#include "GameObject.h"

GameObject::GameObject(glm::vec3 Pos, glm::vec3 Scale, Model* model , const char* Vertexshader = nullptr, const char* FragmentShader = nullptr, const char* GeometryShader = nullptr, const char* texture =nullptr) {
	m_Pos = Pos;
	m_Scale = Scale;
	m_Model = model;

	if (Vertexshader == nullptr && FragmentShader == nullptr) {
		m_Shader = Shader("StandardVS.txt", "StandardFS.txt", GeometryShader);
	}
	else if (Vertexshader != nullptr && FragmentShader == nullptr) {
		m_Shader = Shader(Vertexshader, "StandardFS.txt", GeometryShader);
	}
	else if (Vertexshader == nullptr && FragmentShader != nullptr) {
		m_Shader = Shader("StandardVS.txt", FragmentShader, GeometryShader);
	}

	if (texture != nullptr) {
		loadTexture(texture);
	}
}



void GameObject::Draw() {
	m_Model->Draw(m_Shader);
}

unsigned int GameObject::loadTexture(char const* path)
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