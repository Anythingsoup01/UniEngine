#include "uepch.h"
#include "WindowsInput.h"

#include "UniEngine/Application.h"
#include <GLFW/glfw3.h>

namespace UE {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImplemented(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImplemented(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImplemented()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImplement()
	{
		auto[x, y] = GetMousePositionImplemented();
		return x;
	}

	float WindowsInput::GetMouseYImplement()
	{
		auto[x, y] = GetMousePositionImplemented();
		return y;
	}

}