#include "stb_image.h"
#include "GameObject.h"


GameObject::GameObject(LoaderParams* Params, Shader* shader, char const* TexturePath) : Object(Params), m_Params(Params), m_Pos(Params->GetPos()), m_Extents(Params->GetExtents()), m_Shader(shader) {
	m_Texture = loadTexture(TexturePath);
	isModel = false;
}

GameObject::GameObject(LoaderParams* Params, Model* model, Shader* shader) : Object(Params), m_Params(Params), m_Pos(Params->GetPos()), m_Extents(Params->GetExtents()), m_Shader(shader), m_Model(model) {
	isModel = true;
}

GameObject::GameObject(LoaderParams* Params, Shader* shader) : Object(Params), m_Params(Params), m_Pos(Params->GetPos()), m_Extents(Params->GetExtents()), m_Shader(shader), m_Texture(NULL) {
	isModel = false;
}

void GameObject::Draw() {
	m_Shader->Use();
	glm::mat4 modelMatrix = glm::mat4(1.0);
	modelMatrix = glm::translate(modelMatrix, m_Pos);
	modelMatrix = glm::scale(modelMatrix, m_Params->GetExtents());
	m_Shader->SetMat4("model", modelMatrix);

	if (isModel) {
		m_Model->Draw(m_Shader, &modelMatrix);
	}
	else {
		m_Params->Draw(m_Shader, m_Texture);
	}
}

void GameObject::Update() {
	std::cout << "Update" << std::endl;
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