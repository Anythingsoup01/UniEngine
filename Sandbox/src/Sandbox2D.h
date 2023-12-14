#pragma once
#include "UniHeaders.h"

class Sandbox2D : public UE::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(UE::TimeStep DeltaTime) override;
	virtual void OnImGuiRender() override;
	void OnEvent(UE::Event& e) override;

private:
	UE::OrthographicCameraController cameraController;

	//Temp
	UE::Ref<UE::Shader> Shader;
	UE::Ref<UE::VertexArray> squareVA;

	//Temp
	glm::vec4 square1Color = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 textureColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec3 square1Transform = { 0.0f, 0.0f, 0.0f };
	glm::vec3 textureTransform = { 0.0f, 0.0f, 0.0f };
	glm::vec2 square1Scale = { 0.0f, 0.0f };
	glm::vec2 textureScale = { 0.0f, 0.0f };
	float square1Rotation = 0.0f;
	float textureRotation = 0.0f;
	int textureTiling = 1;

	UE::Ref<UE::Texture2D> checkerboardTexture;

	glm::mat4 transform;
};

