#pragma once

#include <glm/glm.hpp>

namespace UE{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return oc_Position; }
		void SetPosition(const glm::vec3& position) { oc_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return oc_Rotation; }
		void SetRotation(float rotation) { oc_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return oc_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return oc_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return oc_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 oc_ProjectionMatrix;
		glm::mat4 oc_ViewMatrix;
		glm::mat4 oc_ViewProjectionMatrix;

		glm::vec3 oc_Position = { 0.0f, 0.0f, 0.0f };
		float oc_Rotation = 0.0f;
	};
}

