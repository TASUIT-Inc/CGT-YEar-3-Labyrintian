#include "Engine.h"

Renderer* Renderer::m_Instance = 0;
Physics* Physics::m_Instance = 0;

bool Engine::init() {
	if (Renderer::Instance()->Init()) {
		if (Physics::Instance()->Init()) {
			LoaderParams CubeVertex = LoaderParams(PCUBE);
			LoaderParams SphereVertex = LoaderParams(PSPHERE);
			LoaderParams PyramidVertex = LoaderParams(PPYRAMID);
			LoaderParams PlaneVertex = LoaderParams(PPLANE);

		}
	}
	return true;
}

void Engine::Draw() {

}

void Engine::Render() {

}

void Engine::Update() {

}
