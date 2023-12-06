#include <UniHeaders.h>

class ExampleLayer : public UE::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

};

class Sandbox : public UE::Application {
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new UE::ImGuiLayer());
	}
	~Sandbox() {}

};

UE::Application* UE::CreateApplication() {
	return new Sandbox();
}