#include "pch.h"
#include "TestLoadModel.h"

namespace LGL
{
    TestLoadModel::TestLoadModel()
    {
        m_CameraController = CreateScope<FPSCameraController>();
        //m_Model = CreateScope<Model>(u8"D:/MyCodes/GAMES/LearnOpenGL/LearnOpenGL/assets/models/nanosuit/nanosuit.obj");
        m_Model = CreateScope<Model>(u8"D:/MyCodes/GAMES/LearnOpenGL/LearnOpenGL/assets/models/ºúÌÒ/ºúÌÒ.pmx");
        m_Shader = CreateScope<Shader>("D:/MyCodes/GAMES/LearnOpenGL/LearnOpenGL/shaders/model_loading.glsl");
    }

    void TestLoadModel::OnRender()
    {
        // don't forget to enable shader before setting uniforms
        m_Shader->Bind();

        // view/projection transformations
        glm::mat4 projection = m_CameraController->Camera.GetProjectionMatrix();
        glm::mat4 view = m_CameraController->Camera.GetViewMatrix();

        m_Shader->UploadUniformMat4("projection", projection);
        m_Shader->UploadUniformMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        m_Shader->UploadUniformMat4("model", model);
        m_Model->Draw(*m_Shader);
    }

    void TestLoadModel::OnImGuiRender()
    {

    }

}
