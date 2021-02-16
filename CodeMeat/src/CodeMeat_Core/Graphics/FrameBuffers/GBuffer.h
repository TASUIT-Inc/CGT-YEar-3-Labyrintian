#pragma once
#include "Buffer.h"
#include "CodeMeat_Core/Graphics/Shaders/Shader.h"

class GBuffer : public Buffer {
public:
	GBuffer() : Buffer() {
		Init();
	}

	void FirstPass();
	void SecondPass(Shader* shader);
	void Bind();
private:
	unsigned int m_Gbuffer, m_AlbedoSpec, m_GPos, m_GNormal, m_RBODepth;

	unsigned int m_Attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

	void Init();
	
};
