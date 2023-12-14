#include <UniHeaders.h>
#include <UniEngine/Core/EntryPoint.h>

#include "UniEngine/ImGui/ImGuiLayer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"



class ExampleLayer : public UE::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

			
	}

	void OnUpdate(UE::TimeStep DeltaTime) override
	{
		
	}

	virtual void OnImGuiRender() override
	{
	
	}

	void OnEvent(UE::Event& e) override
	{
		
	}

private:

};

class Sandbox : public UE::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}

};

UE::Application* UE::CreateApplication()
{
	return new Sandbox();
}