#pragma once

namespace LGL
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& path, const std::string& typeName="", bool vflip = true);
		~Texture2D();

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		const std::string& GetPath() const { return m_Path; }
		// texture_diffuse, texture_normal, ...
		const std::string& GetTypeName() const { return m_TypeName; }

		void Bind(uint32_t slot=0) const;
	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
		std::string m_Path;
		std::string m_TypeName;
		bool m_VFlip;
	};
}