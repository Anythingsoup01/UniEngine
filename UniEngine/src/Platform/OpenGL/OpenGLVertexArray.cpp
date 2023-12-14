#include "uepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace UE {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case UE::ShaderDataType::Vector: return GL_FLOAT;
		case UE::ShaderDataType::Vector2:return GL_FLOAT;
		case UE::ShaderDataType::Vector3:return GL_FLOAT;
		case UE::ShaderDataType::Vector4:return GL_FLOAT;
		case UE::ShaderDataType::Mat3:return GL_FLOAT;
		case UE::ShaderDataType::Mat4:return GL_FLOAT;
		case UE::ShaderDataType::Int:return GL_INT;
		case UE::ShaderDataType::Int2:return GL_INT;
		case UE::ShaderDataType::Int3:return GL_INT;
		case UE::ShaderDataType::Int4:return GL_INT;
		case UE::ShaderDataType::Bool:return GL_BOOL;
		}
		UE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Reference<VertexBuffer>& vertexbuffer)
	{
		UE_CORE_ASSERT(vertexbuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(rendererID);
		vertexbuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexbuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		vertexBuffer.push_back(vertexbuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Reference<IndexBuffer>& indexbuffer)
	{
		glBindVertexArray(rendererID);
		indexbuffer->Bind();

		indexBuffer = indexbuffer;
	}

}