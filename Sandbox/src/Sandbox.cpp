#include <UniHeaders.h>

class ExampleLayer : public UE::Layer {
public:
	ExampleLayer()
		: Layer("Example") {}


	void OnEvent(UE::Event& event) override {
		UE_CORE_WARN("{0}", event);
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