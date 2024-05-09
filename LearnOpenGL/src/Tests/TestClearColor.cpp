#include "pch.h"
#include "TestClearColor.h"

namespace LGL
{
	
    TestClearColor::TestClearColor()
        : m_ClearColor{ 0.1f, 0.2f, 0.8f, 1.0f }
    {

    }

    void TestClearColor::OnRender()
    {
        RenderCommand::SetClearColor(m_ClearColor);
        RenderCommand::Clear();
    }

    void TestClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_ClearColor));
    }

}