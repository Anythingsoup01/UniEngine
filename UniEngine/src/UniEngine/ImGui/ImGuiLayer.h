#pragma once

#include "UniEngine/Layer.h"

#include "UniEngine/Events/ApplicationEvents.h"
#include "UniEngine/Events/KeyEvents.h"
#include "UniEngine/Events/MouseEvents.h"

namespace UE {

	class UE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;

	};

}

