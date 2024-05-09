#pragma once

#include "Test.h"

namespace LGL
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();

		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::vec4 m_ClearColor;
	};
}