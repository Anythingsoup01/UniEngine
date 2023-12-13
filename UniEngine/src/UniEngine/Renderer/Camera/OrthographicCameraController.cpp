#include "uepch.h"
#include "OrthographicCameraController.h"


namespace UE {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: AspectRatio(aspectRatio), m_Camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel), Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(TimeStep deltaTime)
	{
		if (UE::Input::IsKeyPressed(UE_KEY_W)) {
			cameraPosition.y += cameraTranslationSpeed * deltaTime;
		}
		else if (UE::Input::IsKeyPressed(UE_KEY_S)) {
			cameraPosition.y -= cameraTranslationSpeed * deltaTime;
		}
		if (UE::Input::IsKeyPressed(UE_KEY_A)) {
			cameraPosition.x -= cameraTranslationSpeed * deltaTime;
		}
		else if (UE::Input::IsKeyPressed(UE_KEY_D)) {
			cameraPosition.x += cameraTranslationSpeed * deltaTime;
		}

		if (Rotation) {
			if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_4)) {
				cameraRotation -= cameraRotationSpeed * deltaTime;
			}
			if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_5)) {
				cameraRotation += cameraRotationSpeed * deltaTime;
			}
			m_Camera.SetRotation(cameraRotation);
		}
		cameraTranslationSpeed = zoomLevel;
		m_Camera.SetPosition(cameraPosition);
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(UE_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}
	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
	{
		zoomLevel -= e.GetYOffset() * 0.05;
		zoomLevel = std::max(zoomLevel, 0.25f);
		m_Camera.SetProjection(-AspectRatio * zoomLevel, AspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}
	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
	{
		AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-AspectRatio * zoomLevel, AspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}
};
