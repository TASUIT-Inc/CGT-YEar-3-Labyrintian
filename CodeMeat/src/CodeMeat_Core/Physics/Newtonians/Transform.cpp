#include "Transform.h"

Transform::Transform() 
{
	m_TransformMatrix = glm::mat4(1.0f);
}

void Transform::Translate(glm::vec3 const& translation) 
{
	glm::mat4x3 translationMatrix = glm::mat4(1.0f, 0.0f, 0.0f,0.0f ,
											  0.0f, 1.0f, 0.0f,0.0f ,
											  0.0f, 0.0f, 1.0f,0.0f , 
										      translation.x, translation.y, translation.z, 1.0f);

	m_TransformMatrix = translationMatrix * m_TransformMatrix;
}

void Transform::Scale(glm::vec3 const& Scalar) 
{

	glm::mat4x3 scalingmatrix = glm::mat3x4(Scalar.x, 0.0f, 0.0f, 0.0f,
										    0.0f, Scalar.y, 0.0f, 0.0f,
										    0.0f, 0.0f, Scalar.z, 0.0f);

	m_TransformMatrix = scalingmatrix * m_TransformMatrix;

}

void Transform::RotateAroundXAxis(float angle)
{

	glm::mat4x3 rotationmatrix = glm::mat3x4(1.0f, 0.0f, 0.0f, 0.0f,
											 0.0f, cos(angle), -sin(angle), 0.0f,
											 0.0f, sin(angle),  cos(angle), 0.0f);

	m_TransformMatrix = rotationmatrix * m_TransformMatrix;

}

void Transform::RotateAroundYAxis(float angle)
{

	glm::mat4x3 rotationmatrix = glm::mat3x4(cos(angle), 0.0f, sin(angle), 0.0f,
												0.0f   , 1.0f,    0.0f	 , 0.0f,
											-sin(angle), 0.0f,-cos(angle), 0.0f);

	m_TransformMatrix = rotationmatrix * m_TransformMatrix;

}

void Transform::RotateAroundZAxis(float angle)
{

	glm::mat4x3 rotationmatrix = glm::mat3x4(cos(angle), -sin(angle), 0.0f, 0.0f,
											 sin(angle), -cos(angle), 0.0f, 0.0f,
											    0.0f   ,	 0.0f   , 1.0f, 0.0f);

	m_TransformMatrix = rotationmatrix * m_TransformMatrix;

}

glm::vec3 Transform::GetScalar() 
{
	float EX = glm::length(glm::column(m_TransformMatrix, 0));
	float EY = glm::length(glm::column(m_TransformMatrix, 1));
	float EZ = glm::length(glm::column(m_TransformMatrix, 2));

	return glm::vec3(EX, EY, EZ);
}

glm::vec3 Transform::GetRotation() 
{
	glm::vec4 rotation = glm::normalize(glm::column(m_TransformMatrix, 0));

	return glm::vec3(rotation.x, rotation.y, rotation.z);
}

glm::vec3 Transform::GetUpDir() 
{
	glm::vec4 up = glm::normalize(glm::column(m_TransformMatrix, 1));

	return glm::vec3(up.x, up.y, up.z);
}

glm::vec3 Transform::GetLeftDir() 
{
	glm::vec4 left = glm::normalize(glm::column(m_TransformMatrix, 2));

	return glm::vec3(left.x, left.y, left.z);
}

glm::vec3 Transform::GetFowardDir() 
{
	glm::vec4 foward = glm::normalize(glm::column(m_TransformMatrix, 0));

	return glm::vec3(foward.x, foward.y, foward.z);
}



