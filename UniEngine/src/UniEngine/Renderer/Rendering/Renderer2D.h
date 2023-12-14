#pragma once

#include "UniEngine/Renderer/Camera/OrthographicCamera.h"
#include "UniEngine/Renderer/Textures/Texture.h"

namespace UE {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0, 1.0, 1.0, 1.0 }, const int& tile = 1);
		static void DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0, 1.0, 1.0, 1.0 }, const int& tile = 1);
	};
}

