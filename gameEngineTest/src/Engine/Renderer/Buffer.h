#pragma once

namespace Engine
{
	class VeretexBuffer
	{
	public:
		virtual ~VeretexBuffer() {};      //make the destructor void

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VeretexBuffer* Create(float* vertexSrc, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};      //make the destructor void

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indexSrc, uint32_t count);
	};
}