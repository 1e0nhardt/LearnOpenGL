#pragma once

#include "FPSCamera.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace LGL
{
	class FPSCameraController
	{
	public:
		FPSCameraController(float fovY = 45.0f, float aspectRatio = 16.0f/9.0f);

        void OnUpdate(float deltaTime);
        void OnEvent(Event& e);
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnKeyReleased(KeyReleasedEvent& e);
    public:
        FPSCamera Camera;
        float CameraTranslationSpeed = 5.0f;
        float MouseSensitivity = 0.1f;
    private:
        float m_LastMouseX = 0.0f, m_LastMouseY = 0.0f;
        bool m_FirstMouse = true;
        bool m_CursorDisabled = false;
	};
}