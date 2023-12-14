#include "uepch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "UniEngine/Renderer/Rendering/Renderer.h"

namespace UE {
	Reference<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}