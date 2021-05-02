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
				std::cout << "X Pos: " << p1.x << "Y pos: " << p1.y << "Z Pos: " << p1.z << std::endl;
				std::cout << "X Pos: " << p2.x << "Y pos: " << p2.y << "Z Pos: " << p2.z << std::endl;
				std::cout << "X Pos: " << p3.x << "Y pos: " << p3.y << "Z Pos: " << p3.z << std::endl;
			}
		}
	}

}

