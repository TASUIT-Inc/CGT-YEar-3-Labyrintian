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

	LoaderParams CubeVertex = LoaderParams(PCUBE);
	LoaderParams SphereVertex = LoaderParams(PSPHERE);
	LoaderParams PyramidVertex = LoaderParams(PPYRAMID);
	LoaderParams PlaneVertex = LoaderParams(PPLANE);

	return EngineState;
}

void Engine::Draw() {

	REngine::Instance()->Flush();

}

void Engine::Render() {

	REngine::Instance()->Begin();

	//REngine::Instance()->Submit();

}

void Engine::Update() {

}

void Engine::Clean() {

}
