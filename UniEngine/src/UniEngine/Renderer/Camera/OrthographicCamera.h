#pragma once

#include <glm/glm.hpp>

namespace UE{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return Position; }
		void SetPosition(const glm::vec3& position) { Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return Rotation; }
		void SetRotation(float rotation) { Rotation = rotation; RecalculateViewMatrix(); }


		const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		float Rotation = 0.0f;
	};
}

