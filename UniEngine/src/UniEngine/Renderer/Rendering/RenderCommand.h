#pragma once
#include "RendererAPI.h"

namespace UE {
	class RenderCommand {
	public:
		inline static void Init() {
			r_RendererAPI->Init();
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