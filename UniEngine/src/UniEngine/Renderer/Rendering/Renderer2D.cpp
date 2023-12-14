#include "uepch.h"
#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

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
		rendererData->FlatColorShader->Bind();
		rendererData->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		
		DrawQuad({ position.x, position.y, 0.0f }, rotation, size, color);

	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		rendererData->FlatColorShader->Bind();
		rendererData->FlatColorShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f) , glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		rendererData->FlatColorShader->SetMat4("u_Transform", transform);

		rendererData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->QuadVertexArray);
	}
}