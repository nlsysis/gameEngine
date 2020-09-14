#include "egpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Engine
{
	RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRendererAPI;  ///will be set dynamic later
}