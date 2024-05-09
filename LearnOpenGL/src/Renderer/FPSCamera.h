#pragma once

#include <glm/glm.hpp>

namespace LGL
{
	class FPSCamera
	{
	public:
		FPSCamera(float fovY, float aspectRatio, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch=0.0f);

		void ProcessMouseMove(float xOffset, float yOffset, bool constrainPitch = true);
		const glm::mat4 GetViewMatrix() const;
		const glm::mat4 GetProjectionMatrix() const;
		const glm::mat4 GetViewProjectionMatrix() const;
	private:
		void UpdateVectors();
	public:
        float FovY;
        float AspectRatio;
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
	private:
        float Yaw;
        float Pitch;
	};
}