#pragma once

#include "WindowsWindow.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

#include "Tests/Test.h"

namespace LGL
{

	class Application
	{
	public:
		Application();
		~Application();

		void OnEvent(Event& e);
		void Run();
        template<typename T>
        void RegisterTest(const std::string& name)
        {
            m_TestMenu->RegisterTest<T>(name);
        }

		inline WindowsWindow& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<WindowsWindow> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		Test* m_CurrentTest;
        TestMenu* m_TestMenu;
    private:
        static Application* s_Instance;
	};
}