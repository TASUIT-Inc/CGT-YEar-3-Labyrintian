#include "Engine.h"

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

	Model* shotgun=new Model("E1M1/Shotgun.obj");

	GameObject* m_Cube =new GameObject(glm::vec3(5.0f, 0.5f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	m_Cube->AttachModel(shotgun);
	/*GameObject* m_Pyramid =new GameObject(glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	m_Pyramid->AttachLoaderParams(new LoaderParams(PPYRAMID));
	GameObject* m_Plane =new GameObject(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	m_Plane->AttachLoaderParams(new LoaderParams(PPLANE));*/

	REngine::Instance()->Submit(m_Cube);
	/*REngine::Instance()->Submit(m_Pyramid);
	REngine::Instance()->Submit(m_Plane);
*/
	Light m_SkyLight = Light(glm::vec3(1.0f), glm::vec3(5.0f, -5.0f, 0.0f));

	return EngineState;
}

void Engine::Update() {
	float m_CF = glfwGetTime();
	m_DT = m_CF - m_LT;
	m_LT = m_CF;
}

void Engine::Render() {
	REngine::Instance()->Begin();
}

void Engine::Draw() {

	REngine::Instance()->Flush();
	REngine::Instance()->End();

}

void Engine::Clean() {

}
