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
	UIStyle = new UIElements();
	BgColor = ImVec4(1.0, 0.5, 0.3, 1.0);
	TxtColor = ImVec4(0.1, 0.2, 0.9, 1.0);
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

	if (uiElem != nullptr)
	{
		begin();
		UIStyle->UIStyling(BgColor, TxtColor);
		ImGui::Begin("Test", NULL);
		uiElem();
		UIStyle->CleanStyling();
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		uiElem = nullptr;
	}
}
