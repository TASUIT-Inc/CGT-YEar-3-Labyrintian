#include "GameObject.h"


GameObject::GameObject(glm::vec3 pos, glm::vec3 extents) : Object()
{
	m_Kinematic = new Kinematics( 10.0f, pos);
	m_Kinematic->m_Transform.Scale(extents);	

}

void GameObject::Draw(Shader *shader) {
	
	glm::mat4 modelmatrix = m_Kinematic->m_Transform.LocalToWorld();	//set model matrix to the Objects transform matrix

	if (m_Model != nullptr) {
		shader->Use();
		shader->SetModel(modelmatrix);		//set shader specific variables then draw the model
		shader->SetMat4("Model", modelmatrix);
		m_Model->Draw(shader);
	}
	else if(m_Params != nullptr) {
		shader->Use();
		shader->SetModel(modelmatrix);		//set shader specific variables then draw the LoaderParams
		shader->SetMat4("Model", modelmatrix);
		m_Params->Draw(m_Texture);
		
	}
}


unsigned int GameObject::loadTexture(char const* path)		//Load Texture from file
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	try 
	{
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
	catch (std::system_error& e) 
	{
		std::cout << "Error Code: " << e.code() << "Error Message: " << e.what() << std::endl;
	}
	
	return textureID;
}

void GameObject::GenerateColliders() 
{

		m_MeshCollider = new MeshCollider(m_Model, m_Kinematic->m_Transform);	//Create new Mesh Collider Object
}

GameObject::~GameObject() 
{

	if (m_Model != nullptr) 
	{
		delete m_Model;
	}
	else if (m_Params != nullptr) 
	{
		delete m_Params;
	}
	else if (m_Shader != nullptr)	//if a variable exists delete it
	{
		delete m_Shader;
	}
	else if (m_AABB != nullptr) 
	{
		delete m_AABB;
	}
	else if (m_MeshCollider != nullptr) 
	{
		delete m_MeshCollider;
	}
	delete m_Kinematic;

}
