
#include "GameObject.h"
#include "CodeMeat_Core/Graphics/Renderer.h"

GameObject::GameObject(glm::vec3 pos, glm::vec3 extents, glm::vec3 rotation) : Object(), m_Pos(pos), m_Extents(extents), m_Rotation(rotation), m_Params(&LoaderParams(PCUBE)), m_Texture(loadTexture("Dev.png")), isModel(false) {}

void GameObject::Draw() {
	if (isModel) {
		m_Model->Draw(m_Shader);
	}
	else {
		m_Params->Draw();
	}
}


unsigned int GameObject::loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	std::string FilePath = TEXTURE_POOL_PATH + (std::string)path;

	const char* TotalPath = FilePath.c_str();

	int width, height, nrComponents;
	unsigned char* data = stbi_load(TotalPath, &width, &height, &nrComponents, 0);
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