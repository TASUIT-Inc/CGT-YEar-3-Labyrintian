
#include "GameObject.h"


GameObject::GameObject(glm::vec3 pos, glm::vec3 extents, glm::vec3 rotation) : Object(), m_Pos(pos), m_Extents(extents), m_Rotation(rotation), m_Params(new LoaderParams(PCUBE)), m_Texture(loadTexture("Dev.png")),m_ModelMatrix(glm::mat4(1.0f)) ,isModel(false) {}

void GameObject::Draw(Shader *shader) {
	
	m_ModelMatrix = glm::mat4(1.0f);
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Pos);
	m_ModelMatrix = glm::scale(m_ModelMatrix, m_Extents);
	//m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.x, glm::vec3(1, 0, 0));
	//m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.y, glm::vec3(0, 1, 0));
	//m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.z, glm::vec3(0, 0, 1));
	shader->Use();
	shader->SetModel(m_ModelMatrix);
	shader->SetMat4("Model", m_ModelMatrix);

	if (isModel) {
		m_Model->Draw(shader);
	}
	else {
		m_Params->Draw(m_Texture);
	}

	for (Instance I : m_Instances) {
		m_ModelMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::translate(m_ModelMatrix, I.m_Pos);
		m_ModelMatrix = glm::scale(m_ModelMatrix, I.m_Extents);
		//m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.x, glm::vec3(1, 0, 0));
		//m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.y, glm::vec3(0, 1, 0));
		//m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.z, glm::vec3(0, 0, 1));
		shader->Use();
		shader->SetModel(m_ModelMatrix);
		shader->SetMat4("Model", m_ModelMatrix);

		if (isModel) {
			m_Model->Draw(shader);
		}
		else {
			m_Params->Draw(m_Texture);
		}
	}
}


unsigned int GameObject::loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	std::string FilePath = TEXTURE_POOL_PATH + (std::string)path;


	int width, height, nrComponents;
	unsigned char* data = stbi_load(FilePath.c_str(), &width, &height, &nrComponents, 0);
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