#include "UIContext.h"

bool UIContext::init(GLFWwindow* window)
{
	ImGui::CreateContext();		//Initialises ImGui
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
	ImGui_ImplOpenGL3_NewFrame();	//Creates new frame for drawing ImGui rnederables onto
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UIContext::Draw()
{

	if (uiElem != nullptr)	//Only runs if an Ui element is attached to the Context
	{
		begin();
		UIStyle->UIStyling(BgColor, TxtColor);
		ImGui::Begin("Test", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar); // tell ImGui to begin rendering the Spacified UI Elements
		uiElem();	//Call to Ui element Function
		UIStyle->CleanStyling();
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		uiElem = nullptr;	//Once the Ui element has finished rendering set the Current element to a nullptr
	}
}
