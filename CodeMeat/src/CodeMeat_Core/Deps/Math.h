#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

class Collider;
class BoundingBox;
class MeshCollider;

class Math {
public:
	static const glm::vec3 Up;
	static const glm::vec3 Down;
	static const glm::vec3 Left;
	static const glm::vec3 Right;	//World Direction variables
	static const glm::vec3 Foward;
	static const glm::vec3 Backwards;

	static float DistanceToPoint(const glm::vec3& P1, const glm::vec3& P2);
	static float DistanceToPlane(const glm::vec3& Point, const glm::vec3& Normal, float Direction);
	static float Clamp(float val);																//Public Functions 
	static glm::vec3 ProjectPointOnAABB(const glm::vec3& Point, const BoundingBox* const aabb);
	static glm::vec3 GetAABBFaceNormal(const glm::vec3& Point, const BoundingBox* const aabb);
	/*static glm::vec3 ProjectPointOnPlane(const glm::vec3& Point, const Plane& plane, float c);
	static bool PointIsAbovePlane(const glm::vec3& Point, const Plane& Normal, float c);
	static char ComputePointMask(const glm::vec3& P1, const Collider* const aabb);*/

private:
	Math() {}
};

