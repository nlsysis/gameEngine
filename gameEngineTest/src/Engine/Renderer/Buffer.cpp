#include "egpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{
	VeretexBuffer* VeretexBuffer::Create(float * vertexSrc, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:    EG_CORE_ASSERT(false, "RenderAPI:None is currently not supported!") return nullptr;
			case RendererAPI::OpenGL:  return new OpenGLVertexBuffer(vertexSrc, size);
		}

		EG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t * indexSrc, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    EG_CORE_ASSERT(false, "RenderAPI:None is currently not supported!") return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLIndexBuffer(indexSrc, count);
		}

		EG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}