#pragma once

#include "UniEngine/Input.h"

namespace UE {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImplemented(int keycode) override;

		virtual bool IsMouseButtonPressedImplemented(int button) override;
		virtual std::pair<float, float> GetMousePositionImplemented() override;
		virtual float GetMouseXImplement() override;
		virtual float GetMouseYImplement() override;
	};

}
