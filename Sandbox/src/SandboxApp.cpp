#include <UniHeaders.h>

#include "imgui/imgui.h"

class ExampleLayer : public UE::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (UE::Input::IsKeyPressed(UE_KEY_TAB))
			UE_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
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