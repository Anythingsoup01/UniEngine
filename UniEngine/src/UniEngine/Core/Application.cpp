#include "uepch.h"

#include "Windows.h"
#include "Application.h"
#include "UniEngine/Core/Log.h"
#include "UniEngine/Events/Event.h"
#include "UniEngine/Renderer/Rendering/Renderer.h"

#include "UniEngine/Core/TimeStep.h"
#include <GLFW/glfw3.h>


namespace UE {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)



	Application* Application::a_Instance = nullptr;


	Application::Application()
	{
		UE_CORE_ASSERT(!a_Instance, "Application already exists!");
		a_Instance = this;

		aw_Window = std::unique_ptr<Window>(Window::Create());
		aw_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		

		Renderer::Init();

		ag_ImGuiLayer = new ImGuiLayer();
		PushOverlay(ag_ImGuiLayer);
	}

	

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		al_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		al_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		
		for (auto it = al_LayerStack.end(); it != al_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}


	void Application::Run()
	{
		while (ab_Running)
		{
			float time = (float)glfwGetTime(); // Platform::GetTime()
			TimeStep timestep = time - ts_LastFrameTime;
			ts_LastFrameTime = time;
			if (!applicationMinimized) {
				for (Layer* layer : al_LayerStack)
					layer->OnUpdate(timestep);
			}
			ag_ImGuiLayer->Begin();
			for (Layer* layer : al_LayerStack)
			{
				layer->OnImGuiRender();
			}
			ag_ImGuiLayer->End();

			aw_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		ab_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			applicationMinimized = true;
			UE_INFO("Application Minimized!");
			return false;
		}

		applicationMinimized = false;
		Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());

		return false;
	}

}