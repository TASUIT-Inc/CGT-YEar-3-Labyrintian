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

	float quadVertices[] = {	//Create a quad that a snapshot of the current scene is drawn onto at the end of the draw call
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

	m_LPassShader.Use();
	m_LPassShader.SetInt("m_GPos", 0);
	m_LPassShader.SetInt("m_GNormal", 1);	//Set Shader Specific values
	m_LPassShader.SetInt("m_AlbedoSpec", 2);
}

void GBuffer::FirstPass(Camera* camera, std::vector<GameObject*> *ObjectQueue) {
	glBindFramebuffer(GL_FRAMEBUFFER, m_Gbuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 m_Projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.001f, 1000.0f);
		glm::mat4 m_View = camera->GetViewMatrix();
		m_GPassShader.Use();									//Calculate camera specific matrices and send them to the Specified shader
		m_GPassShader.SetMat4("Projection", m_Projection);
		m_GPassShader.SetMat4("View", m_View);
		for (int i = 0; i < ObjectQueue->size(); i++) {
			ObjectQueue->operator[](i)->Draw(&m_GPassShader);		//Draw call for game Objects
		}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::SecondPass(Camera* camera, std::vector<Light*> *Lights) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_LPassShader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_GPos);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_GNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_AlbedoSpec);


	m_LPassShader.SetInt("NR_LIGHTS", Lights->size());
	m_LPassShader.SetInt("ArrSize", Lights->size());
	for (int i = 0; i < Lights->size() ; i++)					//for each light get the lights type, directional, point or cone, then set type specific variables in the GBuffer shader
	{
		m_LPassShader.SetInt("lights[" + std::to_string(i) + "].Type", Lights->operator[](i)->GetType());
		switch (Lights->operator[](i)->GetType()) {
		case 0:	//Directional Lights
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Direction", Lights->operator[](i)->GetDir());
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Color", Lights->operator[](i)->GetColour());
			break;
		case 1:	//Point Lights
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Position", Lights->operator[](i)->GetPos());
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Color", Lights->operator[](i)->GetColour());
			m_LPassShader.SetFloat("lights[" + std::to_string(i) + "].Quadratic", Lights->operator[](i)->GetQuadratic());
			m_LPassShader.SetFloat("lights[" + std::to_string(i) + "].Linear", Lights->operator[](i)->GetLinear());
			break;
		case 2:	//Cone Ligths
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Position", Lights->operator[](i)->GetPos());
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Color", Lights->operator[](i)->GetColour());
			m_LPassShader.SetVec3("lights[" + std::to_string(i) + "].Direction", Lights->operator[](i)->GetDir());
			m_LPassShader.SetFloat("lights[" + std::to_string(i) + "].Theta", Lights->operator[](i)->GetTheta());
			break;
		}
	}
	m_LPassShader.SetVec3("viewPos", camera->GetPos());
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
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);	//Finally render the screenQuad and Apply the Loaded Texture of the Scene
	glBindVertexArray(0);
}
