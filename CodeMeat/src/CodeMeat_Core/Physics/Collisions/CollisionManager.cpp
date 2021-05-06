#include "CollisionManager.h"

CollisionData* CollisionManager::CheckCollisions(Camera* Obj1, GameObject* Obj2) {
	CollisionData* Data = nullptr;
	if (Obj1->m_Ray == nullptr) {	//if not shooting a ray
		if (dynamic_cast<MeshCollider*>(Obj2->GetCollider()) != nullptr)	// since the players Collider is always an AABB we only need to check if the Objects is a meshCollider ort a Bounding Box
		{
			PlayerToMeshCollider(Obj1, Obj2, &Data);
			return Data;
		}
		if (dynamic_cast<BoundingBox*>(Obj2->GetCollider()) != nullptr)
		{
			PlayerToBoundingBox(Obj1, Obj2, &Data);
			return Data;
		}
	}
	else 
	{
		if (dynamic_cast<BoundingBox*>(Obj2->GetCollider()) != nullptr)	//if shooting a ray see iof the ray collides with any object NOTE: once collisions start working this will disable the players collisions for a brief moment
		{
			if (RayToBoundingBox(Obj1, Obj2, &Data)) 
			{
				std::cout << "Here" << std::endl;
				Obj1->m_Ray = nullptr;
				glfwSetCursorPosCallback(REngine::Instance()->GetWindow(), nullptr);
				glfwSetInputMode(REngine::Instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				REngine::Instance()->GetContext()->SetUIContext(&UIElements::PuzzleTest);
			}
			Obj1->m_Ray = nullptr;
			return Data;
		}
	}
	return Data;
}


bool CollisionManager::PlayerToBoundingBox(Camera* camera, GameObject* object, CollisionData** Data) 
{
	BoundingBox* bb1 = camera->m_Collider;
	BoundingBox* bb2 = dynamic_cast<BoundingBox*>(object->GetCollider());

	if (glm::distance(bb1->m_Pos, bb2->m_Pos) <= glm::length(bb1->m_Extents + bb2->m_Extents) || glm::distance(bb2->m_Pos, bb1->m_Pos) <= glm::length(bb2->m_Extents + bb1->m_Extents)) 
	{
		std::cout << "Box Collision" << std::endl;
		return true;
	}
	return true;
}

bool CollisionManager::RayToBoundingBox(Camera* camera, GameObject* object, CollisionData** Data)
{
	Ray* ray = camera->m_Ray;
	BoundingBox* bb2 = dynamic_cast<BoundingBox*>(object->GetCollider());
	float t1, t2, t3, t4, t5, t6;

	t1 = ((bb2->m_Pos - bb2->m_Extents).x - ray->m_Pos.x) / ray->m_Normal.x;
	t2 = ((bb2->m_Pos + bb2->m_Extents).x - ray->m_Pos.x) / ray->m_Normal.x;

	t3 = ((bb2->m_Pos - bb2->m_Extents).y - ray->m_Pos.y) / ray->m_Normal.y;
	t4 = ((bb2->m_Pos + bb2->m_Extents).y - ray->m_Pos.y) / ray->m_Normal.y;

	t5 = ((bb2->m_Pos - bb2->m_Extents).z - ray->m_Pos.z) / ray->m_Normal.z;
	t6 = ((bb2->m_Pos + bb2->m_Extents).z - ray->m_Pos.z) / ray->m_Normal.z;

	float Tmin = max(max(min(t1,t2), min(t3,t4)), min(t5,t6));
	float Tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	if (Tmax < 0)
		return false;

	if (Tmin > Tmax)
		return false;

	if (Tmin < 0)
		return true;
}

bool CollisionManager::PlayerToMeshCollider(Camera* camera, GameObject* object, CollisionData** Data) 
{
	BoundingBox* bb1 = camera->m_Collider;
	MeshCollider* mc1 = dynamic_cast<MeshCollider*>(object->GetCollider());

	for (auto& T : mc1->GetMeshData()) 
	{
		if(AABBToMeshTriangle(bb1, T))
		{
			//std::cout << "Collision Occurs" << std::endl;
		}
	}
	return true;
}

bool CollisionManager::AABBToMeshTriangle(BoundingBox* box, Triangle& face) //You can use this Triangle variable to either peek or goto the definition of both the Triangle and the MeshCollider
{
	glm::vec3 tp1, tp2, tp3; //points of triangle relative to the position of the BB

	tp1 = face.p1 - box->m_Pos;
	tp2 = face.p2 - box->m_Pos;		//calculate the 3 triangle points relative to the position of the camera's bounding box
	tp3 = face.p3 - box->m_Pos;

	glm::vec3 edge1, edge2, edge3; // edges of the triangle

	edge1 = tp2 - tp1;
	edge2 = tp3 - tp2;		//calculate the edges of the triangle with relative Pos'
	edge3 = tp1 - tp3;

	glm::vec3 BoxFNX = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 BoxFNY = glm::vec3(0.0f, 1.0f, 0.0f); // Face normals for the Bounding box, as it is an AABB the face normals are just the X,Y and Z axis
	glm::vec3 BoxFNZ = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 AxisE1_F1, AxisE2_F1, AxisE3_F1, AxisE1_F2, AxisE2_F2, AxisE3_F2, AxisE1_F3, AxisE2_F3, AxisE3_F3;

	AxisE1_F1 = glm::cross(BoxFNX, edge1);
	AxisE2_F1 = glm::cross(BoxFNX, edge2); //x axis seperation axis
	AxisE3_F1 = glm::cross(BoxFNX, edge3);

	AxisE1_F2 = glm::cross(BoxFNY, edge1);
	AxisE2_F2 = glm::cross(BoxFNY, edge2); // y axis seperation axis
	AxisE3_F2 = glm::cross(BoxFNY, edge3);

	AxisE1_F3 = glm::cross(BoxFNZ, edge1);
	AxisE2_F3 = glm::cross(BoxFNZ, edge2);// z axis seperation axis
	AxisE3_F3 = glm::cross(BoxFNZ, edge3);

	//Link to Website that helped me gain an understanding of the logic and structural flow, https://gdbooks.gitbooks.io/3dcollisions/content/Chapter4/aabb-triangle.html 

	//When walking into any wall of the map, this test is supposed to return true as there should be no axis that seperates the camera's AABB and the triangle but the tests never return true
	// The Triangle class is a struct that is created in MeshCollider.Cpp that can be used to see how the MeshCollider is generated
	//The Issue seems to be that either i have wrongly implemented the SAT tests OR ther is something that i have missed in researching SAT.

	//assert(2 == 1); // added an assert to Point you to where general collision detection occurs
	if (SAT_Test_3Point(AxisE1_F1, box, face.p1, face.p2, face.p3) && SAT_Test_3Point(AxisE2_F1, box, face.p1, face.p2, face.p3) && SAT_Test_3Point(AxisE3_F1, box, face.p1, face.p2, face.p3) &&
		SAT_Test_3Point(AxisE1_F2, box, face.p1, face.p2, face.p3) && SAT_Test_3Point(AxisE2_F2, box, face.p1, face.p2, face.p3) && SAT_Test_3Point(AxisE3_F2, box, face.p1, face.p2, face.p3) &&
		SAT_Test_3Point(AxisE1_F3, box, face.p1, face.p2, face.p3) && SAT_Test_3Point(AxisE2_F3, box, face.p1, face.p2, face.p3) && SAT_Test_3Point(AxisE3_F3, box, face.p1, face.p2, face.p3)) //test all 9 axis for overlaps 
	{	// the Test_3Point test is carried out 9 times as there are 9 seperating axis' between the AABB's face normals and triangle vertices 
		if (SAT_Test_3Point(BoxFNX, box, BoxFNX, BoxFNY, BoxFNZ) &&
			SAT_Test_3Point(BoxFNY, box, BoxFNX, BoxFNY, BoxFNZ) &&
			SAT_Test_3Point(BoxFNZ, box, BoxFNX, BoxFNY, BoxFNZ))
		{ // the 2nd set of tests is apllied to the AABB's face normals and the face normals of the triangles AABB but since both are axis aligned the AABB's face normals are suplimented for the triangles AABB
			if (SAT_Test_1Point(glm::cross(edge1, edge2), box)) 
			{ // this Last test is used to test the face normal of the triangle
				return true; // a collision occors only when no seperation axis exists between AABB and mesh Triangle
			}
			else
				return false;
		}else
			return false;
	}else
		return false;
}


bool CollisionManager::SAT_Test_3Point(const glm::vec3& Axis, BoundingBox* box, const glm::vec3& Vec1, const glm::vec3& Vec2, const glm::vec3& Vec3)
{
	float P1, P2, P3, r;

	P1 = glm::dot(Vec1, Axis);
	P2 = glm::dot(Vec2, Axis); // projection of the 3 triangle vertices onto the specified seperating axis
	P3 = glm::dot(Vec3, Axis);


	// cast the AABB's extents ontot he seperating axis, the center of the AABB isn't projected as it is treated as being at (0,0,0)
	r = box->m_Extents.x * abs(glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), Axis)) + box->m_Extents.y * abs(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), Axis)) + box->m_Extents.z * abs(glm::dot(glm::vec3(0.0f, 0.0f, 1.0f), Axis));

	// test to see if either extreme of the triangles vertices intersect the projected extents
	if (std::max(-std::max({ P1, P2, P3 }), std::min({ P1, P2, P3 })) > r)
	{
		// returns false if both extremes are outside the projected half length, therefore a seperating axis exists and no collision occurs
		return false;
	}
	return true;
}

bool CollisionManager::SAT_Test_1Point(const glm::vec3& Axis, BoundingBox* box )
{
	float P1, P2, P3, r;

	P1 = glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), Axis);
	P2 = glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), Axis); //project the triangles face normal onto the face normals of the AABB
	P3 = glm::dot(glm::vec3(0.0f, 0.0f, 1.0f), Axis);

	//Same as in Test_3Points calculate the projected half extents
	r = box->m_Extents.x * abs(glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), Axis)) + box->m_Extents.y * abs(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), Axis)) + box->m_Extents.z * abs(glm::dot(glm::vec3(0.0f, 0.0f, 1.0f), Axis));

	if (max(-max({ P1, P2, P3 }), min({ P1, P2, P3 })) > r)
	{
		return false;
	}
	return true;
}

