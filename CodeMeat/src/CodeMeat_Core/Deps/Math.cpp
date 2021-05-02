#pragma once
#include"Math.h"
#include"CodeMeat_Core/Physics/Collisions/Collider.h"

const glm::vec3 Math::Up = glm::vec3(0, 1, 0);

const glm::vec3 Math::Down = glm::vec3(0, -1, 0);

const glm::vec3 Math::Left = glm::vec3(0, 0, 1);

const glm::vec3 Math::Right = glm::vec3(0, 0, -1);

const glm::vec3 Math::Foward = glm::vec3(1, 0, 0);

const glm::vec3 Math::Backwards = glm::vec3(-1, 0, 0);


float Math::DistanceToPoint(const glm::vec3& P1, const glm::vec3& P2) 
{
	return glm::distance(P1, P2);
}

float Math::DistanceToPlane(const glm::vec3& Point, const glm::vec3& Normal, float Direction) 
{
	return abs(glm::dot(Point, Normal) - Direction);
}

float Math::Clamp(float val) 
{
	return glm::max(glm::min(val, 1.0f), 0.0f);
}

//glm::vec3 Math::ProjectPointOnAABB(const glm::vec3& Point, const BoundingBox* const aabb) 
//{
//	glm::vec3 center = aabb->m_Pos;
//	glm::vec3 extents = aabb->m_Extents;
//	glm::vec3 normal = Math::GetAABBFaceNormal(Point, aabb);
//	float distance = abs(glm::dot(normal, extents));
//	glm::vec3 P = Math::ProjectPointOnPlane(Point - center, normal, distance);
//	return P + center;
//}
//
//glm::vec3 Math::GetAABBFaceNormal(const glm::vec3& Point, const BoundingBox* const aabb)
//{
//	char mask = Math::ComputePointMask(Point, aabb);
//	glm::vec3 normal = glm::vec3(0);
//	
//	if ((mask & 1) == 1) {	// +x
//		normal += Math::Foward;
//	}
//	if ((mask & 2) == 2) {	// -x
//		normal += Math::Backwards;
//	}
//	if ((mask & 4) == 4) {	// +y
//		normal += Math::Up;
//	}
//	if ((mask & 8) == 8) {	// -y
//		normal += Math::Down;
//	}
//	if ((mask & 16) == 16) {	//+z
//		normal += Math::Left;
//	}
//	if ((mask & 32) == 32) {	//-z
//		normal += Math::Right;
//	}
//	return glm::normalize(normal);
//}
//
//glm::vec3 Math::ProjectPointOnPlane(const glm::vec3& Point, const glm::vec3& Normal, float c) 
//{
//	float distance = Math::DistanceToPlane(Point, Normal, c);
//	return Point - distance * Normal;
//}
//
//bool Math::PointIsAbovePlane(const glm::vec3& Point, const glm::vec3& Normal, float c) 
//{
//	return glm::dot(Normal, Point) + c > FLT_EPSILON;
//}
//
///*
//Mask is computed as in the following ASCII image.
//
//This is foe the 2D case with codes for +/-x and +/-y
//
//000110	    |	+y 000100   	|	000101
//-----------------------------------
//-x 000010	|	   000000		|	+x 000001
//-----------------------------------
//001010	    |	-y 001000  	    |	001001
//
//the 3D case for +/-z is similar but using 6 bits instead of 4 so +z = 010000 and -z = 100000
//
//*/
//
//char Math::ComputePointMask(const glm::vec3& P1, const BoundingBox* const aabb)
//{
//	glm::vec3 center = aabb->m_Pos;
//	glm::vec3 extents = aabb->m_Extents;
//
//	char mask = 0;
//
//	if (Math::PointIsAbovePlane(P1, Math::Foward, -center.x - extents.x))
//	{
//		//cout << "X" << endl;
//		mask |= 1;// +x
//	}
//	if (PointIsAbovePlane(P1, Math::Backwards, center.x - extents.x))
//	{
//		//cout << "-X" << endl;
//		mask |= 2;	// -x
//	}
//	if (PointIsAbovePlane(P1, Math::Up, -center.y - extents.y))
//	{
//		//cout << "Y" << endl;
//		mask |= 4;	// +y
//	}
//	if (PointIsAbovePlane(P1, Math::Down, center.y - extents.y))
//	{
//		//cout << "-Y" << endl;
//		mask |= 8;	// -y
//	}
//	if (PointIsAbovePlane(P1, Math::Left, -center.z - extents.z))
//	{
//		//cout << "z" << endl;
//		mask |= 16;	// +z
//	}
//	if (PointIsAbovePlane(P1, Math::Right, center.z - extents.z))
//	{
//		//cout << "-z" << endl;
//		mask |= 32;	// -z
//	}
//	return mask;
//}