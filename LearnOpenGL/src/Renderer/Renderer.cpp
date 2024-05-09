#include "pch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace LGL
{
    Scope<LGL::Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    /*void Renderer::BeginScene(Camera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }*/

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(Shader& shader, const VertexArray& vertexArray, const glm::mat4& transform)
    {
        shader.Bind();
        shader.UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader.UploadUniformMat4("u_Transform", transform);

        vertexArray.Bind();
        //RenderCommand::DrawIndexed(vertexArray);
    }

}