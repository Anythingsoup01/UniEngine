#pragma once
#include "uepch.h"

namespace UE {

	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t s_RendererID;
	};

}
