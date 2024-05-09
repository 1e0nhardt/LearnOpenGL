#pragma once

#include "Test.h"
#include "LGL.h"
#include "Utils/Model.h"

namespace LGL
{
    class TestLoadModel : public Test
    {
    public:
        TestLoadModel();

        void OnRender() override;
        void OnImGuiRender() override;
    private:
        Scope<Model> m_Model;
        Scope<Shader> m_Shader;

    ADD_CAMERA(FPSCameraController)
    };
}

