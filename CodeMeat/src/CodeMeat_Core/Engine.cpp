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

	ALCdevice* bob;

	GameObject* l_Cube =new GameObject(glm::vec3(0.0f), glm::vec3(5.0f, 1.0f, 5.0f), glm::vec3(0.0f));
	GameObject* l_Chair = new GameObject(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.02f, 0.02f), glm::vec3(0.0f));
	l_Chair->AttachModel(new Model("Chair/Chair.fbx"));
	/*GameObject* l_Book = new GameObject(glm::vec3(10.0f, 0.0f, 5.0f), glm::vec3(5.0f, 1.0f, 5.0f), glm::vec3(0.0f));
	l_Book->AttachModel(new Model("Book/Book.fbx"));*/
	GameObject* l_Post = new GameObject(glm::vec3(15.0f, -28.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.0f));
	l_Post->AttachModel(new Model("Light/Light.fbx"));
	GameObject* l_Light = new GameObject(glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.02f, 0.02f), glm::vec3(0.0f));
	l_Light->AttachModel(new Model("Lamp Post/Lamp Post.fbx"));
	GameObject* l_Door = new GameObject(glm::vec3(25.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.0f));
	l_Door->AttachModel(new Model("Door/Door.fbx"));
	GameObject* l_Vase = new GameObject(glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.0f));
	l_Vase->AttachModel(new Model("Vase/Vase.fbx"));

	//room instances
		//room 1
	l_Cube->AddInstance(glm::vec3(4.5f, 2.0f, 0.0f), glm::vec3(0.5f, 1.0f, 5.0f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(-4.5f, 2.0f, 0.0f), glm::vec3(0.5f, 1.0f, 5.0f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(0.0f, 2.0f, 4.5f), glm::vec3(5.0f, 1.0f, 0.5f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(2.5f, 2.0f, -4.5f), glm::vec3(1.75f, 1.0f, 0.5f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(-2.5f, 2.0f, -4.5f), glm::vec3(1.75f, 1.0f, 0.5f), glm::vec3(0.0f));
	l_Cube->AddInstance(glm::vec3(0.0f, 2.75f, -4.5f), glm::vec3(0.75f, 0.25f, 0.5f), glm::vec3(0.0f));

	REngine::Instance()->Submit(l_Cube);
	REngine::Instance()->Submit(l_Chair);
	//REngine::Instance()->Submit(l_Book);
	REngine::Instance()->Submit(l_Post);
	REngine::Instance()->Submit(l_Light);
	REngine::Instance()->Submit(l_Door);
	REngine::Instance()->Submit(l_Vase);

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
}

void Engine::Draw() {
	REngine::Instance()->Draw();
}

void Engine::Clean() {

}
