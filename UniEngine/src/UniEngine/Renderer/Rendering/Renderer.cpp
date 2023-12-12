#include "uepch.h"

#include "Renderer.h"

namespace UE {

	Renderer::ScenenData* Renderer::r_SceneData = new Renderer::ScenenData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		r_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{

	}
	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("oc_ViewProjection", r_SceneData->ViewProjectionMatrix);


		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}