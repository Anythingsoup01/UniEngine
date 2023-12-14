#pragma once
// For use by Universal Engine Applications

//--------Core----------------------------------------------------------
#include "UniEngine/Core/Application.h"
#include "UniEngine/Core/Layer.h"
#include "UniEngine/Core/Log.h"
#include "UniEngine/ImGui/ImGuiLayer.h"
#include "UniEngine/Core/TimeStep.h"
#include "UniEngine/Core/EntryPoint.h"

//--------Renderer------------------------------------------------------
#include "UniEngine/Events/ApplicationEvent.h"
#include "UniEngine/Events/Event.h"
#include "UniEngine/Events/KeyEvent.h"
#include "UniEngine/Events/MouseEvent.h"

//--------Renderer------------------------------------------------------
#include "UniEngine/Renderer/Arrays/VertexArray.h"
#include "UniEngine/Renderer/Buffer/Buffer.h"
#include "UniEngine/Renderer/Camera/OrthographicCamera.h"
#include "UniEngine/Renderer/Camera/OrthographicCameraController.h"
//#include "UniEngine/Renderer/Materials/"
#include "UniEngine/Renderer/Rendering/GraphicsContext.h"
#include "UniEngine/Renderer/Rendering/RenderCommand.h"
#include "UniEngine/Renderer/Rendering/Renderer.h"
#include "UniEngine/Renderer/Rendering/RendererAPI.h"
#include "UniEngine/Renderer/Shader/Shader.h"
#include "UniEngine/Renderer/Textures/Texture.h"

//--------Dependenceies-------------------------------------------------
#include "glm/gtc/type_ptr.hpp"
#include "../ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>