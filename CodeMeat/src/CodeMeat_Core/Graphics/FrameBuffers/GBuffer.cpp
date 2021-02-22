#include "GBuffer.h"

void GBuffer::Init() {

	glGenFramebuffers(1, &m_Gbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_Gbuffer);
	
	// position color buffer
	glGenTextures(1, &m_GPos);
	glBindTexture(GL_TEXTURE_2D, m_GPos);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_GPos, 0);
	// normal color buffer
	glGenTextures(1, &m_GNormal);
	glBindTexture(GL_TEXTURE_2D, m_GNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_GNormal, 0);
	// color + specular color buffer
	glGenTextures(1, &m_AlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, m_AlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_AlbedoSpec, 0);

	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
	glDrawBuffers(3, m_Attachments);

	// create and attach depth buffer (renderbuffer)
	glGenRenderbuffers(1, &m_RBODepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBODepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBODepth);

	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_LPassShader.Use();
	m_LPassShader.SetInt("gPosition", 0);
	m_LPassShader.SetInt("gNormal", 1);
	m_LPassShader.SetInt("gAlbedoSpec", 2);
}

void GBuffer::FirstPass(std::vector<GameObject*> ObjectQueue) {
	glBindFramebuffer(GL_FRAMEBUFFER, m_Gbuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 m_Projection = glm::perspective(glm::radians(m_CameraRef->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 m_View = m_CameraRef->GetViewMatrix();
		m_GPassShader.Use();
		m_GPassShader.SetMat4("Projection", m_Projection);
		m_GPassShader.SetMat4("View", m_Projection);
		for (int i = 0; i < ObjectQueue.size(); i++) {
			ObjectQueue[i]->Draw(m_GPassShader);
		}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::SecondPass(std::vector<Light*> Lightarr) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_LPassShader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_GPos);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_GNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_AlbedoSpec);

	for (unsigned int i = 0; i < Lightarr.size() ; i++)
	{
		switch (Lightarr[i]->GetType()) {
		case 0:
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Direction", Lightarr[i]->GetDir());
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Color", Lightarr[i]->GetColour());
			break;
		case 1:
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Position", Lightarr[i]->GetPos());
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Color", Lightarr[i]->GetColour());
			m_LPassShader.SetFloat("lights[" + std::to_string(i) + "].Quadratic", Lightarr[i]->GetQuadratic());
			m_LPassShader.SetFloat("lights[" + std::to_string(i) + "].Linear", Lightarr[i]->GetLinear());
			break;
		case 2:
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Position", Lightarr[i]->GetPos());
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Color", Lightarr[i]->GetColour());
			m_LPassShader.SetFloat("lights[" + std::to_string(i) + "].Quadratic", Lightarr[i]->GetQuadratic());
			m_LPassShader.SetFloat("lights[" + std::to_string(i) + "].Linear", Lightarr[i]->GetLinear());
			m_LPassShader.SetFloat("lights[" + std::to_string(i) + "].Theta", Lightarr[i]->GetTheta());
			break;
		}
	}
	m_LPassShader.SetVec3("viewPos", m_CameraRef->Position);
	RenderQuad();
}

void GBuffer::Bind() {

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Gbuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
	// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
	// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
	// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
	glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void GBuffer::RenderQuad()
{
	if (m_VAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
