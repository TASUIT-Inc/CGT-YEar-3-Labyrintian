#include "UIElements.h"

void UIElements::PauseMenu()	//Functionality and Looks of the Pause menu
{
	ImGui::SetWindowFontScale(1.0f);	//Set the Font size to 1
	ImGui::OpenPopup("Pause Menu");		//Tell ImGui to open a popup with the desired title
	
	while (ImGui::BeginPopup("Pause Menu")) {	//while the popup is open Draw all Ui Elements
		if (ImGui::Button("Resume", ImVec2(120, 120)))	//Button with text Resume
		{
			static AudioSource speaker;
			//Do nothing
			speaker.Play(SE_LOAD("Error.wav"));
			std::cout << "Resume";
		}
		if (ImGui::Button("Options", ImVec2(120, 120)))  //Button with text Options
		{
			std::cout << "Options";
			//Do nothing
		}
		if (ImGui::Button("Exit", ImVec2(120, 120)))  //Button with text Exit
		{
			Engine::Instance()->SetState();
		}
	}
	ImGui::EndPopup();
}

void UIElements::PuzzleTest()
{
	ImGui::SetNextWindowContentSize(ImVec2(550, 500));
	ImGui::SetWindowSize(ImVec2(0, 0));
	ImGui::SetWindowFontScale(9.5);
	const float Spacing = ImGui::GetStyle().ItemSpacing.x;
	static float ButtonWidth = 100.0f;
	float pos;
	static unsigned int Img1 = GameObject::loadTexture("2.png");
	static unsigned int Img2 = GameObject::loadTexture("3.png");	//Images used for Puzzle elements
	static unsigned int Img3 = GameObject::loadTexture("5.png");
	static unsigned int Img4 = GameObject::loadTexture("9.png");
	static int b1Index = 0;
	static int b2Index = 0;
	static int b3Index = 0;		//index variables used to keep track of what image should be displayed
	static int b4Index = 0;

	static bool input = false;
	static AudioSource sfx;
	
	ImGui::OpenPopup("Puzzle");

	
	while (ImGui::BeginPopup("Puzzle"))
	{

		pos = ButtonWidth + Spacing;		//positional calculations for neatness
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::ArrowButton("UArr1", ImGuiDir_Up))	//Arrow button, the size of the button is sdependant on the font size
		{
			sfx.Play(SE_LOAD("Blip_Select.wav"));
			b1Index--;		//decrease the value of index1 and play a sound
			
			if (b1Index < 0)
				b1Index = 3;				
		}
		ButtonWidth = ImGui::GetItemRectSize().x;


		pos += ButtonWidth + Spacing;		//positional calculations for neatness
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::ArrowButton("UArr2", ImGuiDir_Up))
		{
			sfx.Play(SE_LOAD("Blip_Select.wav"));
			b2Index--;		//decrease the value of index2 and play a sound
			
			if (b2Index < 0)
				b2Index = 3;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;

		pos += ButtonWidth + Spacing;		//positional calculations for neatness
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::ArrowButton("UArr3", ImGuiDir_Up))
		{
			sfx.Play(SE_LOAD("Blip_Select.wav"));
			b3Index--;		//decrease the value of index3 and play a sound
			
			if (b3Index < 0)
				b3Index = 3;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;

		pos += ButtonWidth + Spacing;		//positional calculations for neatness
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::ArrowButton("UArr4", ImGuiDir_Up))
		{
			sfx.Play(SE_LOAD("Blip_Select.wav"));
			b4Index--;		//decrease the value of index4 and play a sound
			
			if (b4Index < 0)
				b4Index = 3;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;


		ImGui::NewLine();
		pos = ButtonWidth + Spacing;		//positional calculations for neatness
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		switch (b1Index)	//check to see what image should be drawn depending on the Index Value
		{
		case 0:
			ImGui::Image((void*)Img1, ImVec2(120, 120));
			break;
		case 1:
			ImGui::Image((void*)Img2, ImVec2(120, 120));
			break;
		case 2:
			ImGui::Image((void*)Img3, ImVec2(120, 120));
			break;
		case 3:
			ImGui::Image((void*)Img4, ImVec2(120, 120));
			break;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;

		pos += ButtonWidth + Spacing;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		switch (b2Index)	//check to see what image should be drawn depending on the Index Value
		{
		case 0:
			ImGui::Image((void*)Img1, ImVec2(120, 120));
			break;
		case 1:
			ImGui::Image((void*)Img2, ImVec2(120, 120));
			break;
		case 2:
			ImGui::Image((void*)Img3, ImVec2(120, 120));
			break;
		case 3:
			ImGui::Image((void*)Img4, ImVec2(120, 120));
			break;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;

		pos += ButtonWidth + Spacing;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);		//positional calculations for neatness
		switch (b3Index)	//check to see what image should be drawn depending on the Index Value
		{
		case 0:
			ImGui::Image((void*)Img1, ImVec2(120, 120));
			break;
		case 1:
			ImGui::Image((void*)Img2, ImVec2(120, 120));
			break;
		case 2:
			ImGui::Image((void*)Img3, ImVec2(120, 120));
			break;
		case 3:
			ImGui::Image((void*)Img4, ImVec2(120, 120));
			break;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;

		pos += ButtonWidth + Spacing;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);		//positional calculations for neatness
		switch (b4Index)	//check to see what image should be drawn depending on the Index Value
		{
		case 0:
			ImGui::Image((void*)Img1, ImVec2(120, 120));
			break;
		case 1:
			ImGui::Image((void*)Img2, ImVec2(120, 120));
			break;
		case 2:
			ImGui::Image((void*)Img3, ImVec2(120, 120));
			break;
		case 3:
			ImGui::Image((void*)Img4, ImVec2(120, 120));
			break;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;


		pos = ButtonWidth + Spacing;
		ImGui::NewLine();			//positional calculations for neatness
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::ArrowButton("DArr1", ImGuiDir_Down))
		{
			sfx.Play(SE_LOAD("Blip_Select.wav"));
			b1Index++;		//increase the value of index1 and play a sound
			
			if (b1Index > 3)
				b1Index = 0;

		}
		ButtonWidth = ImGui::GetItemRectSize().x;


		pos += ButtonWidth + Spacing;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);		//positional calculations for neatness
		if (ImGui::ArrowButton("DArr2", ImGuiDir_Down))
		{
			sfx.Play(SE_LOAD("Blip_Select.wav"));
			b2Index++;		//increase the value of index2 and play a sound
			
			if (b2Index > 3)
				b2Index = 0;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;

		pos += ButtonWidth + Spacing;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);		//positional calculations for neatness
		if (ImGui::ArrowButton("DArr3", ImGuiDir_Down))
		{
			sfx.Play(SE_LOAD("Blip_Select.wav"));
			b3Index++;		//increase the value of index3 and play a sound
			
			if (b3Index > 3)
				b3Index = 0;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;

		pos += ButtonWidth + Spacing;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);		//positional calculations for neatness
		if (ImGui::ArrowButton("DArr4", ImGuiDir_Down))
		{
			sfx.Play(SE_LOAD("Blip_Select.wav"));
			b4Index++;		//increase the value of index4 and play a sound
			
			if (b4Index > 3)
				b4Index = 0;
		}
		ButtonWidth = ImGui::GetItemRectSize().x;

		ImGui::NewLine();
		pos = 240.0f + Spacing;		//positional calculations for neatness
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::Button("Enter", ImVec2(240.0f, 120.0f)))		//test button used to call the Event function currently assigned to the Event Manager
		{
			if (Events::TestCode(b4Index, b3Index, b2Index, b1Index)) 
			{
				if (REngine::Instance()->FindObjectWithTag("DOOR") != nullptr)	//finds the Object with a specifit tag
				{
					sfx.Play(SE_LOAD("Error.wav"));
					GameObject* a = REngine::Instance()->FindObjectWithTag("DOOR");
					glm::vec3 pos = a->GetKinematics()->m_Transform.GetPos();
					a->GetKinematics()->m_Transform.Translate(glm::vec3(pos.x, pos.y + 0.5f, pos.z));	//Sets the Objects Y position to its current Y position + 0.5
				}
			};
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
