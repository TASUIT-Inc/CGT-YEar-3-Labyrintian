#pragma once
#include "CodeMeat_Core/Graphics/Renderer.h"
#include "CollisionData.h"

class Camera;

class CollisionManager 
{
public:
	CollisionManager() {}
	static CollisionData* CheckCollisions(Camera* Obj1, GameObject* Obj2);
private:
	/*static bool AABBAABBCollision(GameObject* Obj1, GameObject* Obj2, CollisionData* data);*/
	static bool PlayerToMeshCollider(Camera* camera, GameObject* object, CollisionData** Data);
	static bool PlayerToBoundingBox(Camera* camera, GameObject* object, CollisionData** Data);
	static bool RayToBoundingBox(Camera* camera, GameObject* object, CollisionData** Data);

	static bool AABBToMeshTriangle(BoundingBox* box, Triangle& face);
	static bool AABBToAABB(BoundingBox* box1, BoundingBox* box2);
	static bool SAT_Test_3Point(const glm::vec3& Axis, BoundingBox* box , const glm::vec3& Vec1, const glm::vec3& Vec2, const glm::vec3& Vec3);
	static bool SAT_Test_1Point(const glm::vec3& Axis, BoundingBox* box);
	

	virtual ~CollisionManager() {}

};