#pragma once
#include "uepch.h"

namespace UE {

	class Shader {
	public:
		virtual~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Reference<Shader> Create(const std::string& path);
		static Reference<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}
