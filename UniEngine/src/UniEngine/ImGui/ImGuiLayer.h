#pragma once

#include "UniEngine/Core/Layer.h"

#include "UniEngine/Events/ApplicationEvent.h"
#include "UniEngine/Events/KeyEvent.h"
#include "UniEngine/Events/MouseEvent.h"

namespace UE {

	class UE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float Time = 0.0f;
	};

}