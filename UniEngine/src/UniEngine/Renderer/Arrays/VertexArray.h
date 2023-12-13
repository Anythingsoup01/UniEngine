#pragma once

#include <memory>
#include "UniEngine/Renderer/Buffer/Buffer.h"

namespace UE {
	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Referance<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Referance<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Referance<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Referance<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	private:
	};
}
