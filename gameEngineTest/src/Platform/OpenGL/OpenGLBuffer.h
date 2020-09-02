#pragma once

#include "Engine/Renderer/Buffer.h"

namespace Engine
{

	class OpenGLVertexBuffer : public VeretexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertexSrc, uint32_t size);
		~OpenGLVertexBuffer();      //make the destructor void

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indexSrc, uint32_t count);
		~OpenGLIndexBuffer();      //make the destructor void

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}