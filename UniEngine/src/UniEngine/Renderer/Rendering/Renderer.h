#pragma once

#include "RenderCommand.h"
#include "UniEngine/Renderer/Shader/Shader.h"
#include "UniEngine/Renderer/Camera/OrthographicCamera.h"

namespace UE {

	class Renderer
	{
	public:

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> r_Shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct ScenenData {
			glm::mat4 ViewProjectionMatrix;
		};
		static ScenenData* r_SceneData;
	};

}
