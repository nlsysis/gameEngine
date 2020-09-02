#pragma once

/*
	*@brief: this class is designed for different renderer API to inherit.
	*   and the generally functions are used as interface.
**/

namespace Engine
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}