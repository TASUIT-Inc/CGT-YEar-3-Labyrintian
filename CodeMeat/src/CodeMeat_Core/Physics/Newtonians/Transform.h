#pragma once
#include "CodeMeat_Core/Deps/Math.h"

class Transform 
{
public:
	Transform();

	virtual ~Transform() {}

	//transformations
	void Translate(glm::vec3 const& translation);
	void Scale(glm::vec3 const& Scalar);
	void RotateAroundXAxis(float angle);
	void RotateAroundYAxis(float angle);
	void RotateAroundZAxis(float angle);

	//getters
	glm::vec3 GetPos() { return glm::column(m_TransformMatrix, 3); }
	glm::vec3 GetScalar();
	glm::vec3 GetRotation();
	glm::vec3 GetUpDir();
	glm::vec3 GetLeftDir();
	glm::vec3 GetFowardDir();

	glm::mat4 LocalToWorld() { return m_TransformMatrix; }
	glm::mat4 WorldToLocal() { return glm::inverse(m_TransformMatrix); }
private:
	glm::mat4 m_TransformMatrix;
};

