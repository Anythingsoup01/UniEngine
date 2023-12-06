#include "uepch.h"
#include "Application.h"

#include "UniEngine/Events/MouseEvents.h"
#include "UniEngine/Log.h"


namespace UE {
	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application() {}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}