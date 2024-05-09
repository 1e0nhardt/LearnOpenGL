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
            // FragmentShader -> ģ����� -> ��Ȳ���
            glEnable(GL_DEPTH_TEST);
            //glDepthMask(GL_FALSE); // ��ֹд����Ȼ��塣 
            //glDepthFunc(GL_ALWAYS); // always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))

            //glDepthFunc(GL_LESS);
            //glEnable(GL_STENCIL_TEST);
            //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            //glEnable(GL_STENCIL_TEST);
            //// ����һ��λ����(Bitmask)�������뽫Ҫд�뻺������/ģ��ֵ������(AND)����
            //glStencilMask(0xFF); // ÿһλд��ģ�建��ʱ������ԭ��
            ////glStencilMask(0x00); // ÿһλ��д��ģ�建��ʱ������0������д�룩
            //glStencilFunc(GL_ALWAYS, 1, 0xFF); // ��������ģ����Եĺ���
            //glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // ģ�����S, ��Ȳ���D�����Ӧ����Ϊ�� S-��S+D-, S-D- 
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
        // д��ģ�建��ʱ��ֻ��maskΪ1��λ����д�롣
        static void SetStencilTestMask(GLuint mask) { glStencilMask(0x00); }
        // fail: ģ�����ʧ��ʱ�Ĳ���
        // zfail: ģ�����ͨ������Ȳ���ʧ��
        // zpass: ģ����Ժ���Ȳ��Զ�ͨ��
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