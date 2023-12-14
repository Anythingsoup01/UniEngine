#include "uepch.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "UniEngine/Renderer/Shader/Shader.h"
#include "UniEngine/Renderer/Arrays/VertexArray.h"
#include "UniEngine/Renderer/Rendering/RenderCommand.h"

namespace UE {

	struct Renderer2DStorage {
		Reference<VertexArray> QuadVertexArray;
		Reference<Shader> FlatColorShader;
	};


	static Renderer2DStorage* rendererData;

	void Renderer2D::Init()
	{
		rendererData = new Renderer2DStorage();
		rendererData->QuadVertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		UE::Reference<VertexBuffer> squareVB; squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ShaderDataType::Vector3, "a_Position"}
			});
		rendererData->QuadVertexArray->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Reference<IndexBuffer> squareIB; squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		rendererData->QuadVertexArray->SetIndexBuffer(squareIB);


		rendererData->FlatColorShader = UE::Shader::Create("assets/shaders/Shader.Shader");
	}
	void Renderer2D::Shutdown()
	{
		delete rendererData;
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		
		DrawQuad({ position.x, position.y, 0.0f }, size, color);

	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->FlatColorShader)->UploadUniformFloat4("u_Color", color);

		rendererData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->QuadVertexArray);
	}
}