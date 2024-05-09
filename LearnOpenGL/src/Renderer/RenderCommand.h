#pragma once

#include "VertexArray.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace LGL
{

	class RenderCommand
	{
	public:
		static void Init() {
            // configure global opengl state
            // -----------------------------
            // FragmentShader -> 模板测试 -> 深度测试
            glEnable(GL_DEPTH_TEST);
            //glDepthMask(GL_FALSE); // 禁止写入深度缓冲。 
            //glDepthFunc(GL_ALWAYS); // always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))

            //glDepthFunc(GL_LESS);
            //glEnable(GL_STENCIL_TEST);
            //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            //glEnable(GL_STENCIL_TEST);
            //// 设置一个位掩码(Bitmask)，它会与将要写入缓冲的深度/模板值进行与(AND)运算
            //glStencilMask(0xFF); // 每一位写入模板缓冲时都保持原样
            ////glStencilMask(0x00); // 每一位在写入模板缓冲时都会变成0（禁用写入）
            //glStencilFunc(GL_ALWAYS, 1, 0xFF); // 设置用于模板测试的函数
            //glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // 模板测试S, 深度测试D结果对应的行为。 S-，S+D-, S-D- 
		}

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) 
        {
            glViewport(x, y, width, height);
        }

        static void SetClearColor(const glm::vec4& color)
        {
            glClearColor(color.x, color.y, color.z, color.w);
        }

        static void Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }

        static void EnableBlend() { glEnable(GL_BLEND); }
        static void DisableBlend() { glDisable(GL_BLEND); }
        static void SetBlendFunc(GLenum srcfactor, GLenum destfactor) { glBlendFunc(srcfactor, destfactor); }
        static void SetAlphaBlend() { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }

        static void EnableDepthTest() { glEnable(GL_DEPTH_TEST); }
        static void DisableDepthTest() { glDisable(GL_DEPTH_TEST); }
        // func: GL_NEVER, GL_ALWAYS, GL_LESS, GL_LEQUAL, GL_EQUAL, GL_GEQUAL, GL_GREATER, GL_NOTEQUAL
        static void SetDepthTestFunc(GLenum func) { glDepthFunc(func); }
        static void SetDepthTestMask(GLboolean canWrite) { glDepthMask(canWrite);  }

        static void EnableStencilTest() { glEnable(GL_STENCIL_TEST); }
        static void DisableStencilTest() { glDisable(GL_STENCIL_TEST); }
        // func: GL_NEVER, GL_ALWAYS, GL_LESS, GL_LEQUAL, GL_EQUAL, GL_GEQUAL, GL_GREATER, GL_NOTEQUAL
        // if (func(ref&mask, stencil_val&mask)) 
        //     stencil test pass
        static void SetStencilTestFunc(GLenum func, GLint ref, GLuint mask) { glStencilFunc(func, ref, mask); }
        // 写入模板缓冲时，只有mask为1的位可以写入。
        static void SetStencilTestMask(GLuint mask) { glStencilMask(0x00); }
        // fail: 模板测试失败时的操作
        // zfail: 模板测试通过，深度测试失败
        // zpass: 模板测试和深度测试都通过
        // GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR, GL_DECR_WRAP, GL_INVERT
        static void SetStencilTestOp(GLenum fail, GLenum zfail, GLenum zpass) { glStencilOp(fail, zfail, zpass); }

        static void Draw(const VertexArray& vao)
        {
            glDrawArrays(GL_TRIANGLES, 0, vao.GetVertexBufferCount());
        }

        static void DrawIndexed(const Ref<VertexArray>& vao)
        {
            glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(vao->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);
        }
        
        static void DrawIndexed(const Scope<VertexArray>& vao)
        {
            glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(vao->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);
        }
	};
}