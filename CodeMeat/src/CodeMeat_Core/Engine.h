#ifndef __Engine__
#define __Engine__


#include "CodeMeat_Core/Graphics/UI/UIHandler.h"
#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Deps/Output.h"
#include "CodeMeat_Core/Graphics/Renderer.h"
#include "CodeMeat_Core/Physics/Physics.h"
#include "CodeMeat_Core/Objects/Player.h"
#include "CodeMeat.h"

class Renderer;
class Physics;
class UIHandler;

class Engine
{
public:
	bool init();
	void Render();
	void Draw();
	void Update();
	void Clean();

	bool GetState() { return EngineState; }

	static Engine* Instance() {
		if (m_Instance == 0) {
			m_Instance = new Engine();
			return m_Instance;
		}
		return m_Instance;
	}

private:
	bool EngineState;
	float m_DT, m_LT;
	Player m_Player;
	static Engine* m_Instance;

	Engine() {}
	virtual ~Engine() {}

};
typedef Engine GEngine;
#endif //!__Engine__
