#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Base.h"
#include "Core/KeyCodes.h"
#include "Core/MouseButtonCodes.h"
#include "Core/Input.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/OrthographicCameraController.h"
#include "Renderer/FPSCamera.h"
#include "Renderer/FPSCameraController.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "ImGui/ImGuiLayer.h"