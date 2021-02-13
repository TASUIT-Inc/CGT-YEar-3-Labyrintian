#pragma once

//Path Definitions

#define TEXTURE_PATH "src/CodeMeat_Core/Graphics/Textures/TexturePool/"
#define SHADER_PATH  "src/CodeMeat_Core/Graphics/Shaders/ShaderPool/"

#define MODEL_PATH	  "src/CodeMeat_Core/Objects/Models/ModelPool/"
#define INSTANCE_PATH "src/CodeMeat_Core/Objects/Instance/InstancePool/"
#define MAP_PATH	  "src/CodeMeat_Core/Objects/Levels/MapPool/"


//Graphics Headers

	//Camera Class'
#include "CodeMeat_Core/Graphics/Camera/Camera.h"

	//FrameBuffer Class'
#include "CodeMeat_Core/Graphics/FrameBuffers/Bloom.h"
#include "CodeMeat_Core/Graphics/FrameBuffers/BloomBuffer.h"
#include "CodeMeat_Core/Graphics/FrameBuffers/Buffer.h"
#include "CodeMeat_Core/Graphics/FrameBuffers/FrameBuffer.h"

	//Light Class'
#include "CodeMeat_Core/Graphics/Ligths/Light.h"

	//Shader Class'
#include "CodeMeat_Core/Graphics/Shaders/Shader.h"

	//Renderer Class'
#include "CodeMeat_Core/Graphics/Renderer.h"

//Object Headers

	//GameObject Class'
#include "CodeMeat_Core/Objects/GameObject/GameObject.h"
#include "CodeMeat_Core/Objects/GameObject/Object.h"

	//Instance Class'

	//Model Class'
#include "CodeMeat_Core/Objects/Models/Model.h"
#include "CodeMeat_Core/Objects/Models/Mesh.h"

	//Level Class'

	//LoaderParam Class'
#include "CodeMeat_Core/Objects/LoaderParams.h"

	//Player Class'
#include "CodeMeat_Core/Objects/Player.h"

//Physics Headers
#include "CodeMeat_Core/Physics/Physics.h"

//Engine Headers
#include "CodeMeat_Core/Engine.h"

//Deps Headers
#include "CodeMeat_Core/Deps/stb_image.h"
