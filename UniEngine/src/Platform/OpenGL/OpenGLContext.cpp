#include "uepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace UE {

	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
		: windowHandle(windowhandle)
	{
		UE_CORE_ASSERT(windowhandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UE_CORE_ASSERT(status, "Failed to initialize Glad!");
	}



	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}

}