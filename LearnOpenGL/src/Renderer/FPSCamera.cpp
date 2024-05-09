#include "pch.h"
#include "FPSCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace LGL
{
	
    FPSCamera::FPSCamera(float fovY, float aspectRatio, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : FovY(fovY), AspectRatio(aspectRatio), Position(position), Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(up), Yaw(yaw), Pitch(pitch)
    {
        UpdateVectors();
    }

    void FPSCamera::ProcessMouseMove(float xOffset, float yOffset, bool constrainPitch /*= true*/)
    {
        Yaw += xOffset;
        Pitch += yOffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        UpdateVectors();
    }

    const glm::mat4 FPSCamera::GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    const glm::mat4 FPSCamera::GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(FovY), AspectRatio, 0.1f, 100.0f);
    }

    const glm::mat4 FPSCamera::GetViewProjectionMatrix() const
    {
        return glm::perspective(glm::radians(FovY), AspectRatio, 0.1f, 100.0f) * glm::lookAt(Position, Position + Front, Up);
    }

    void FPSCamera::UpdateVectors()
    {
        glm::vec3 front = { 0.0f, 0.0f, 0.0f };
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }

}