#include "uepch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace UE {

	Renderer::ScenenData* Renderer::sceneData = new Renderer::ScenenData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{

	}
	void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}