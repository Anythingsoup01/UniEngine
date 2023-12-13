#pragma once
#include "RendererAPI.h"

namespace UE {
	class RenderCommand {
	public:
		inline static void Init() {
			r_RendererAPI->Init();
		}
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			r_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color) {
			r_RendererAPI->SetClearColor(color);
		}
		inline static void Clear() {
			r_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Referance<VertexArray>& vertexArray) {
			r_RendererAPI->DrawIndexed(vertexArray);
		}
		
	private:
		static RendererAPI* r_RendererAPI;
	};
}