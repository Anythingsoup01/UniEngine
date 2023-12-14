#pragma once

#include "RenderCommand.h"
#include "UniEngine/Renderer/Shader/Shader.h"
#include "UniEngine/Renderer/Camera/OrthographicCamera.h"

namespace UE {

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResized(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Referance<Shader> r_Shader, const Referance<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct ScenenData {
			glm::mat4 viewProjectionMatrix;
		};
		static ScenenData* sceneData;
	};

}
