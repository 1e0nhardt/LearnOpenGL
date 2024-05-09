#include "pch.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace LGL
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case LGL::ShaderDataType::Float:    return GL_FLOAT;
        case LGL::ShaderDataType::Float2:   return GL_FLOAT;
        case LGL::ShaderDataType::Float3:   return GL_FLOAT;
        case LGL::ShaderDataType::Float4:   return GL_FLOAT;
        case LGL::ShaderDataType::Mat3:     return GL_FLOAT;
        case LGL::ShaderDataType::Mat4:     return GL_FLOAT;
        case LGL::ShaderDataType::Int:      return GL_INT;
        case LGL::ShaderDataType::Int2:     return GL_INT;
        case LGL::ShaderDataType::Int3:     return GL_INT;
        case LGL::ShaderDataType::Int4:     return GL_INT;
        case LGL::ShaderDataType::Bool:     return GL_BOOL;
        }

        LGL_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vbo)
    {
        LGL_CORE_ASSERT(vbo->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vbo->Bind();
        const auto& layout = vbo->GetLayout();
        for (auto& element : layout)
        {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            if (element.Name == "a_BoneIDs")
            {
                glVertexAttribIPointer(
                    m_VertexBufferIndex,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    layout.GetStride(),
                    (const void*)(intptr_t)element.Offset);
                m_VertexBufferIndex++;
            }
            else
            {
                glVertexAttribPointer(
                    m_VertexBufferIndex,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized,
                    layout.GetStride(),
                    (const void*)(intptr_t)element.Offset);
                m_VertexBufferIndex++;
            }
        }

        m_VBOs.push_back(vbo);
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& ebo)
    {
        glBindVertexArray(m_RendererID);
        ebo->Bind();

        m_EBO = ebo;
    }

    uint32_t VertexArray::GetVertexBufferCount() const
    {
        uint32_t count = 0;
        for (auto& vbo : m_VBOs)
        {
            count += vbo->GetVertexCount();
        }
        return count;
    }

}