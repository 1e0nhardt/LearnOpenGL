#include "pch.h"
#include "TestHelloTriangle.h"

namespace LGL
{
	
    TestHelloTriangle::TestHelloTriangle()
    {
        m_Texture = CreateRef<Texture2D>("D:/MyCodes/GAMES/LearnOpenGL/LearnOpenGL/assets/images/awesomeface.png");

        float vertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // 右上角
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 右下角
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // 左上角
        };

        uint32_t indices[] = {
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
        };

        m_Shader = CreateScope<Shader>("D:/MyCodes/GAMES/LearnOpenGL/LearnOpenGL/shaders/hello_triangle.glsl");
        m_VAO = CreateScope<VertexArray>();

        Ref<VertexBuffer> vbo = CreateRef<VertexBuffer>(vertices, static_cast<uint32_t>(sizeof(vertices)));
        BufferLayout layout = {
            BufferElement(ShaderDataType::Float3, "a_Position"),
            BufferElement(ShaderDataType::Float2, "a_TexCoords"),
        };
        vbo->SetLayout(layout);
        m_VAO->AddVertexBuffer(vbo);
        
        Ref<IndexBuffer> ebo = CreateRef<IndexBuffer>(indices, static_cast<uint32_t>(sizeof(indices) / sizeof(uint32_t)));
        m_VAO->SetIndexBuffer(ebo);

        m_Shader->Bind();
        m_Shader->UploadUniformInt("texture0", 0);
    }

    void TestHelloTriangle::OnRender()
    {
        m_Texture->Bind(0);
        m_Shader->Bind();
        m_VAO->Bind();
        RenderCommand::DrawIndexed(m_VAO);
    }

    void TestHelloTriangle::OnImGuiRender()
    {

    }

}