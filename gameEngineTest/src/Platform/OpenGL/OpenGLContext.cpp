#include "egpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine
{
	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		:m_WindowHandle(windowHandle)
	{
		EG_CORE_ASSERT(windowHandle, "window handle is null!");
	}

	void OpenGLContext::Init()
	{
		EG_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EG_CORE_ASSERT(status, "Failed to initialize Glad!");

		EG_CORE_INFO("Engine Info:");
		EG_CORE_INFO("  Vendor:  {0}", glGetString(GL_VENDOR));
		EG_CORE_INFO("  Renderer:  {0} ", glGetString(GL_RENDERER));
		EG_CORE_INFO("  Version:  {0} ", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		EG_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}