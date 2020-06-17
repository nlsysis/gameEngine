#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Window.h"

namespace Engine
{
	class EG_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
	};

	///To be defined in client.
	Application *CreateApplication();

}

