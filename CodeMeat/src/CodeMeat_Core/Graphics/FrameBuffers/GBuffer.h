#pragma once
#include "Buffer.h"
#include "CodeMeat_Core/Objects/GameObject/GameObject.h"
#include "CodeMeat_Core/Graphics/Camera/Camera.h"
#include "CodeMeat_Core/Graphics/Ligths/Light.h"

class GameObject;
class Shader;
class Camera;
class Light;

class GBuffer : public Buffer {
public:
	GBuffer(Camera *camera) : Buffer() ,m_CameraRef(camera) ,m_GPassShader(Shader("VS-Default.txt","FS-Default.txt")), m_LPassShader(Shader("VS-LightingShader.txt","FS-LightingShader.txt")), m_VAO(0) {
		Init();
		RenderQuad();
	}

	void FirstPass(std::vector<GameObject*> ObjectQueue);
	void SecondPass(std::vector<Light*> LightQueue);
	void Bind();
private:
	unsigned int m_Gbuffer, m_AlbedoSpec, m_GPos, m_GNormal, m_RBODepth;

	unsigned int m_Attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

	void Init();
	void RenderQuad();

	Camera* m_CameraRef;
	Shader m_GPassShader, m_LPassShader;

	unsigned int m_VAO, m_VBO;
};
