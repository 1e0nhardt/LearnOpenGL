#pragma once

#include "Test.h"
#include "LGL.h"

namespace LGL
{
	class TestHelloTriangle : public Test
	{
	public:
		TestHelloTriangle();

        void OnRender() override;
        void OnImGuiRender() override;
	private:
		Scope<VertexArray> m_VAO;
		Scope<Shader> m_Shader;
		Ref<Texture2D> m_Texture;
	};
}