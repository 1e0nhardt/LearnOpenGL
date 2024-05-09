#pragma once

#include "Buffer.h"

#include <vector>

namespace LGL
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Bind() const;
		void Unbind();

		void AddVertexBuffer(const Ref<VertexBuffer>& vbo);
		void SetIndexBuffer(const Ref<IndexBuffer>& ebo);

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VBOs; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_EBO; }
		uint32_t GetVertexBufferCount() const;
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VBOs;
		Ref<IndexBuffer> m_EBO;
	};
}