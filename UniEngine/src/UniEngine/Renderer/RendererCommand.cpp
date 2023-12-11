#include "uepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace UE {
	RendererAPI* RenderCommand::r_RendererAPI = new OpenGLRendererAPI;
}