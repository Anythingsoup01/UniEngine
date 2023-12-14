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
	UE::Reference<UE::Shader> Shader;
	UE::Reference<UE::VertexArray> squareVA;
	glm::vec4 square1Color = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 square2Color = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec2 square1Transform = { 0.0f, 0.0f };
	glm::vec3 square2Transform = { 0.0f, 0.0f, 0.0f };
	float square1Rotation = 0.0f;
	float square2Rotation = 0.0f;
	glm::mat4 transform;
};

