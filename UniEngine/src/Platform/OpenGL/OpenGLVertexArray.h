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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffer; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }
	private:
		uint32_t rendererID;
		std::vector<Ref<VertexBuffer>> vertexBuffer;
		Ref<IndexBuffer> indexBuffer;
	};
}
