#include "UIContext.h"

bool UIContext::init(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	if (window == NULL)
	{
		std::cout << "Window cannot be found" << std::endl;
		return 0;
	}

	std::cout << "Initialised ImGui stuffs" << std::endl;
	return 1;
}

void UIContext::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UIContext::Draw()
{
	if (UIelem != nullptr)
	{
		begin();
		ImGui::Begin("Test", NULL);
		UIelem();
		ImGui::End();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
