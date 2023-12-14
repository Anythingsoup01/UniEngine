#pragma once

#include "UniEngine/Core/Core.h"
#include "UniEngine/Events/Event.h"
#include "UniEngine/Core/TimeStep.h"

namespace UE {

	class UE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return z_DebugName; }
	protected:
		std::string z_DebugName;
	};

}