#pragma once
#include "Core.h"
#include "Events/Events.h"

namespace UE {
	class UE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

