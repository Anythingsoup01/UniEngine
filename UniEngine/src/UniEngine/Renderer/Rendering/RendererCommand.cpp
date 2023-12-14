#include "uepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace UE {
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}