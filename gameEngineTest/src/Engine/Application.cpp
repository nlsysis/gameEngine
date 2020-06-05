#include "egpch.h"
#include "Application.h"

#include "Engine/Event/ApplicationEvent.h"
#include "Engine/Log.h"

namespace Engine
{
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			
			EG_TRACE(e);
		}

		while (true);
	}
}