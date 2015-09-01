#pragma once
#include <Common.h>
#include <RenderCommon.h>

// TODO: move
#include <Objects/Pixmap.h>

namespace OpenCarma
{
    // TODO: disable copy & assign
    class Texture
    {
    public:
        Texture();
        ~Texture();

        void setMinFilter(GLenum filter);
        void setMagFilter(GLenum filter);

        void setTexData2d();        

        void bind();
        void unbind();

    private:
        GLuint m_tex;
    };

    typedef std::shared_ptr<Texture> TexturePtr;
    typedef std::weak_ptr<Texture> TextureWeakPtr;
}