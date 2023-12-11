#include <UniHeaders.h>

#include "UniEngine/ImGui/ImGuiLayer.h"


using namespace UE;
class ExampleLayer : public UE::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(UE::Event& event) override
	{
		if (event.GetEventType() == UE::EventType::KeyPressed)
		{
			UE::KeyPressedEvent& e = (UE::KeyPressedEvent&)event;
			if (e.GetKeyCode() == UE_KEY_TAB)
				UE_TRACE("Tab key is pressed (event)!");
			UE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public UE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

UE::Application* UE::CreateApplication()
{
	return new Sandbox();
}