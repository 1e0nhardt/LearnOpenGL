#pragma once

#include "Events/Event.h"

#include <GLFW/glfw3.h>

namespace LGL
{
    using EventCallback = std::function<void(Event&)>;

    struct WindowProps
    {
        unsigned int Width;
        unsigned int Height;
        std::string Title;

        WindowProps(const std::string& title = "LearnOpenGL",
            unsigned int width = 1280,
            unsigned int height = 720)
            : Title(title), Width(width), Height(height)
        {
        }
    };

	class WindowsWindow
	{
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        WindowsWindow(const WindowProps& props);
        ~WindowsWindow();

        void OnUpdate();

        inline unsigned int GetWidth() const { return m_Data.Width; }
        inline unsigned int GetHeight() const { return m_Data.Height; }

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVSync() const;

        inline GLFWwindow* GetNativeWindow() const { return m_Window; }
        inline void DisableCursor() { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
        inline void EnableCursor() { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
    private:
        void Init(const WindowProps& props);
        void Shutdown();
    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
	};
}