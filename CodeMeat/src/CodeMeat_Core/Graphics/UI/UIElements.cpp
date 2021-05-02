#include "UIElements.h"

void UIElements::PauseMenu()
{
	
	ImGui::Text("This is normal text.");
	if (ImGui::Button("Resume", ImVec2(120, 120)))
	{
		static AudioSource speaker;
		//Do nothing
		speaker.Play(SE_LOAD("Error.wav"));
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

void UIElements::PuzzleTest()
{
	static int c1, c2, c3, c4;
	static bool a1 = false;
	static bool a2 = false;
	static bool a3 = false;
	static bool a4 = false;
	static bool answer = false;
	static bool wrong = false;

	static bool input = false;

	static int userInput = 0;

	
	
	ImGui::OpenPopup("Puzzle");

	
	while (ImGui::BeginPopup("Puzzle"))
	{

		
		if (userInput == 0)
		{
			ImGui::Text("%d", c1);
		}
		if (userInput == 1)
		{
			ImGui::Text("%d", c2);
		}
		if (userInput == 2)
		{
			ImGui::Text("%d", c3);
		}
		if (userInput == 3)
		{
			ImGui::Text("%d", c4);
		}

		//if (wrong)
		//{
		//	ImGui::TextColored(ImVec4(1.0, 0.1, 0.1, 1.0), "Incorrect");
		//}
		//if (!wrong)
		//{
		//	ImGui::TextColored(ImVec4(0.0, 0.1, 1.0, 1.0), "correct");
		//}
		
		if (ImGui::Button("1", ImVec2(120, 120)))
		{
				
			std::cout << "c1";
				a1 = true;
				userInput++;
				input = true;
				c1 = 1;
				//testInput[0] = c1;
				/**/
				 
				//Do nothing
		}

		if (ImGui::Button("2", ImVec2(120, 120)))
		{
			std::cout << "c2";
				a2 = true;
				userInput++;
				c2 = 2;
			//Do nothing
		}

		if (ImGui::Button("3", ImVec2(120, 120)) )
		{
			std::cout << "c3";
			userInput++;
			c3 = 3;
			//if (userInput == 2) {
			//	//a3 = true;
			//	c1 = 3;
			//}
				 
			//Do nothing
		}
		//std::cout << a3 << std::endl;

		if (ImGui::Button("4", ImVec2(120, 120)))
		{
			std::cout << "c4";
				a4 = true;
				c4 = 4;

			//Do nothing
		}

			
			
		if (ImGui::Button("Return", ImVec2(120, 120)))
		{
			if (a1 == true && a2 == true && a3 == true && a4 == true)
			{
				answer = true;
				std::cout << answer;
				break;
				ImGui::EndPopup();

			}
			else
			{
				wrong = true;
				ImGui::Checkbox("Incorrect", &wrong);
				std::cout << "Error: Wrong Code" << std::endl;
					
			}
		}
	}
	ImGui::EndPopup();
	
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
