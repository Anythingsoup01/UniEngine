#pragma once

#include <glm/glm.hpp>

#include "UniEngine/Renderer/Arrays/VertexArray.h"

namespace UE {

	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		};

	public:
		virtual void Init() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Referance<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return r_API; }



	private:
		static API r_API;


	};
}