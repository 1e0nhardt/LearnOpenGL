#include "pch.h"
#include "OrthographicCameraController.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/Application.h"

namespace LGL
{
	
    OrthographicCameraController::OrthographicCameraController(float aspectRation, bool rotation)
        : m_AspectRatio(aspectRation), Camera(-m_ZoomLevel*m_AspectRatio, m_ZoomLevel* m_AspectRatio, -m_ZoomLevel, m_ZoomLevel), CanRotate(rotation)
    {

    }

    void OrthographicCameraController::OnUpdate(float deltaTime)
    {
        if (Input::IsKeyPressed(LGL_KEY_A))
        {
            m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
            m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
        }
        else if (Input::IsKeyPressed(LGL_KEY_D))
        {
            m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
            m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
        }

        if (Input::IsKeyPressed(LGL_KEY_W))
        {
            m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
            m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
        }
        else if (Input::IsKeyPressed(LGL_KEY_S))
        {
            m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
            m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
        }

        if (CanRotate)
        {
            if (Input::IsKeyPressed(LGL_KEY_Q))
                m_CameraRotation += m_CameraRotationSpeed * deltaTime;
            if (Input::IsKeyPressed(LGL_KEY_E))
                m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

            if (m_CameraRotation > 180.0f)
                m_CameraRotation -= 360.0f;
            else if (m_CameraRotation <= -180.0f)
                m_CameraRotation += 360.0f;

            Camera.SetRotation(m_CameraRotation);
        }

        Camera.SetPosition(m_CameraPosition);

        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(LGL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(LGL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.2f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

}