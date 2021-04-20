#include "UIHandler.h"

bool UIHandler::Init(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
	//int a, b, c;

	//glfwGetVersion(&a, &b, &c);
	//std::cout << a << "." << b << "." << c << std::endl;

	//std::string version = std::to_string(a) + std::to_string(b) + "0";
	//glGetString(GL_VERSION)
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    if (window == NULL)
    {
        std::cout << "Window cannot be found" << std::endl;
        return 0;
    }

	std::cout << "Initialised ImGui stuffs" << std::endl;
	//ImGuiIO& io = ImGui::GetIO();
	////font1 = io.Fonts->AddFontFromFileTTF("Doom.ttf", 150);
	////Title = io.Fonts->AddFontFromFileTTF("Triforce.ttf", 96);
	//isOpen = NULL;
    return 1;
}

void UIHandler::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

	//UIHandler::Instance()->createPauseMenu(isOpen);

   /* ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
}

void UIHandler::Render()
{
	//UIHandler::Draw();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIHandler::Clean()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIHandler::createPauseMenu(bool* open)
{
 //   ImGui::PushStyleColor(ImGuiCol_WindowBg, WindowBGCol);
	//ImGui::PushStyleColor(ImGuiCol_Text, WindowCol);
	////ImGui::Dummy(ImVec2(200.f, 50.f));
	//ImGui::PushStyleColor(ImGuiCol_TitleBgActive, TitleCol);
	ImGui::Begin("Test", open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); // Create a window called "Hello, world!" and append into it.

	/*ImGui::PushFont(font);
	ImGui::Indent(window_width / 2 - 100);
	ImGui::Text("This is Title text.");
	ImGui::PopFont();*/
	//ImGui::SetWindowSize(ImVec2(600, 600));
	//ImGui::SetWindowSize(ImVec2(window_width, window_height));
	//ImGui::SetWindowPos(ImVec2(s_width / 2 - window_width / 2, s_height / 2 - window_height / 2));
	//ImGui::Unindent(window_width / 2);
	/*ImGui::PushFont(pFont);*/
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
	//ImGui::PopFont();

	//ImGui::PopStyleColor();
	//ImGui::PopStyleColor();
	//ImGui::PopStyleColor();
	ImGui::End();
}
