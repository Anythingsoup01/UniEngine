#include "uepch.h"
#include "WindowsInput.h"

#include "UniEngine/Application.h"
#include <GLFW/glfw3.h>
namespace UE
{
	Input* Input::s_Instance = new WindowsInput();

	bool UE::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool UE::WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> UE::WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float UE::WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float UE::WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}
}
