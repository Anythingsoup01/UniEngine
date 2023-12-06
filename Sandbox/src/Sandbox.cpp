#include <UniHeaders.h>

class ExampleLayer : public UE::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		UE_INFO("ExampleLayer::Update");
	}

	void OnEvent(UE::Event& event) override {
		UE_TRACE("{0}", event);
	}
};

class Sandbox : public UE::Application {
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}

};

UE::Application* UE::CreateApplication() {
	return new Sandbox();
}