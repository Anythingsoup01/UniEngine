#pragma once
#include "uepch.h"
#include <glm/glm.hpp>

namespace UE {

	class Shader {
	public:
		virtual~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
		
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;

		virtual void SetInt(const std::string& name, const int value) = 0;


		static Ref<Shader> Create(const std::string& path);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}
