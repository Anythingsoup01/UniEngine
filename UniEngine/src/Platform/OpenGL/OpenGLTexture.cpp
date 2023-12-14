#include "uepch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace UE {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: Width(width), Height(height), Path(Path)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, Width, Height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererID,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID,GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		UE_CORE_ASSERT(data, "Failed to load image!");
		Width = width;
		Height = height;

		GLenum InternalFormat = 0, DataFormat = 0;
		if (channels == 4) {
			InternalFormat = GL_RGBA8;
			DataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			InternalFormat = GL_RGB8;
			DataFormat = GL_RGB;
		}

		internalFormat = InternalFormat;
		dataFormat = DataFormat;

		UE_CORE_ASSERT(InternalFormat & DataFormat, "Format Not Supported!!");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, Width, Height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(rendererID, 0, 0, 0, Width, Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);


	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererID);
	}
	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = dataFormat == GL_RGBA ? 4 : 3;
		UE_CORE_ASSERT(size == Width * Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(rendererID, 0, 0, 0, Width, Height, dataFormat, GL_UNSIGNED_BYTE, data);
	}
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererID);
	}
}