#include "pch.h"
#include "FPSCameraController.h"
#include "Core/KeyCodes.h"
#include "Core/Application.h"
#include "Core/Input.h"

namespace LGL
{
	
    FPSCameraController::FPSCameraController(float fovY, float aspectRatio)
        : Camera(FPSCamera(fovY, aspectRatio))
    {
    }

    void FPSCameraController::OnUpdate(float deltaTime)
    {
        float velocity = CameraTranslationSpeed * deltaTime;
        if (Input::IsKeyPressed(LGL_KEY_W))
            Camera.Position += Camera.Front * velocity;
        if (Input::IsKeyPressed(LGL_KEY_S))
            Camera.Position -= Camera.Front * velocity;
        if (Input::IsKeyPressed(LGL_KEY_A))
            Camera.Position -= Camera.Right * velocity;
        if (Input::IsKeyPressed(LGL_KEY_D))
            Camera.Position += Camera.Right * velocity;
        if (Input::IsKeyPressed(LGL_KEY_Q))
            Camera.Position += Camera.Up * velocity;
        if (Input::IsKeyPressed(LGL_KEY_E))
            Camera.Position -= Camera.Up * velocity;
    }

    void FPSCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(LGL_BIND_EVENT_FN(FPSCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(LGL_BIND_EVENT_FN(FPSCameraController::OnWindowResized));
        dispatcher.Dispatch<MouseMovedEvent>(LGL_BIND_EVENT_FN(FPSCameraController::OnMouseMoved));
        dispatcher.Dispatch<KeyReleasedEvent>(LGL_BIND_EVENT_FN(FPSCameraController::OnKeyReleased));
    }

    bool FPSCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        Camera.FovY -= e.GetYOffset() * 0.2f;
        Camera.FovY = std::max(Camera.FovY, 0.25f);
        LGL_CORE_INFO("Camera FovY: {0}", Camera.FovY);
        return false;
    }

    bool FPSCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        Camera.AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        return false;
    }

    bool FPSCameraController::OnMouseMoved(MouseMovedEvent& e)
    {
        float xpos = e.GetX();
        float ypos = e.GetY();

        if (m_FirstMouse)
        {
            m_LastMouseX = xpos;
            m_LastMouseY = ypos;

            m_FirstMouse = false;
        }

        float xoffset = xpos - m_LastMouseX;
        float yoffset = ypos - m_LastMouseY;

        m_LastMouseX = xpos;
        m_LastMouseY = ypos;

        Camera.ProcessMouseMove(xoffset * MouseSensitivity, yoffset * MouseSensitivity);
        return false;
    }

    bool FPSCameraController::OnKeyReleased(KeyReleasedEvent& e)
    {
        if (e.GetKeyCode() == LGL_KEY_SPACE)
        {
            if (m_CursorDisabled)
            {
                m_FirstMouse = true;
                Application::Get().GetWindow().EnableCursor();
            }
            else
                Application::Get().GetWindow().DisableCursor();

            m_CursorDisabled = !m_CursorDisabled;
        }

        return false;
    }

}