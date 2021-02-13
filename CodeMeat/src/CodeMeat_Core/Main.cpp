#include "CodeMeat.h"

Engine* Engine::m_Instance = 0;

int main()
{
	if (Engine::Instance()->init()) {
		while (Engine::Instance()->GetState()) {
			
			Engine::Instance()->Update();
			Engine::Instance()->Render();
			Engine::Instance()->Draw();
		}
	}

	return 0;
}
