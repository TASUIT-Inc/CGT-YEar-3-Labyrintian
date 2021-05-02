#pragma once
#define PCUBE 0x001
#define PPYRAMID 0x002
#define PSPHERE 0x003
#define PPLANE 0x004


#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat_Core/Deps/Vertex.h"

class LoaderParams
{
public:
	LoaderParams(int Type, glm::vec2 Segments = glm::vec2(50.0f)) :isSphere(false) {
		
		switch (Type) {
		case PCUBE:
			CreateCube();
			break;
		case PPYRAMID:
			CreatePyramid();
			break;
		case PSPHERE:
			CreateSphere(Segments);
			break;
		case PPLANE:
			CreatePlane();
			break;
		default:
			
			break;
		}
	}

	void PushVertexOrder(Vertex V1, Vertex V2, Vertex V3);
	void Draw(unsigned int texture);
	void InitBufferData();

	//getters
	std::vector<Vertex>& GetVertexData() { return m_InterLeavedVertices; }

	virtual ~LoaderParams() {}
private:
	std::vector<Vertex> m_InterLeavedVertices;
	bool isSphere;
	GLint DrawMode;
	unsigned int m_VAO = 0, m_VBO = 0;

	void CreateCube();
	void CreatePyramid();
	void CreateSphere(glm::vec2 Segments);
	void CreatePlane();



};