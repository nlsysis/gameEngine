#include "egpch.h"

#include "Engine/Core.h"
#include "WinsWindow.h"

namespace Engine
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WinsWindow(props);
	}

	WinsWindow::WinsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WinsWindow::~WinsWindow()
	{
		Shutdown();
	}

	void WinsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		EG_CORE_INFO("Creation window {0} {1}, {2}", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			EG_CORE_ASSERT(success, "Coudle not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WinsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WinsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WinsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}

	bool WinsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}

