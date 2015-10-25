#include <Render/RenderCommon.h>
#include <PlainShaderProgram.h>
#include <Logger/Log.h>
#include <Exception/exception.h>

namespace OpenCarma
{
    namespace Render
    {
        static const std::string FRAGMENT_SHADER =
            "#version 400\n"
            "out vec4 frag_colour;"
            "uniform sampler2D u_tex1;"
            "in vec2 v_uv;"
            "void main () {"
            //"  frag_colour = texture(u_tex1, v_uv);"
            "  frag_colour = vec4(v_uv[0], v_uv[1], 1.0, 1.0);"
            //"  frag_colour = vec4(1.0, 1.0, 0.0, 1.0);"
            "}";

        static const std::string VERTEX_SHADER =
            "#version 400\n"
            "layout(location = 0) in vec3 vp;"
            "layout(location = 1) in vec2 uv;"
            "uniform mat4 m_MVP;"
            "out vec2 v_uv;"
            "void main () {"
            "  v_uv = uv;"
            "  gl_Position = m_MVP * vec4(vp, 1.0);"
            "}";

        PlainShaderProgram::PlainShaderProgram()
            : ShaderProgram()
        {
            init();
        }

        PlainShaderProgram::~PlainShaderProgram()
        {
        }

        static void WriteShaderLog(const std::string& log)
        {
            if (!log.empty())
            {
                LOG_WARN(log.c_str());
            }
        }

        void PlainShaderProgram::init()
        {
            Commons::Render::ShaderPtr vs(new Commons::Render::Shader(GL_VERTEX_SHADER));
            vs->setSource(VERTEX_SHADER);
            LOG_INFO("Compiling plain vertex shader...");
            bool isCompiled = vs->compile();
            std::string log;
            vs->getInfoLog(log);
            WriteShaderLog(log);
            if (!isCompiled)
                throw Commons::GLException("Can't compile vertex shader. See log for details");

            Commons::Render::ShaderPtr fs(new Commons::Render::Shader(GL_FRAGMENT_SHADER));
            fs->setSource(FRAGMENT_SHADER);
            isCompiled = fs->compile();
            fs->getInfoLog(log);
            WriteShaderLog(log);
            if (!isCompiled)
                throw Commons::GLException("Can't compile fragment shader. See log for details");

            // Link
            attach(fs);
            attach(vs);

            bool isLinked = link();
            getInfoLog(log);
            WriteShaderLog(log);
            if (!isLinked)
                throw Commons::GLException("Can't link shader program. See log for details");



            bool isValidated = validate();
            getInfoLog(log);
            WriteShaderLog(log);
            if (!isValidated)
                throw Commons::GLException("Can't validate shader program. See log for details");

            //uint32_t a = m_shader->getNumAttributes();
            //uint32_t un = m_shader->getNumUniforms();

            // TODO: helpers...
            m_uMVP = getUniformLocation("m_MVP");
            m_uTex1 = getUniformLocation("u_tex1");
            setUniformSampler2D(m_uTex1, 0);
        }

        void PlainShaderProgram::setMVP(const glm::mat4& matrix)
        {
            setUniformMatrix(m_uMVP, matrix);
        }

        void PlainShaderProgram::setTex1Sampler(uint32_t sampler)
        {
            setUniformSampler2D(m_uTex1, sampler);
        }
    }
}
