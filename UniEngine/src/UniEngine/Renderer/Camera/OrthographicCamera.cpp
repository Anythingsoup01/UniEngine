#include "uepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace UE {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: oc_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		
		oc_ViewProjectionMatrix = oc_ProjectionMatrix * oc_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), oc_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(oc_Rotation), glm::vec3(0, 0, 1));

		oc_ViewMatrix = glm::inverse(transform);
		oc_ViewProjectionMatrix = oc_ProjectionMatrix * oc_ViewMatrix;
	}
}