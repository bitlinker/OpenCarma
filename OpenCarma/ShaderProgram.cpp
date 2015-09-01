#include "ShaderProgram.h"

namespace OpenCarma
{
    ShaderProgram::ShaderProgram()
        : m_program(0)
        , attachedShaders()
        , isLinked(false)
        , isValidated(false)
    {
        m_program = glCreateProgram();
    }

    bool ShaderProgram::attach(const ShaderPtr& shader)
    {
        if (isLinked)
            return false;

        attachedShaders.insert(shader);
        glAttachShader(m_program, shader->get());
        return true;
    }

    bool ShaderProgram::detach(const ShaderPtr& shader)
    {
        if (isLinked)
            return false;

        attachedShaders.erase(shader);
        glDetachShader(m_program, shader->get());
        return true;
    }

    bool ShaderProgram::link()
    {
        if (isLinked)
            return false;

        glLinkProgram(m_program);
        isLinked = checkLinkStatus();
        return isLinked;
    }

    bool ShaderProgram::validate()
    {
        if (isValidated)
            return false;

        glValidateProgram(m_program);
        isValidated = checkValidateStatus();

        return isValidated;
    }

    bool ShaderProgram::checkValidateStatus()
    {
        GLint validateStatus = 0;
        glGetProgramiv(m_program, GL_VALIDATE_STATUS, &validateStatus);
        return validateStatus == GL_TRUE;
    }

    bool ShaderProgram::checkLinkStatus()
    {
        GLint linkStatus = 0;
        glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);
        return linkStatus == GL_TRUE;
    }

    void ShaderProgram::getInfoLog(std::string& log)
    {
        log.clear();

        GLint logLen = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen)
        {
            log.resize(logLen);
            glGetProgramInfoLog(m_program, logLen, &logLen, &log[0]);
        }
    }

    bool ShaderProgram::use()
    {
        if (!isLinked)
            return false;

        glUseProgram(m_program);
        return true;
    }

    uint32_t ShaderProgram::getNumUniforms()
    {
        if (!isLinked)
            return 0;

        GLint uniforms = 0;
        glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &uniforms);
        return uniforms;
    }    

    uint32_t ShaderProgram::getUniform(uint32_t index)
    {
        if (!isLinked)
            return 0;

        //glGetProgram with the value GL_ACTIVE_UNIFORM_MAX_LENGTH
        GLsizei len = 256; // TODO
        std::string name;
        name.resize(len);

        GLint size = 0;
        GLenum type = 0;
        
        glGetActiveUniform(m_program, index, len, &len, &size, &type, &name[0]);
        return size; // TODO
    }

    uint32_t ShaderProgram::getUniformLocation(const std::string& name)
    {
        if (!isLinked)
            return 0;

        return (uint32_t)glGetUniformLocation(m_program, name.c_str());
    }

    bool ShaderProgram::setUniformMatrix(uint32_t index, const glm::mat4& mat)
    {
        if (!isLinked)
            return false;

        glUniformMatrix4fv(index, 1, GL_FALSE, &mat[0][0]);
        return true;
    }

    bool ShaderProgram::setUniformSampler2D(uint32_t index, uint32_t samplerId)
    {
        if (!isLinked)
            return false;

        glUniform1ui(index, samplerId);
        return true;
    }    

    uint32_t ShaderProgram::getNumAttributes()
    {
        if (!isLinked)
            return 0;

        GLint attributes = 0;
        glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &attributes);
        return attributes;
    }

    uint32_t ShaderProgram::getAttribute(uint32_t index)
    {
        if (!isLinked)
            return 0;

        GLsizei len = 256; // TODO
        std::string name;
        name.resize(len);

        GLint size = 0;
        GLenum type = 0;

        glGetActiveAttrib(m_program, index, len, &len, &size, &type, &name[0]);
        return size; // TODO
    }

    uint32_t ShaderProgram::getAttributeLocation(const std::string& name)
    {
        if (!isLinked)
            return 0;

        return glGetAttribLocation(m_program, name.c_str());
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_program);
    }
}