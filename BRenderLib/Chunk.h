#pragma once
#include "Common.h"

namespace OpenCarma
{
    namespace BRender
    {
        //! Chunk magics:
        const uint32_t CHUNK_HEADER = 0x12;
        const uint32_t CHUNK_TEXTURE_HEAD = 0x3;

        class BR_API Chunk
        {
        public:
            Chunk();

            const uint32_t getMagic() const { return m_magic; }
            void setMagic(const uint32_t magic) { m_magic = magic; }

            const uint32_t getSize() const { return m_size; }
            void setSize(const uint32_t size) { m_size = size; }

            const bool isEmpty() const { return (m_size == 0 && m_magic == 0); }

        private:
            uint32_t m_magic;
            uint32_t m_size;
        };

        //! Texture or palette or shadetab header chunk
        class TextureHeadChunk : public Chunk
        {
        public:
        private:
            uint32_t m_type;		//!< 3 for pixel maps and shade tabs; 7 for palettes
            uint32_t m_width1;	    //!< Width for textures; number of components for palettes
            uint32_t m_width2;	    //!< Width for textures; 1 for palettes
            uint32_t m_height;	    //!< Height for textures; number of colors for palettes
            uint32_t m_u1;
            uint32_t m_u2;
            std::string m_name;     //!< Null-terminated name
        };


    }
}