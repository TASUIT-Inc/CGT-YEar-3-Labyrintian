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
	GameObject(LoaderParams* Params, Shader* shader, char const* TexturePath, Camera* camera);
	GameObject(LoaderParams* Params, Model* model, Shader* shader, Camera* camera);

	void Draw();
	void Update();

	void SetPos(glm::vec3 NewPos) { m_Pos = NewPos; }
	void SetPos(float Posx, float Posy, float Posz) { m_Pos.x = Posx; m_Pos.y = Posy; m_Pos.z = Posz; }

	void SetWidth(int width) { Width = width; }
	void SetHeight(int height) { Height = height; }

	virtual ~GameObject() {}
private:

	unsigned int loadTexture(char const* path);


	bool isModel;
	int Width, Height;
	glm::vec3 m_Pos;
	unsigned int m_Texture;
	Shader* m_Shader;
	Model* m_Model;
	Camera* m_Camera;
	LoaderParams* m_Params;


};
