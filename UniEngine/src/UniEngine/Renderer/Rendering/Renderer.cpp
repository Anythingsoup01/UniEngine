#include "uepch.h"
#include "Platform/OpenGL/OpenGLShader.h"
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
	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("oc_ViewProjection", r_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("o_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}