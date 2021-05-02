#include "Engine.h"
#include "al.h"
#include "alc.h"

Renderer* Renderer::m_Instance = 0;
Physics* Physics::m_Instance = 0;


bool Engine::init() {
	if (Renderer::Instance()->Init()) {
		EngineState = true;
		if (Physics::Instance()->Init()) {
			EngineState = true;
		}
		else {
			EngineState = false;
			std::cout << "Physics Init Failed!" << std::endl;
		}
	}
	else {
		EngineState = false;
		std::cout << "Renderer Init Failed!" << std::endl;
	}
	AudioDevice::init();
	//ALCdevice* bob;

	//uint32_t snd1 = AudioBuffer::get()->addAudioFX("Error.wav");
	//AudioSource speaker;

	GameObject* l_Cube =new GameObject(glm::vec3(0.0f), glm::vec3(5.0f, 1.0f, 5.0f), glm::vec3(0.0f));


	myMusic = new MusicBuffer("PauseMenu.wav");

	//myMusic->Play();
	//speaker.Play(snd1);
	//room instances
		//room 1
	l_Cube->AddInstance(glm::vec3(4.5f, 2.0f, 0.0f), glm::vec3(0.5f, 1.0f, 5.0f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(-4.5f, 2.0f, 0.0f), glm::vec3(0.5f, 1.0f, 5.0f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(0.0f, 2.0f, 4.5f), glm::vec3(5.0f, 1.0f, 0.5f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(2.5f, 2.0f, -4.5f), glm::vec3(1.75f, 1.0f, 0.5f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(-2.5f, 2.0f, -4.5f), glm::vec3(1.75f, 1.0f, 0.5f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(0.0f, 2.75f, -4.5f), glm::vec3(0.75f, 0.25f, 0.5f), glm::vec3(0.0f));


	REngine::Instance()->Submit(l_Cube);

	Light* l_SkyLight =new Light(glm::vec3(1.0f), glm::vec3(-0.2f, -1.0f, -0.3f));
	//Light* l_PL = new Light(glm::vec3(0.0f), glm::vec3(1.0f), 0.8f, 1.5f);
	REngine::Instance()->Submit(l_SkyLight);
	//REngine::Instance()->Submit(l_PL);
	return EngineState;
}

void Engine::Update() {
	float l_CF = glfwGetTime();
	m_DT = l_CF - m_LT;
	m_LT = l_CF;
	REngine::Instance()->processInput(m_DT);
	if (myMusic->isPlaying())
	{
		myMusic->UpdateBufferStream();
	}
}


void Engine::Draw() {
	REngine::Instance()->Draw();
	
	
}

void Engine::Clean() {

}
