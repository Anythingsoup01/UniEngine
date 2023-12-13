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

		virtual void AddVertexBuffer(const Referance<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Referance<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Referance<VertexBuffer>>& GetVertexBuffers() const { return b_VertexBuffers; }
		virtual const Referance<IndexBuffer>& GetIndexBuffer() const { return b_IndexBuffer; }
	private:
		uint32_t b_RendererID;
		std::vector<Referance<VertexBuffer>> b_VertexBuffers;
		Referance<IndexBuffer> b_IndexBuffer;
	};
}
