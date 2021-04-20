#pragma once
#include "CodeMeat_Core/Graphics/UI/imgui.h"
#include "CodeMeat_Core/Graphics/UI/imgui_impl_glfw.h"
#include "CodeMeat_Core/Graphics/UI/imgui_impl_opengl3.h"
#include <iostream>
#include <functional>
#include "UIElements.h"

class UIContext
{

public:
	UIContext(GLFWwindow* window) { init(window); }
	~UIContext() {};

	bool init(GLFWwindow* window);
	void begin();
	void SetUIContext(std::function<void(UIElements*)> newfunction) { UIelem = newfunction; }

	void Draw();
private:
	std::function<void(UIElements*)> UIelem = nullptr;
	
};