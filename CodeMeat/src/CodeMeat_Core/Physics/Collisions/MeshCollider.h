#pragma once
#include "Collider.h"
#include "CodeMeat_Core/Objects/Models/Model.h"


struct Triangle			//Triangle primative
{
	glm::vec3 p1,p2,p3;
};

class MeshCollider : public Collider {
public:
	MeshCollider(Model* model, Transform& transform) : Collider()
	{
		GenerateMeshData(model, transform);
	
	}

	std::vector<Triangle>& GetMeshData() { return meshdata; }
	void GenerateMeshData(Model* model, Transform& transform);
	

private:
	std::vector<Triangle> meshdata;	//triangle vector for use in collision tests
	
};

