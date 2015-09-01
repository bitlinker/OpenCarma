#include <Shader.h>
#include <Exception.h>

namespace OpenCarma
{
    Shader::Shader(const GLuint type)
        : m_shader(0)
        , isCompiled(false)
    {
        m_shader = glCreateShader(type);
    }

    bool Shader::setSource(const std::string& source)
    {
        if (isCompiled)
            return false;

        const char *srcPtr = &source[0];
        glShaderSource(m_shader, 1, &srcPtr, NULL);
        return true;
    }

    bool Shader::compile()
    {
        if (isCompiled)
            return false;

        glCompileShader(m_shader);
        isCompiled = checkCompileStatus();

        return isCompiled;
    }

    bool Shader::checkCompileStatus()
    {
        GLint compiled = 0;
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compiled);
        return compiled == GL_TRUE;
    }

    void Shader::getInfoLog(std::string& log)
    {
        log.clear();

        GLint logLen = 0;
        glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen)
        {
            log.resize(logLen);
            glGetShaderInfoLog(m_shader, logLen, &logLen, &log[0]);
        }
    }

    Shader::~Shader()
    {
        glDeleteShader(m_shader);
    }

    /*void Shader::loadBinary()
    {
    glShaderBinary(1, &m_shader, )
    }*/
}