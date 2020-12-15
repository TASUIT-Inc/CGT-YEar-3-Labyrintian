#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"

#include <vector>
#include <cmath>
class LoaderParams
{

public:
	LoaderParams(glm::vec3 Pos, glm::vec3 Extents, char Tag) : m_Pos(Pos), m_Extents(Extents), m_InterLeavedStride(32) {
		std::cout << "in Loader" << std::endl;
		switch (Tag) {
		case 'C':
			CreateCube();
			break;
		case'c':
			CreateCube();
			break;
		case'P':
			CreatePyramid();
			break;
		case'p':
			CreatePyramid();
			break;
		default:
			CreateCube();
			break;
		}

		m_Segments = glm::vec2(0, 0);
	}

	LoaderParams(glm::vec3 Pos, glm::vec3 Extents, glm::vec2 Segemnts/*, char Tag = ' '*/) : m_Pos(Pos), m_Extents(Extents), m_Segments(Segemnts), m_InterLeavedStride(32) {

		CreateSphere();

	}

	LoaderParams(glm::vec3 Pos, glm::vec3 Extents) : m_Pos(Pos), m_Extents(Extents), m_InterLeavedStride(32) {

		m_Segments = glm::vec2(0, 0);

		CreatePlane();

	}


	glm::vec3 GetPos() { return m_Pos; }
	glm::vec3 GetExtents() { return m_Extents; }
	glm::vec2 GetSegments() { return m_Segments; }

	void SetPos(glm::vec3 NewPos) { m_Pos = NewPos; }
	void SetPos(float Posx, float Posy, float Posz) { m_Pos.x = Posx; m_Pos.y = Posy; m_Pos.z = Posz; }

	void SetExtents(glm::vec3 NewExtents) { m_Extents = NewExtents; }
	void SetExtents(float Extentsx, float Extentsy, float Extentsz) { m_Extents.x = Extentsx; m_Extents.y = Extentsy; m_Extents.z = Extentsz; }

	void SetSegments(glm::vec2 NewSegments) { m_Segments = NewSegments; }
	void SetSegments(float Segmentsx, float Segmentsy, float Segmentsz) { m_Segments.x = Segmentsx; m_Segments.y = Segmentsy; }

	void SetInterlacedVertices();

	void Draw(Shader* shader, unsigned int texture);

	virtual ~LoaderParams() {}
private:
	glm::vec3 m_Pos;
	glm::vec3 m_Extents;
	glm::vec2 m_Segments;
	std::vector<float> m_Vertices;
	std::vector<float> m_Normals;
	std::vector<float> m_Texcoords;
	std::vector<float> m_InterLeavedVertices;
	int m_InterLeavedStride;
	unsigned int VBO, VAO;

	void CreateCube();
	void CreatePyramid();
	void CreateSphere();
	void CreateTorus();
	void CreatePlane();
	void InitVertexObjects();

	void AddVertex(float x, float y, float z);
	void Addnormal(float x, float y, float z);
	void AddTexCoord(float x, float y);

	std::vector<float> ComputeFaceNormals(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);


};