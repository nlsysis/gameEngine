#pragma once

#include <memory>
#include "Engine/Renderer/Buffer.h"

namespace Engine
{
	/**
	 * @brief Set the vertex
	 */
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}      ///make the destructor void

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}
