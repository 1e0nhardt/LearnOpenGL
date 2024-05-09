#pragma once

#include "Test.h"

namespace LGL
{
	class TestDepthStencil : public Test
	{
	public:
		TestDepthStencil();

		void OnRender() override;
		void OnImGuiRender() override;
	private:
        Scope<VertexArray> m_CubeVAO, m_PlaneVAO;
		Scope<Shader> m_ObjectShader, m_SingleColorShader;
		Scope<Texture2D> m_CubeTexture, m_FloorTexture;

	ADD_CAMERA(FPSCameraController)
	};
}