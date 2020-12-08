#include "Model.h"






void Model::loadModel(std::string const& path)		// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
{
	Assimp::Importer importer;		// read file via ASSIMP
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)		 // check for errors		// if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));		// retrieve the directory path of the filepath

	processNode(scene->mRootNode, scene);		// process ASSIMP's root node recursively
}



void Model::processNode(aiNode* node, const aiScene* scene)			// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)		// process each mesh located at the current node
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];		// the node object only contains indices to index the actual objects in the scene
		meshes.push_back(processMesh(mesh, scene));				// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	{
		processNode(node->mChildren[i], scene);
	}
}



Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) 
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		//std::cout << textures.size() << std::endl;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
	

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		

		if (mesh->mTextureCoords[0]) 
		{

			glm::vec2 vec;


			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else 
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}


		if(mesh->mTangents == nullptr){
		
			//std::cout << "Error: The Loaded Mesh has no Tangents." << std::endl;
			vertex.Tangent = glm::vec3(0, 0, 0);
		}
		else {
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
		}

		if (mesh->mBitangents == nullptr) {

			//std::cout << "Error: The Loaded Mesh has no Tangents." << std::endl;
			vertex.Bitangent = glm::vec3(0, 0, 0);
		}
		else {
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
			
		}
		vertices.push_back(vertex);
	}
	

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{

		aiFace face = mesh->mFaces[i];
		
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	

	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	

	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	

	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	

	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) 
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		

		bool skip = false;


		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   
			Texture texture;

			texture.id = TextureFromFile(str.C_Str(), this->directory);
			//std::cout << this->directory << std::endl;
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);

		}
	}

	return textures;
}

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma) 
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	
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