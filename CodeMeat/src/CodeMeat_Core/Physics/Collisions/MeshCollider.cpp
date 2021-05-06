#include "MeshCollider.h"

void MeshCollider::GenerateMeshData(Model* model, Transform& transform) 
{
	glm::vec3 p1, p2, p3;
	for (auto& M : model->meshes)		//for each mesh
	{
		for (int i = 0; i < M.indices.size(); i += 6)	//for each set of 6 indices
		{
			for (int j = 0; j < 6; j +=3)	//for each set of 3 in that set of 6
			{
				p1 = glm::vec3(M.vertices[M.indices[i + j]].m_Pos) * transform.GetScalar();		
				p2 = glm::vec3(M.vertices[M.indices[i + j + 1]].m_Pos) * transform.GetScalar();		//models that are scaled have their vertex position scaled by that amount so at 0.2f a pos of 1.0f = 0.2f
				p3 = glm::vec3(M.vertices[M.indices[i + j + 2]].m_Pos) * transform.GetScalar();

				meshdata.push_back(Triangle{ p1,p2,p3 });		//create a triangle with the 3 vertices
			}
		}
	}

}

