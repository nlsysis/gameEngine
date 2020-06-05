#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace Engine
{
	class EG_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};

	///To be defined in client.
	Application *CreateApplication();

}

