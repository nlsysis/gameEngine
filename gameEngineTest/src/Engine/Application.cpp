#include "egpch.h"
#include "Application.h"

#include "Engine/Event/ApplicationEvent.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
	/*	WindowResizeEvent e(1200, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			
			EG_TRACE(e);
		}*/

		while (true)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}

	}
}