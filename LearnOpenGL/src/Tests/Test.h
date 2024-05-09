#pragma once

#include <string>
#include <vector>
#include <functional>

#include "LGL.h"

#include <imgui.h>

#define ADD_CAMERA(type) \
public:\
	inline void OnEvent(Event& e) override { m_CameraController->OnEvent(e); };\
	inline void OnUpdate(float deltaTime) override { m_CameraController->OnUpdate(deltaTime); }\
private:\
	Scope<##type> m_CameraController;

namespace LGL
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() = default;

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPtr);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			LGL_TRACE("Registering Test:{0}", name);
			m_Tests.push_back(make_pair(name, []() { return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};

}