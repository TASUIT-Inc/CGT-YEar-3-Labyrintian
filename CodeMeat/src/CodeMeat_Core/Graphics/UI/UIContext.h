#pragma once
#include "CodeMeat_Core/Graphics/UI/imgui.h"
#include "CodeMeat_Core/Graphics/UI/imgui_impl_glfw.h"
#include "CodeMeat_Core/Graphics/UI/imgui_impl_opengl3.h"
#include <iostream>
#include <functional>
#include "UIElements.h"


class UIElements;

class UIContext
{

public:
	UIContext(GLFWwindow* window) { init(window); }
	~UIContext() {};

	bool init(GLFWwindow* window);
	void begin();
	void SetUIContext(void(*Newfunction)() = nullptr) { uiElem = Newfunction; }	//Set uiElem veriable to functor pointer
	void* GetUIElem() const { return uiElem; }	//getts the current attached UI element

	void Draw();
private:
	void(*uiElem)() = nullptr;		//Pointer to Specified Function that is used to create UI elements
	UIElements* UIStyle;
	ImColor BgColor;				//ImGui Specific formating variables
	ImColor TxtColor;
};
