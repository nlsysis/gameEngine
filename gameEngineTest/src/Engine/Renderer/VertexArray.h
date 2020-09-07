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

		virtual void AddVertexBuffer(const std::shared_ptr<VeretexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VeretexBuffer>>& GetVertexBuffer() = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() = 0;

		static VertexArray* Create();
	};
}
