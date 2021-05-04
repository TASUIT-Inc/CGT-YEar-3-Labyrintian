#ifndef CAMERA_H
#define CAMERA_H

#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat_Core/Physics/Collisions/BoundingBox.h"
#include "CodeMeat_Core/Physics/Collisions/Ray.h"
#include "CodeMeat_Core/Physics/Newtonians/Kinematics.h"
#include "CodeMeat_Core/Objects/GameObject/GameObject.h"


/*

Name: Brodie Frail

Student ID: B00369676

I declare that the following code was produced by Brodie Frail and Daryyl Cully as a group assignment for the Real Time graphics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = 180.0f;
const float PITCH = 0.0f;
const float SPEED = 100.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	
	
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float yConstraint;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{

		m_Kinematics = new Kinematics(10.0f, position);
		m_Kinematics->m_Transform.Scale(glm::vec3(1.0f));
		glm::vec3 pos = m_Kinematics->m_Transform.GetPos();
		glm::vec3 extents = glm::vec3(1.0f);
		m_Collider = new BoundingBox(pos, extents);
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		yConstraint = position.y;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		m_Kinematics = new Kinematics(10.0f, glm::vec3(posX, posY, posZ));
		m_Kinematics->m_Transform.Scale(glm::vec3(1.0f));
		m_Collider = new BoundingBox(glm::vec3(posX, posY, posZ), glm::vec3(1.0f));
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		glm::vec3 Pos = m_Kinematics->m_Transform.GetPos();
		return glm::lookAt(Pos, Pos + Front, Up);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		m_Kinematics->m_Vel = glm::vec3(0.0f);
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			m_Kinematics->m_Vel = Front * velocity;
		if (direction == BACKWARD)
			m_Kinematics->m_Vel = Front * -velocity;
		if (direction == LEFT)
			m_Kinematics->m_Vel = Right * -velocity;
		if (direction == RIGHT)
			m_Kinematics->m_Vel = Right * velocity;
		m_Kinematics->m_Vel.y = 0.0f;
		Update(deltaTime);

	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

	glm::vec3 GetPos() { return m_Kinematics->m_Transform.GetPos(); }

	BoundingBox* m_Collider;
	Ray* m_Ray = nullptr;

private:
	
	void Update(float dt) 
	{
		glm::vec3 newPos = m_Kinematics->m_Vel * dt;
		m_Kinematics->m_Transform.Translate(newPos);
		m_Collider->Update(m_Kinematics->m_Transform);
	}
	Kinematics* m_Kinematics;
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}

};
#endif