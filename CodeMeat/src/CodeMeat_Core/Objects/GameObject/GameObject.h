#pragma once
#include "CodeMeat_Core/Deps/stb_image.h"
#include "CodeMeat_Core/Objects/GameObject/Object.h"
#include "CodeMeat_Core/Objects/LoaderParams.h"
#include "CodeMeat_Core/Objects/Models/Model.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat.h"
#include "CodeMeat_Core/Physics/Collisions/MeshCollider.h"
#include "CodeMeat_Core/Physics/Collisions/BoundingBox.h"
#include "CodeMeat_Core/Physics/Newtonians/Kinematics.h"
#include "CodeMeat_Core/Physics/Newtonians/Transform.h"


class Object;
class Model;
class Shader;
class GameObject;
class Collider;



class GameObject : public Object
{
public:
	GameObject(glm::vec3 pos, glm::vec3 extents);
	/*GameObject() : Object() {}*/

	void Draw(Shader *shader);
	void Update() { }

	void AttachModel(Model* model) { m_Model = model; m_Params = nullptr; GenerateColliders(); }
	void AttachLoaderParams(LoaderParams* NewParams) { m_Params = NewParams; m_Model = nullptr; }
	void AttachTexture(const char* TexturePath) { m_Texture = loadTexture(TexturePath); }
	void AttachShader(Shader* shader) { m_Shader = shader; }


	Collider* GetCollider() 
	{ 
		if (m_AABB != nullptr) 
		{
			return m_AABB;
		}
		else if (m_MeshCollider != nullptr) 
		{
			return m_MeshCollider;
		}
	}

	Kinematics* GetKinematics() const { return m_Kinematic; } 

	virtual ~GameObject();
protected:

	unsigned int loadTexture(char const* path);
	void GenerateColliders();

	glm::mat4 m_ModelMatrix;
	
	unsigned int m_Texture;

	Model* m_Model = nullptr;
	LoaderParams* m_Params = nullptr;
	Shader* m_Shader = nullptr;
	Kinematics* m_Kinematic;
	BoundingBox* m_AABB = nullptr;
	MeshCollider* m_MeshCollider = nullptr;

};
