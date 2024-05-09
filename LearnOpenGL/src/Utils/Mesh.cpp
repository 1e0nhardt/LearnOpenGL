#include "pch.h"
#include "Mesh.h"

namespace LGL
{
	
    Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture2D>& textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    void Mesh::Draw(Shader& shader)
    {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            //glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].GetTypeName();
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to string

            // now set the sampler to the correct texture unit
            shader.UploadUniformInt((name + number).c_str(), i);
            // and finally bind the texture
            textures[i].Bind(i);
        }

        // draw mesh
        m_VAO->Bind();
        RenderCommand::DrawIndexed(m_VAO);

        // always good practice to set everything back to defaults once configured.
        //glActiveTexture(GL_TEXTURE0);
    }

    void Mesh::setupMesh()
    {
        m_VAO = CreateScope<VertexArray>();
        Ref<VertexBuffer> meshVBO = CreateRef<VertexBuffer>(vertices, (uint32_t)(vertices.size() * sizeof(Vertex)));
        BufferLayout meshDataLayout = {
            BufferElement(ShaderDataType::Float3, "a_Position"),
            BufferElement(ShaderDataType::Float3, "a_Normal"),
            BufferElement(ShaderDataType::Float2, "a_TexCoord"),
            BufferElement(ShaderDataType::Float3, "a_Tangent"),
            BufferElement(ShaderDataType::Float3, "a_Bitengent"),
            BufferElement(ShaderDataType::Int4, "a_BoneIDs"),
            BufferElement(ShaderDataType::Float4, "a_Weights"),
        };
        meshVBO->SetLayout(meshDataLayout);
        m_VAO->AddVertexBuffer(meshVBO);

        Ref<IndexBuffer> meshEBO = CreateRef<IndexBuffer>(&indices[0], (uint32_t)indices.size());
        m_VAO->SetIndexBuffer(meshEBO);
    }
}