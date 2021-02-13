#pragma once
#include "CodeMeat_Core/Objects/GameObject/Object.h"
#include "CodeMeat_Core/Objects/Models/Model.h"
#include <string.h>


class GameObject : public Object
{
public:
	GameObject(LoaderParams* Params, glm::vec3 pos, glm::vec3 extents, glm::vec3 rotation);

	void Draw();
	void Update();

	void SetPos(glm::vec3 NewPos) { m_Pos = NewPos; }
	void SetPos(float Posx, float Posy, float Posz) { m_Pos.x = Posx; m_Pos.y = Posy; m_Pos.z = Posz; }

	glm::vec3 GetPos() { return m_Pos; }

	void SetExtents(glm::vec3 Newextents) { m_Extents = Newextents; }
	void SetExtents(float Extentsx, float Extentsy, float Extentsz) { m_Extents.x = Extentsx; m_Extents.y = Extentsy; m_Extents.z = Extentsz; }

	void SetWidth(int width) { Width = width; }
	void SetHeight(int height) { Height = height; }

	virtual ~GameObject() {}
private:

	unsigned int loadTexture(char const* path);


	bool isModel;
	int Width, Height;
	glm::vec3 m_Pos, m_Extents, m_Rotation;
	unsigned int m_Texture;
	Shader* m_Shader;
	Model* m_Model;
	LoaderParams* m_Params;


};
