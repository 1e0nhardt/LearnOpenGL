#pragma once

#include "OrthographicCamera.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace LGL
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRation = 16.0f / 9.0f, bool rotation=true);

		void OnUpdate(float deltaTime);
		void OnEvent(Event& e);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
    public:
        OrthographicCamera Camera;
        bool CanRotate = true;
	private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.5f };
        float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}