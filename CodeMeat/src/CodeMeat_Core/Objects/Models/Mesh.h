#ifndef MESH_H
#define MESH_H

#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Graphics/Shaders/Shader.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat_Core/Deps/Vertex.h"


//Class Definitions
class Shader;

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int VAO;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		setupMesh();
	}

	void Draw(Shader *shader);
private:
	unsigned int VBO, EBO;

	void setupMesh();
};
#endif