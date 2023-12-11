#pragma once

#include "UniEngine/Renderer/Buffer/Buffer.h"

namespace UE {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return b_Layout; }
		virtual void SetLayout(const BufferLayout layout) override {b_Layout = layout;}
	private:
		uint32_t b_RendererID;
		BufferLayout b_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetCount() const { return b_Count; }
	private:
		uint32_t b_RendererID;
		uint32_t b_Count;
	};

}