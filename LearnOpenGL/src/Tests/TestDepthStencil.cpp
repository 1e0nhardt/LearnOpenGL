#include "pch.h"
#include "TestDepthStencil.h"

namespace LGL
{
	
    TestDepthStencil::TestDepthStencil()
    {
        m_CameraController = CreateScope<FPSCameraController>();
        m_ObjectShader = CreateScope<Shader>("shaders/main.glsl");
        m_SingleColorShader = CreateScope<Shader>("shaders/single_color.glsl");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float cubeVertices[] = {
            // positions          // texture Coords
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        float planeVertices[] = {
            // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
             5.0f, -0.5f, -5.0f,  2.0f, 2.0f
        };

        // cube VAO
        m_CubeVAO = CreateScope<VertexArray>();
        Ref<VertexBuffer> cubeVBO = CreateRef<VertexBuffer>(cubeVertices, (uint32_t)sizeof(cubeVertices));
        BufferLayout cubeDataLayout = {
            BufferElement(ShaderDataType::Float3, "a_Position"),
            BufferElement(ShaderDataType::Float2, "a_TexCoord")
        };
        cubeVBO->SetLayout(cubeDataLayout);
        m_CubeVAO->AddVertexBuffer(cubeVBO);

        // plane VAO
        m_PlaneVAO = CreateScope<VertexArray>();
        Ref<VertexBuffer> planeVBO = CreateRef<VertexBuffer>(planeVertices, (uint32_t)sizeof(planeVertices));
        BufferLayout planeDataLayout = {
            BufferElement(ShaderDataType::Float3, "a_Position"),
            BufferElement(ShaderDataType::Float2, "a_TexCoord")
        };
        planeVBO->SetLayout(planeDataLayout);
        m_PlaneVAO->AddVertexBuffer(planeVBO);

        // load textures
        // -------------
        m_CubeTexture = CreateScope<Texture2D>("assets/images/marble.jpg");
        m_FloorTexture = CreateScope<Texture2D>("assets/images/metal.png");

        // shader configuration
        // --------------------
        m_ObjectShader->Bind();
        m_ObjectShader->UploadUniformInt("texture1", 0);
    }

    void TestDepthStencil::OnRender()
    {
        RenderCommand::EnableStencilTest();
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF); // ÆôÓÃÄ£°å»º³åÐ´Èë

        m_SingleColorShader->Bind();
        glm::mat4 view = m_CameraController->Camera.GetViewMatrix();
        glm::mat4 projection = m_CameraController->Camera.GetProjectionMatrix();
        m_SingleColorShader->UploadUniformMat4("view", view);
        m_SingleColorShader->UploadUniformMat4("projection", projection);

        m_ObjectShader->Bind();
        glm::mat4 model = glm::mat4(1.0f);
        m_ObjectShader->UploadUniformMat4("view", view);
        m_ObjectShader->UploadUniformMat4("projection", projection);

        // cubes
        m_CubeTexture->Bind();
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        m_ObjectShader->UploadUniformMat4("model", model);
        m_CubeVAO->Bind();
        RenderCommand::Draw(*m_CubeVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        m_ObjectShader->UploadUniformMat4("model", model);
        m_CubeVAO->Bind();
        RenderCommand::Draw(*m_CubeVAO);

        // floor
        glStencilMask(0x00);
        m_FloorTexture->Bind();
        m_ObjectShader->UploadUniformMat4("model", glm::mat4(1.0f));
        m_PlaneVAO->Bind();
        RenderCommand::Draw(*m_PlaneVAO);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00); // ½ûÖ¹Ä£°å»º³åµÄÐ´Èë
        glDisable(GL_DEPTH_TEST);
        m_SingleColorShader->Bind();
        // cubes
        m_CubeTexture->Bind();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(1.12f, 1.12f, 1.12f));
        m_SingleColorShader->UploadUniformMat4("model", model);
        m_CubeVAO->Bind();
        RenderCommand::Draw(*m_CubeVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.12f, 1.12f, 1.12f));
        m_SingleColorShader->UploadUniformMat4("model", model);
        m_CubeVAO->Bind();
        RenderCommand::Draw(*m_CubeVAO);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glBindVertexArray(0);
        glEnable(GL_DEPTH_TEST);
    }

    void TestDepthStencil::OnImGuiRender()
    {

    }

}