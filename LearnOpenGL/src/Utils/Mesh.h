#pragma once

//#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/RenderCommand.h"
#include "Vertex.h"

#include <string>
#include <vector>

namespace LGL
{

    class Mesh 
    {
    public:
        // mesh Data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture2D>    textures;

        Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture2D>& textures);

        void Draw(Shader& shader);
    private:
        void setupMesh();
    private:
        Scope<VertexArray> m_VAO;
    };
}