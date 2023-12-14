#pragma once

#include <memory>
#include "UniEngine/Renderer/Arrays/VertexArray.h"

namespace UE {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Reference<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffer; }
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }
	private:
		uint32_t rendererID;
		std::vector<Reference<VertexBuffer>> vertexBuffer;
		Reference<IndexBuffer> indexBuffer;
	};
}
