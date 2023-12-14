#include "Sandbox2D.h"
#include "UniHeaders.h"

#include "UniEngine/Renderer/Rendering/Renderer2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	checkerboardTexture = UE::Texture2D::Create("assets/textures/Checkerboard.png");
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

	UE::Renderer2D::DrawQuad(square1Transform, square1Rotation, square1Scale, square1Color);
	UE::Renderer2D::DrawQuad(textureTransform, textureRotation, textureScale, checkerboardTexture, textureColor, textureTiling);
	
	UE::Renderer2D::EndScene();
// Todo - Add the functions: Shader::SetMat4, Shader::SetFloat4
}


void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Square One");
	ImGui::ColorEdit4("First Square Color", glm::value_ptr(square1Color));
	ImGui::DragFloat3("First Square Transform", glm::value_ptr(square1Transform), 0.025f);
	ImGui::DragFloat("First Square Rotation", &square1Rotation, 0.025f);
	ImGui::DragFloat2("First Square Scale", glm::value_ptr(square1Scale), 0.025f);

	ImGui::End();

	ImGui::Begin("Square Two");

	//ImGui::ColorEdit4("Second Square Color", glm::value_ptr(square2Color));
	ImGui::DragFloat3("Texture Transform", glm::value_ptr(textureTransform), 0.025f);
	ImGui::DragFloat("Texture Rotation", &textureRotation, 0.025f);
	ImGui::DragFloat2("Texture Scale", glm::value_ptr(textureScale), 0.025f);
	ImGui::ColorEdit4("Texture Color", glm::value_ptr(textureColor));
	ImGui::DragInt("Texture Tiling", &textureTiling, 0.025, 1, 100);

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
