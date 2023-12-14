#pragma once

#include "UniEngine/Core/Window.h"
#include "UniEngine/Renderer/Rendering/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace UE {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return Data.Width; }
		inline unsigned int GetHeight() const override { return Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* Window;
		GraphicsContext* Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData Data;
	};

}