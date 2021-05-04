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
	myMusic = new MusicBuffer("PauseMenu.wav");

	//myMusic->Play();
	//speaker.Play(snd1);
	//room instances
		//room 1
	LoadLevel1();


	return EngineState;
}

void Engine::Update() {
	float l_CF = glfwGetTime();
	m_DT = l_CF - m_LT;
	m_LT = l_CF;

	
	if (myMusic->isPlaying())
	{
		myMusic->UpdateBufferStream();
	}
	REngine::Instance()->Input(m_DT);
	PEngine::Instance()->Update(REngine::Instance()->GetCamera() ,REngine::Instance()->GetObjectListRef(), m_DT);
}


void Engine::Draw() {
	REngine::Instance()->Draw();
	
	
}

void Engine::Clean() {

}


void Engine::LoadLevel1() 
{
	Renderer* R = REngine::Instance();
	LoaderParams* cube =  new LoaderParams(PCUBE);
	Model* Door = new Model("Door/Door.obj");
	//Begining room layout
	GameObject* floor = new GameObject(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	floor->AttachModel(new Model("Labyrinth/Roof.obj"));

	GameObject* Puzzle = new GameObject(glm::vec3(-2.8f, 0.15f, -12.7f), glm::vec3(1.0f));
	Puzzle->AttachModel(new Model("Puzle/Puzzle Board.obj"));
	Puzzle->AttachBoundingBox(Puzzle->GetKinematics()->m_Transform.GetPos() + glm::vec3(1.0f, 0.0f, -4.5f), glm::vec3(0.2f, 1.0f, 0.1f));
	Puzzle->SetTag("PUZZLE");

	GameObject* hint1 = new GameObject(glm::vec3(-9.7f, 0.1f, -0.8f), glm::vec3(1.0f));
	hint1->AttachLoaderParams(cube);
	hint1->AttachTexture("5.png");

	GameObject* hint2 = new GameObject(glm::vec3(4.32, 0.2f, -2.3f), glm::vec3(1.0f));
	hint2->AttachLoaderParams(cube);
	hint2->AttachTexture("2.png");

	GameObject* hint3 = new GameObject(glm::vec3(11.3, 0.2f, -9.4f), glm::vec3(1.0f));
	hint3->AttachLoaderParams(cube);
	hint3->AttachTexture("5.png");

	GameObject* hint4 = new GameObject(glm::vec3(4.35, 0.2f, -16.4f), glm::vec3(1.0f));
	hint4->AttachLoaderParams(cube);

	hint4->AttachTexture("9.png");

	GameObject* door = new GameObject(glm::vec3(-13.5f,0.0f,-35.0f), glm::vec3(0.2f));
	door->AttachModel(Door);
	door->AttachBoundingBox(door->GetKinematics()->m_Transform.GetPos(), glm::vec3(0.1f, 1.0f, 1.0f));
	door->SetTag("DOOR");
	

	
	Light* RoomLight1 = new Light(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight2 = new Light(glm::vec3(-6.5f, 0.5f, 0.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight3 = new Light(glm::vec3(6.6f, 0.5f, 0.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight4 = new Light(glm::vec3(7.1f, 0.5f, -7.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight5 = new Light(glm::vec3(0.3f, 0.5f, -7.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight6 = new Light(glm::vec3(-6.7f, 0.5f, -7.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight7 = new Light(glm::vec3(13.5f, 0.5f, -7.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight8 = new Light(glm::vec3(6.6f, 0.5f, -14.15f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight9 = new Light(glm::vec3(-0.2f, 0.5f, -14.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight10 = new Light(glm::vec3(6.9f, 0.5f, -21.0f), glm::vec3(1.0f), 0.8, 0.8);
	
	
	R->Submit(floor);
	R->Submit(Puzzle);
	R->Submit(hint1);
	R->Submit(hint2);
	R->Submit(hint3);
	R->Submit(hint4);
	R->Submit(door);

	R->Submit(RoomLight1);
	R->Submit(RoomLight2);
	R->Submit(RoomLight3);
	R->Submit(RoomLight4);
	R->Submit(RoomLight5);
	R->Submit(RoomLight6);
	R->Submit(RoomLight7);
	R->Submit(RoomLight8);
	R->Submit(RoomLight9);

}