#include "MeshCollider.h"

void MeshCollider::GenerateMeshData(Model* model, Transform& transform) 
{
	glm::vec3 p1, p2, p3;
	for (auto& M : model->meshes) 
	{
		for (int i = 0; i < M.indices.size(); i += 6) 
		{
			for (int j = 0; j < 6; j +=3) 
			{
				p1 = glm::vec3(M.vertices[M.indices[i + j]].m_Pos) * transform.GetScalar();
				p2 = glm::vec3(M.vertices[M.indices[i + j + 1]].m_Pos) * transform.GetScalar();
				p3 = glm::vec3(M.vertices[M.indices[i + j + 2]].m_Pos) * transform.GetScalar();

				meshdata.push_back(Triangle{ p1,p2,p3 });
			}
		}
	}

}

