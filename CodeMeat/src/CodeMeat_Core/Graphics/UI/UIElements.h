#pragma once
#include "CodeMeat_Core/Graphics/UI/imgui.h"
#include "CodeMeat_Core/Objects/Audio/AudioBuffer.h"
#include "CodeMeat_Core/Objects/Audio/AudioSource.h"
#include "CodeMeat_Core/Engine.h"
#include "CodeMeat_Core/Physics/Events/Events.h"
#include <iostream>
#include <string>
#include <charconv>
class UIElements
{
public:
	static void PauseMenu();
	static void PuzzleTest();
	static void UIStyling(ImColor col, ImColor col2);
	static void CleanStyling();
	UIElements() {}
	~UIElements() {};

private:
	
};