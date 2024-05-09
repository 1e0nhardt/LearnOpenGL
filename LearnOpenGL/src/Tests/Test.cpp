#include "pch.h"
#include "Test.h"

#include <imgui.h>

namespace LGL
{
	
    TestMenu::TestMenu(Test*& currentTestPtr):
        m_CurrentTest(currentTestPtr)
    {

    }

    void TestMenu::OnImGuiRender()
    {
        for (auto& test : m_Tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                m_CurrentTest = test.second();
            }
            //ImGui::SameLine();
        }
    }

}