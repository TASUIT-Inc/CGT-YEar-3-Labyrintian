#pragma once
#include "CodeMeat_Core/Deps/stb_image.h"
#include "CodeMeat_Core/Objects/GameObject/Object.h"
#include "CodeMeat_Core/Objects/LoaderParams.h"
#include "CodeMeat_Core/Objects/Models/Model.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat.h"

class Object;
class Model;
class Shader;

class GameObject : public Object
{
public:
	GameObject(glm::vec3 pos, glm::vec3 extents, glm::vec3 rotation);

	void Draw(Shader shader);
	void Update() {}

	void SetPos(glm::vec3 NewPos) { m_Pos = NewPos; }
	void SetPos(float Posx, float Posy, float Posz) { m_Pos.x = Posx; m_Pos.y = Posy; m_Pos.z = Posz; }

	void SetExtents(glm::vec3 Newextents) { m_Extents = Newextents; }
	void SetExtents(float Extentsx, float Extentsy, float Extentsz) { m_Extents.x = Extentsx; m_Extents.y = Extentsy; m_Extents.z = Extentsz; }

	void SetRotation(glm::vec3 Newrotation) { m_Rotation = Newrotation; }
	void SetRotation(float Rotationx, float Rotationy, float Rotationz) { m_Rotation.x = Rotationx; m_Rotation.y = Rotationy; m_Rotation.z = Rotationz; }

	void AttachModel(Model *NewModel) { m_Model = NewModel; isModel = true; }
	void AttachLoaderParams(LoaderParams* NewParams) { m_Params = NewParams;}
	void AttachTexture(const char* TexturePath) { m_Texture = loadTexture(TexturePath); }
	void AttachShader(Shader* shader) { m_Shader = shader; }


	glm::vec3 GetPos() { return m_Pos; }
	glm::vec3 GetExtents() { return m_Extents; }
	glm::vec3 GetRotation() { return m_Rotation; }

	virtual ~GameObject() {}
private:

	unsigned int loadTexture(char const* path);

	bool isModel;

	glm::vec3 m_Pos, m_Extents, m_Rotation;
	glm::mat4 m_ModelMatrix;
	
	unsigned int m_Texture;

	Model* m_Model;
	LoaderParams* m_Params;
	Shader* m_Shader;

};
