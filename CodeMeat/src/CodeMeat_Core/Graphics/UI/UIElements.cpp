#include "UIElements.h"

void UIElements::PauseMenu()
{
	
	ImGui::Text("This is normal text.");
	if (ImGui::Button("Resume", ImVec2(120, 120)))
	{
		//Do nothing
		std::cout << "Resume";
	}
	if (ImGui::Button("Options", ImVec2(120, 120)))
	{
		std::cout << "Options";
		//Do nothing
	}
	if (ImGui::Button("Exit", ImVec2(120, 120)))
	{
		//Do nothing
		std::cout << "Exit";
	}
	
}

void UIElements::UIStyling(ImColor col, ImColor col2)
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(col));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(col2));
}

void UIElements::CleanStyling()
{
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}
