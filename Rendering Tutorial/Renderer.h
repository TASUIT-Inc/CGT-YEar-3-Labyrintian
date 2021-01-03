#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "GameObject.h"
class Renderer
{
public:
	Renderer(Camera* camera, const unsigned int width, const unsigned int height, std::vector<GameObject*>* objects);

	void InitShaderSamples(Shader* shader);

	void SetLightDirection(Shader* shader, Light* newLight);

	void SetPointLightVariables(Shader* shader, Light* newLight);

	void SetSpotlightVariables(Shader* shader, Light* newLight);

	void GeometryPass(Shader* shader);

	void LightingPass(Shader* shader);

	void RenderQuad();

	void AddLight(Light* newlight) { m_Lights.push_back(newlight); }

	void BindFrameBuffers();

	glm::mat4 GetModelMatrix() { return model; }

	void setWidth(int Width) { SCR_WIDTH = Width; }
	void setHeight(int Height) { SCR_HEIGHT = Height; }

private:
	unsigned int gBuffer, gPosition, gNormal, gAlbedoSpec, rboDepth, m_Attachments[3], quadVAO, quadVBO;
	int SCR_WIDTH, SCR_HEIGHT;

	glm::mat4 view, Projection, model;

	Camera* m_Camera;
	std::vector<Light*> m_Lights;
	std::vector<GameObject*>* m_Objects;

protected:


};



