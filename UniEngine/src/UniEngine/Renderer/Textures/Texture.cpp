#include "uepch.h"
#include "Texture.h"

#include "UniEngine/Renderer/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace UE {
	Referance<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
