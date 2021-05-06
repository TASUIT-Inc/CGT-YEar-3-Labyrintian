#include "Engine.h"
#include "al.h"
#include "alc.h"

Renderer* Renderer::m_Instance = 0;
Physics* Physics::m_Instance = 0;


bool Engine::init() {
	if (Renderer::Instance()->Init()) { //initialise both the renderer and physics components of the engine
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

	AudioDevice::init(); // initialise the audio manager

	myMusic = new MusicBuffer("PauseMenu.wav"); // Load sound file into the audio buffer
	AudioDevice::get()->SetGain(0.5f); // set volume to 50%
	

	LoadLevel1(); // Load all gameObjects needed for the first level
	myMusic->Play(); // Tell the Audiomanager to play the sound file loaded in the audio buffer

	return EngineState;
}

void Engine::Update() {
	float l_CF = glfwGetTime();
	m_DT = l_CF - m_LT;		//timer for time inbetween update cycles
	m_LT = l_CF;

	
	if (myMusic->isPlaying())
	{
		myMusic->UpdateBufferStream();
	}
	REngine::Instance()->Input(m_DT); // check for user input
	PEngine::Instance()->Update(REngine::Instance()->GetCamera() ,REngine::Instance()->GetObjectListRef(), m_DT); // physics update call
}


void Engine::Draw() {
	REngine::Instance()->Draw(); // render call
}

void Engine::Clean() {
	REngine::Instance()->Clean(); //Clear Renderer and Physics Components of Data
	PEngine::Instance()->Clean();
}


void Engine::LoadLevel1() 
{
	Renderer* R = REngine::Instance(); // Store reference to the render in local variable
	
	LoaderParams* cube =  new LoaderParams(PCUBE);

	Model* Chair = new Model("Chair/Chair.obj");
	Model* Door = new Model("Door/Door.obj");	//Load needed models and LoaderParams
	Model* CLight = new Model("Light/CLight.obj");
	Model* Vase = new Model("Vase/Vase.obj");


	GameObject* floor = new GameObject(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));	//The main map that the player sees
	floor->AttachModel(new Model("Labyrinth/Roof.obj")); // assign a model tot he object then generate colliders off of the mesh data
	floor->GenerateColliders();

	GameObject* Puzzle = new GameObject(glm::vec3(-2.8f, 0.15f, -12.7f), glm::vec3(1.0f));
	Puzzle->AttachModel(new Model("Puzle/Puzzle Board.obj"));	//Create Object for the puzzle board, attatch the model and a AABB then Set the Objects Tag
	Puzzle->AttachBoundingBox(Puzzle->GetKinematics()->m_Transform.GetPos() + glm::vec3(1.0f, 0.0f, -4.5f), glm::vec3(0.2f, 1.0f, 0.1f));
	Puzzle->SetTag("PUZZLE");

	GameObject* hint1 = new GameObject(glm::vec3(-9.7f, 0.1f, -0.8f), glm::vec3(1.0f));
	hint1->AttachLoaderParams(cube);
	hint1->AttachTexture("5.png");

	GameObject* hint2 = new GameObject(glm::vec3(4.32, 0.2f, -2.3f), glm::vec3(1.0f));
	hint2->AttachLoaderParams(cube);
	hint2->AttachTexture("2.png");
																							//Create the Hints that show the desired numbers then assign a texture to each one
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

	GameObject* chair1 = new GameObject(glm::vec3(-11.0f, -0.9f, -12.0f), glm::vec3(0.2f));
	chair1->AttachModel(Chair);
																								//Create Objects then assign them the models from above
	GameObject* light1 = new GameObject(glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(0.2f));
	light1->AttachModel(CLight);

	GameObject* vase1 = new GameObject(glm::vec3(-2.25f, -0.02f, -2.25f), glm::vec3(1.0f));
	vase1->AttachModel(Vase);
	

	
	Light* RoomLight1 = new Light(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight2 = new Light(glm::vec3(-6.5f, 0.5f, 0.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight3 = new Light(glm::vec3(6.6f, 0.5f, 0.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight4 = new Light(glm::vec3(7.1f, 0.5f, -7.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight5 = new Light(glm::vec3(0.3f, 0.5f, -7.0f), glm::vec3(1.0f), 0.8, 0.8);			//Create point lights and place them throughout the map
	Light* RoomLight6 = new Light(glm::vec3(-6.7f, 0.5f, -7.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight7 = new Light(glm::vec3(13.5f, 0.5f, -7.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight8 = new Light(glm::vec3(6.6f, 0.5f, -14.15f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight9 = new Light(glm::vec3(-0.2f, 0.5f, -14.0f), glm::vec3(1.0f), 0.8, 0.8);
	Light* RoomLight10 = new Light(glm::vec3(6.9f, 0.5f, -21.0f), glm::vec3(1.0f), 0.8, 0.8);
	
	
	R->Submit(floor);
	R->Submit(Puzzle);
	R->Submit(hint1);
	R->Submit(hint2);
	R->Submit(hint3);			//Pushing all game Objects to a Vector stored in Renderer.cpp
	R->Submit(hint4);
	R->Submit(door);
	R->Submit(chair1);
	R->Submit(light1);
	R->Submit(vase1);


	R->Submit(RoomLight1);
	R->Submit(RoomLight2);
	R->Submit(RoomLight3);
	R->Submit(RoomLight4);
	R->Submit(RoomLight5);		//Pushing all lights to a Vectors stored in Renderer.cpp
	R->Submit(RoomLight6);
	R->Submit(RoomLight7);
	R->Submit(RoomLight8);
	R->Submit(RoomLight9);
	
	std::cout << "Hello, and welcome to Labarytin, The goal of you the player" << std::endl; 
	std::cout << "Is to locate all puzzle hints, exit door and puzzle hidden throught the map" << std::endl;
	std::cout << "In order to escape you need to input the correct series of numbers to unlock the door" << std::endl;
	std::cout << "Once you input the correct code and test it, if you are correct then a sound will play" << std::endl;
	std::cout << "Once you hear this sound you can exit the map and close the game" << std::endl;
	std::cout << "The Controls for the game are as follows:" << std::endl;								//Display overall point of the game and controls
	std::cout << "Movement - W,S,A,D control fowards, backwards, left and right movement respectivly" << std::endl;
	std::cout << "The Mouse is used to look around the enviroment" << std::endl;
	std::cout << "I - This key brings up the puzzle UI, you can release this key to hid the UI" << std::endl;
	std::cout << "Esc - This key brings up the main menu here you can exit the game, again release this key to close the main menu" << std::endl;
	std::cout << "Have fun, and most importantly enjoy our small tech demo!" << std::endl;


}