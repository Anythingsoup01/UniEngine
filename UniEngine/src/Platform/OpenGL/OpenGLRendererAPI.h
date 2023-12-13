#pragma once

#include "UniEngine/Renderer/Rendering/RendererAPI.h"

namespace UE {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Referance<VertexArray>& vertexArray) override;
	private:
	};
}