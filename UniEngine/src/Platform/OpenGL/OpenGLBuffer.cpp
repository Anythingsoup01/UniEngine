#include "uepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace UE {

	//Tracks the Vertexes that either you set or are eventually set automatically 

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &b_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, b_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	inline OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &b_RendererID);
	}


	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, b_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	//===========================================================================
	// INDEXBUFFER---------------------------------------------------------------
	//===========================================================================

	//Tracks the Indices

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: b_Count(count)
	{
		glCreateBuffers(1, &b_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	inline OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &b_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}