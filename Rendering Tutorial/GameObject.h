#pragma once
#include "stb_image.h"
#include "Object.h"
#include "Shader.h"
#include <string.h>
#include "Model.h"
#include "Camera.h"

class GameObject : public Object
{
public:
	GameObject(LoaderParams* Params, Shader* shader, char const* TexturePath);
	GameObject(LoaderParams* Params, Model* model, Shader* shader);
	GameObject(LoaderParams* Params, Shader* shader);

	void Draw();
	void Update();

	void SetPos(glm::vec3 NewPos) { m_Pos = NewPos; }
	void SetPos(float Posx, float Posy, float Posz) { m_Pos.x = Posx; m_Pos.y = Posy; m_Pos.z = Posz; }

	void SetExtents(glm::vec3 Newextents) { m_Extents = Newextents; }
	void SetExtents(float Extentsx, float Extentsy, float Extentsz) { m_Extents.x = Extentsx; m_Extents.y = Extentsy; m_Extents.z = Extentsz; }

	void SetWidth(int width) { Width = width; }
	void SetHeight(int height) { Height = height; }

	virtual ~GameObject() {}
private:

	unsigned int loadTexture(char const* path);


	bool isModel;
	int Width, Height;
	glm::vec3 m_Pos, m_Extents;
	unsigned int m_Texture;
	Shader* m_Shader;
	Model* m_Model;
	LoaderParams* m_Params;


};
