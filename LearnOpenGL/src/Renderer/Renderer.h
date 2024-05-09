#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include "VertexArray.h"

namespace LGL
{
	class Renderer
	{
	public:
		static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);

        //static void BeginScene(Camera& camera);
        static void EndScene();

        static void Submit(Shader& shader, const VertexArray& vertexArray, const glm::mat4& transform);
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> s_SceneData;
	};
}