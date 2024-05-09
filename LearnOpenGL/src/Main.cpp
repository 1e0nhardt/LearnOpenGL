#include "pch.h"
#include "LGL.h"
#include "Core/Application.h"
#include "Tests/Test.h"
#include "Tests/TestClearColor.h"
#include "Tests/TestDepthStencil.h"
#include "Tests/TestLoadModel.h"
#include "Tests/TestHelloTriangle.h"

using namespace LGL;

int main()
{
    Log::Init();

    Application* app = new Application();
    app->RegisterTest<TestClearColor>("ClearColor");
    app->RegisterTest<TestDepthStencil>("DepthTest&StencilTest");
    app->RegisterTest<TestLoadModel>("LoadModel");
    app->RegisterTest<TestHelloTriangle>("HelloTriangle");
    app->Run();
    delete app;    
    return 0;
}