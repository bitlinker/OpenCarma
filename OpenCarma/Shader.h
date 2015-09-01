#pragma once
#include <RenderCommon.h>

namespace OpenCarma
{
    class Shader
    {
    public:
        // GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
        Shader(const GLuint type);
        ~Shader();

        bool compile();
        bool setSource(const std::string& source);

        GLuint get() const { return m_shader; }

        void getInfoLog(std::string& log);

    private:
        bool checkCompileStatus();

    private:
        GLuint m_shader;
        bool isCompiled;
    };

    typedef std::shared_ptr<Shader> ShaderPtr;
}