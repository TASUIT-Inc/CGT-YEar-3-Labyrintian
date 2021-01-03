#include "Renderer.h"

Renderer::Renderer(Camera* camera, const unsigned int width, const unsigned int height, std::vector<GameObject*>* objects) : m_Camera(camera), SCR_WIDTH(width), SCR_HEIGHT(height), m_Objects(objects) {

	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

	m_Attachments[0] = GL_COLOR_ATTACHMENT0;
	m_Attachments[1] = GL_COLOR_ATTACHMENT1;
	m_Attachments[2] = GL_COLOR_ATTACHMENT2;

	glDrawBuffers(3, m_Attachments);

	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};
	// setup plane VAO
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

}


void  Renderer::InitShaderSamples(Shader* shader) {
	shader->Use();
	shader->SetInt("gPosition", 0);
	shader->SetInt("gNormal", 1);
	shader->SetInt("gAlbedoSpec", 2);
}

void Renderer::RenderQuad() {

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Renderer::SetLightDirection(Shader* shader, Light* newLight) {
	m_Lights.push_back(newLight);
	shader->Use();
	shader->SetInt("NR_LIGHTS", m_Lights.size());
	int i = m_Lights.size();

	shader->SetVec3("lights[" + std::to_string(i) + "].direction", m_Lights[i]->GetDir());
	shader->SetVec3("lights[" + std::to_string(i) + "].Color", m_Lights[i]->GetColour());
}

void Renderer::SetPointLightVariables(Shader* shader, Light* newLight) {
	m_Lights.push_back(newLight);
	shader->Use();
	shader->SetInt("NR_LIGHTS", m_Lights.size());
	int i = m_Lights.size();

	shader->SetVec3("lights[" + std::to_string(i) + "].Position", m_Lights[i]->GetPos());
	shader->SetFloat("lights[" + std::to_string(i) + "].linear", m_Lights[i]->GetLinear());
	shader->SetFloat("lights[" + std::to_string(i) + "].quadratic", m_Lights[i]->GetQuadratic());
	shader->SetVec3("lights[" + std::to_string(i) + "].Color", m_Lights[i]->GetColour());
}

void Renderer::SetSpotlightVariables(Shader* shader, Light* newLight) {
	m_Lights.push_back(newLight);
	shader->Use();
	shader->SetInt("NR_LIGHTS", m_Lights.size());
	int i = m_Lights.size();

	shader->SetVec3("lights[" + std::to_string(i) + "].Position", m_Lights[i]->GetPos());
	shader->SetVec3("lights[" + std::to_string(i) + "].direction", m_Lights[i]->GetDir());
	shader->SetFloat("lights[" + std::to_string(i) + "].theta", m_Lights[i]->GetTheta());
	shader->SetVec3("lights[" + std::to_string(i) + "].Color", m_Lights[i]->GetColour());
}

void Renderer::GeometryPass(Shader* shader) {
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 Projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = m_Camera->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	shader->Use();
	shader->SetMat4("projection", Projection);
	shader->SetMat4("view", view);
	for (int i = 0; i < m_Objects->size(); i++) {
		m_Objects->operator[](i)->Draw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::LightingPass(Shader* shader) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);


	shader->SetInt("NR_LIGHTS", m_Lights.size());
	shader->SetInt("ArrSize", m_Lights.size());
	for (int i = 0; i < m_Lights.size(); i++) {
		shader->SetInt("lights[" + std::to_string(i) + "].Type", m_Lights[i]->GetType());
		switch (m_Lights[i]->GetType()) {
		case 0:
			shader->SetVec3("lights[" + std::to_string(i) + "].Direction", m_Lights[i]->GetDir());
			shader->SetVec3("lights[" + std::to_string(i) + "].Color", m_Lights[i]->GetColour());
			break;
		case 1:
			shader->SetVec3("lights[" + std::to_string(i) + "].Position", m_Lights[i]->GetPos());
			shader->SetFloat("lights[" + std::to_string(i) + "].Linear", m_Lights[i]->GetLinear());
			shader->SetFloat("lights[" + std::to_string(i) + "].Quadratic", m_Lights[i]->GetQuadratic());
			shader->SetVec3("lights[" + std::to_string(i) + "].Color", m_Lights[i]->GetColour());
			break;
		case 2:
			shader->SetVec3("lights[" + std::to_string(i) + "].Position", m_Lights[i]->GetPos());
			shader->SetVec3("lights[" + std::to_string(i) + "].Direction", m_Lights[i]->GetDir());
			shader->SetFloat("lights[" + std::to_string(i) + "].Theta", m_Lights[i]->GetTheta());
			shader->SetVec3("lights[" + std::to_string(i) + "].Color", m_Lights[i]->GetColour());
			break;
		}
	}
	shader->SetVec3("viewPos", m_Camera->GetPos());
}

void  Renderer::BindFrameBuffers() {

	glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
