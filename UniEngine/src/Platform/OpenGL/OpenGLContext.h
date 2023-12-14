#pragma once

#include "UniEngine/Renderer/Rendering/GraphicsContext.h"

struct GLFWwindow;

namespace UE {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowhandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};

}