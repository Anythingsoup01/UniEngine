#pragma once

#include "UniEngine/Core/Core.h"

namespace UE {

	class UE_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImplemented(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImplemented(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImplemented(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImplement(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImplement(); }
	protected:
		virtual bool IsKeyPressedImplemented(int keycode) = 0;

		virtual bool IsMouseButtonPressedImplemented(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImplemented() = 0;
		virtual float GetMouseXImplement() = 0;
		virtual float GetMouseYImplement() = 0;
	private:
		static Input* s_Instance;
	};

}