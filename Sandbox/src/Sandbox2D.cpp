#include "Sandbox2D.h"
#include "UniHeaders.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "UniEngine/Renderer/Rendering/Renderer2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f, true)
{

}

void Sandbox2D::OnAttach()
{

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

	UE::Renderer2D::BeginScene(cameraController.GetCamera());

	UE::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f,1.0f }, squareColor);
	
	UE::Renderer2D::EndScene();
// Todo - Add the functions: Shader::SetMat4, Shader::SetFloat4
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
