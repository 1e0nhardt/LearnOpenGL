#include "pch.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include <imgui.h>

struct GLFWwindow;

namespace LGL
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
        : m_CurrentTest(nullptr)
    {
        LGL_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        WindowProps windowProps("LearnOpenGL", 1280, 720);
        m_Window = CreateScope<WindowsWindow>(windowProps);
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        Renderer::Init();

        GLFWwindow* window = m_Window->GetNativeWindow();
        m_ImGuiLayer = new ImGuiLayer(window);
        //m_ImGuiLayer = new ImGuiLayer(m_Window->GetNativeWindow()); // 为什么这样写不行？C2665 没有重载函数可以转换所有参数类型
        m_ImGuiLayer->OnAttach();

        m_TestMenu = new TestMenu(m_CurrentTest);
        m_CurrentTest = m_TestMenu;
    }

    Application::~Application()
    {
        m_ImGuiLayer->OnDetach();
        delete m_ImGuiLayer;
        if (m_CurrentTest != m_TestMenu && m_CurrentTest != nullptr)
            delete m_CurrentTest;
        delete m_TestMenu;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            float currentFrameTime = static_cast<float>(glfwGetTime());
            float deltaTime = currentFrameTime - m_LastFrameTime;
            m_LastFrameTime = currentFrameTime;

            // render
            // ------
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::Clear();

            m_ImGuiLayer->Begin();
            if (m_CurrentTest)
            {
                m_CurrentTest->OnUpdate(deltaTime);
                m_CurrentTest->OnRender();
                ImGui::Begin("Test");
                if (m_CurrentTest != m_TestMenu && ImGui::Button("<-"))
                {
                    delete m_CurrentTest;
                    m_CurrentTest = m_TestMenu;
                }
                m_CurrentTest->OnImGuiRender();
                ImGui::End();
            }

            m_ImGuiLayer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

        m_CurrentTest->OnEvent(e);
    }
    
    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

    LGL::Application* Application::s_Instance = nullptr;

}