#pragma once
#include "UniEngine/Renderer/Textures/Texture.h"


#include <glad/glad.h>

namespace UE {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return Width; }
		virtual uint32_t GetHeight() const override { return Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		const std::string& Path;
		uint32_t Width, Height;
		uint32_t rendererID;
		GLenum internalFormat, dataFormat;
	};
}

