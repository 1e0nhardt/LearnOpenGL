#pragma once

#include <GLFW/glfw3.h>

namespace LGL
{
	class ImGuiLayer
	{
	public:
		ImGuiLayer(GLFWwindow*& window) : m_Window(window) {};

		void OnAttach();
		void OnDetach();

		void Begin();
		void OnImGuiRender();
		void End();
	private:
		GLFWwindow*& m_Window;
	};
}