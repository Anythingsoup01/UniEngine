#include "uepch.h"

#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "UniEngine/Renderer/Rendering/Renderer.h"

namespace UE {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}