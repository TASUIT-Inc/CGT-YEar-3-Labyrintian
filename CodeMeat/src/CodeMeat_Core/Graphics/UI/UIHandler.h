#ifndef __UIHandler__
#define __UIHandler__
#include "CodeMeat_Core/Graphics/UI/imgui.h"
#include "CodeMeat_Core/Graphics/UI/imgui_impl_glfw.h"
#include "CodeMeat_Core/Graphics/UI/imgui_impl_opengl3.h"
#include "CodeMeat_Core/Deps/Commons.h"
#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Deps/Output.h"
#include <iostream>


class UIHandler
{
public:
	bool Init(GLFWwindow* window);

	static UIHandler* Instance() {

		if (m_Instance == 0) {
			m_Instance = new UIHandler();
			return m_Instance;
		}
		return m_Instance;
	}
	void Draw();
	void Render();
	void Clean();
	void createPauseMenu(bool* open);


	////testing variables--to be deleted
	/*ImGuiIO& io;
	ImFont* font1;
	ImFont* Title;*/
	bool* isOpen = NULL;
	const char* titlename = "Paused";
	float window_width = 1440.f;
	float window_height = 720.f;
	float s_width = 1920.f;
	float s_height = 1080.f;
	ImGuiWindowFlags windowFlag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
	ImGuiCol UiCol = ImGuiCol_TitleBgActive | ImGuiCol_WindowBg;
	ImVec4 TitleCol = ImVec4(0.5f, 0.3f, 0.0f, 1.0f);
	ImVec4 WindowCol = ImVec4(1.f, 0.8f, 0.0f, 1.0f);
	ImVec4 WindowBGCol = ImVec4(0.5f, 0.3f, 0.0f, .4f);
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	//UIHandler() : isOpen(NULL) {};
	virtual ~UIHandler() {};

private:
	static UIHandler* m_Instance;
	
};
typedef UIHandler UIEngine;
#endif //!__UIHandler__

