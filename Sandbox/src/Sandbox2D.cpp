#include "Sandbox2D.h"
#include "UniHeaders.h"

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	squareVA = UE::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f, 
		 0.5f, -0.5f, 0.0f, 
		 0.5f,  0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f
	};
	UE::Reference<UE::VertexBuffer> squareVB; squareVB.reset(UE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{UE::ShaderDataType::Vector3, "v_Position"}
		});
	squareVA->AddVertexBuffer(squareVB);

	unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	UE::Reference<UE::IndexBuffer> squareIB; squareIB.reset(UE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	squareVA->SetIndexBuffer(squareIB);


	Shader = UE::Shader::Create("assets/shaders/Shader.Shader");

}


void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(UE::TimeStep DeltaTime)
{
	//Update
	cameraController.OnUpdate(DeltaTime);

	//Render
	UE::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 0.05f });
	UE::RenderCommand::Clear();

	UE::Renderer::BeginScene(cameraController.GetCamera());

	std::dynamic_pointer_cast<UE::OpenGLShader>(Shader)->Bind();
	std::dynamic_pointer_cast<UE::OpenGLShader>(Shader)->UploadUniformFloat4("u_Color", squareColor);

	UE::Renderer::Submit(Shader, squareVA, glm::mat4(1.0f));

	UE::Renderer::EndScene();

}


void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Inspector");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
	ImGui::End();

	ImGui::Begin("Assets");

	ImGui::End();

	ImGui::Begin("Hierarchy");

	ImGui::End();
}

void Sandbox2D::OnEvent(UE::Event& e)
{
	cameraController.OnEvent(e);
}
