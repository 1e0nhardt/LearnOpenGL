#include "pch.h"
#include "Texture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace LGL
{
	
    Texture2D::Texture2D(const std::string& path, const std::string& name, bool vflip/*=true*/)
        : m_VFlip(vflip), m_TypeName(name)
    {
        m_Path = path.substr(path.find_last_of('/') + 1);

        int width, height, channels;
        stbi_set_flip_vertically_on_load(m_VFlip);
        //LGL_CORE_INFO(path);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        LGL_CORE_ASSERT(data, "Failed to load image!");
        //LGL_CORE_INFO("{0}x{1}x{2}", width, height, channels);

        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        LGL_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
        //glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        //LGL_CORE_WARN("Texture Deleted: {0}", m_Path);
        //glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::Bind(uint32_t slot/*=0*/) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }

}