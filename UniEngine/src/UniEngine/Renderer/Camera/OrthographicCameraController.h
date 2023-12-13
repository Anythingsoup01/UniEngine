#pragma once

#include "UniEngine/Renderer/Camera/OrthographicCamera.h"
#include "UniEngine/Core/TimeStep.h"

#include "UniEngine/Events/ApplicationEvent.h"
#include "UniEngine/Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace UE {

	class OrthographicCameraController {
	public:

		OrthographicCameraController(float aspectRatio, bool rotation = false); // zoom * (aspectRatio * 2 units)

		void OnUpdate(TimeStep dletaTime);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);

	private:
		float AspectRatio;
		float zoomLevel = 1.0f;
		float cameraTranslationSpeed = 1.0f, cameraRotationSpeed = 25.0f;
		float cameraRotation = 0.0f;

		glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };

		bool Rotation = false;

		OrthographicCamera m_Camera;
	};

};

