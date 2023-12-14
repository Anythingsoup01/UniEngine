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
	glm::vec4 squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};

