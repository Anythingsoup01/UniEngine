#include "Sandbox2D.h"
#include "UniHeaders.h"

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

	UE::Renderer2D::DrawQuad(square1Transform, square1Rotation, { 1.0f,1.0f }, square1Color);
	UE::Renderer2D::DrawQuad(square2Transform, square2Rotation, { 1.0f,1.0f }, square2Color);
	
	UE::Renderer2D::EndScene();
// Todo - Add the functions: Shader::SetMat4, Shader::SetFloat4
}


void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Inspector");
	ImGui::ColorEdit4("First Square Color", glm::value_ptr(square1Color));
	ImGui::DragFloat2("First Square Transform", glm::value_ptr(square1Transform), 0.025f);
	ImGui::DragFloat("First Square Rotation", &square1Rotation);

	ImGui::ColorEdit4("Second Square Color", glm::value_ptr(square2Color));
	ImGui::DragFloat2("Second Square Transform", glm::value_ptr(square2Transform), 0.025f);
	ImGui::DragFloat("Second Square Rotation", &square2Rotation);

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
