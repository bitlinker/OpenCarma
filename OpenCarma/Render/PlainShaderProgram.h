#pragma once
#include <Render/ShaderProgram.h>

namespace OpenCarma
{
    namespace Render
    {
        // TODO: rename to blinn/phong?
        // add material properties
        class PlainShaderProgram : public Commons::Render::ShaderProgram
        {
        public:
            PlainShaderProgram();
            virtual ~PlainShaderProgram();

            void setMVP(const glm::mat4& matrix);
            void setTex1Sampler(uint32_t sampler);

        private:
            void init();

        private:
            uint32_t m_uMVP;
            uint32_t m_uTex1;
        };

        typedef std::shared_ptr<PlainShaderProgram> PlainShaderProgramPtr;
    }
}
