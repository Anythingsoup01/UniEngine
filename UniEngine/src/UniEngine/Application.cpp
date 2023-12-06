#include "Application.h"

#include "UniEngine/Events/MouseEvents.h"
#include "UniEngine/Log.h"


namespace UE {
	Application::Application() {}
	Application::~Application() {}

	void Application::Run() {
		MouseMovedEvent e(100, 100);
		UE_CORE_INFO(e);
		


		while (true);
	}
}