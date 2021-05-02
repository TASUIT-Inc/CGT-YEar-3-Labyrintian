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
	
	LoadLevel1();

	return EngineState;
}

void Engine::Update() {
	float l_CF = glfwGetTime();
	m_DT = l_CF - m_LT;
	m_LT = l_CF;
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
	Model* Chairmodel = new Model("Chair/Chair.fbx");
	Model* CeilingLight = new Model("Light/Light.fbx");
	//Begining room layout
	GameObject* floor = new GameObject(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	floor->AttachModel(new Model("Labyrinth/Roof.obj"));

	
	Light* RoomLight = new Light(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* SkyLight = new Light(glm::vec3(1.0f), glm::vec3(1.0f, -1.0f, 0.0f));

	R->Submit(floor);
	/*R->Submit(DoorWayTop);
	R->Submit(DoorWayRight);
	R->Submit(DoorWayleft);
	R->Submit(LeftWall);
	R->Submit(RightWall);
	R->Submit(BackWall);
	R->Submit(Celing);
	R->Submit(Chair);
	R->Submit(light);
	R->Submit(CorridorRightWall);
	R->Submit(Maze_LeftWall);*/

	R->Submit(RoomLight);
	R->Submit(SkyLight);




}