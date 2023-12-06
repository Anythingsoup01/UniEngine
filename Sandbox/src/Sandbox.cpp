#include <UniHeaders.h>

class ExampleLayer : public UE::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	void OnUpdate() override {
		if (UE::Input::IsKeyPressed(UE_KEY_SPACE)) {
			UE_INFO("Space has actually been pressed");
		}
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