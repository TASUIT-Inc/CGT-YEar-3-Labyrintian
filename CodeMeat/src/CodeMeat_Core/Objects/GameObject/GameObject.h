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

	//Component Attachers
	void AttachModel(Model* model) { m_Model = model; m_Params = nullptr;  }
	void AttachBoundingBox(glm::vec3 const& pos, glm::vec3 const& extents) { m_AABB = new BoundingBox(pos, extents); m_MeshCollider = nullptr; }
	void AttachLoaderParams(LoaderParams* NewParams) { m_Params = NewParams; m_Model = nullptr; }
	void AttachTexture(const char* TexturePath) { m_Texture = loadTexture(TexturePath); }
	void AttachShader(Shader* shader) { m_Shader = shader; }
	static unsigned int loadTexture(char const* path);

	void GenerateColliders();

	//Getters
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
	const char* GetTag() const { return m_Tag; }

	void SetTag(const char* newtag) { m_Tag = newtag; }

	virtual ~GameObject();
protected:

	glm::mat4 m_ModelMatrix;
	
	unsigned int m_Texture;
	const char* m_Tag = "OBJ";

	Model* m_Model = nullptr;
	LoaderParams* m_Params = nullptr;
	Shader* m_Shader = nullptr;
	Kinematics* m_Kinematic;		//Object Specific components
	BoundingBox* m_AABB = nullptr;
	MeshCollider* m_MeshCollider = nullptr;

};
