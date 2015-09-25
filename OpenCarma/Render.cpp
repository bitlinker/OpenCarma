#include <Render.h>
#include <Exception/Exception.h>
#include <Log.h>

// TODO: rm
#include <StaticModel.h>
#include <Serialization/ModelSerializer.h>
#include <fstream>

namespace OpenCarma
{
    // TODO: rm
    //StaticModelPtr mdl;

    // TODO
    void _update_fps_counter(GLFWwindow* window) {
        static double previous_seconds = glfwGetTime();
        static int frame_count;
        double current_seconds = glfwGetTime();
        double elapsed_seconds = current_seconds - previous_seconds;
        if (elapsed_seconds > 0.25) {
            previous_seconds = current_seconds;
            double fps = (double)frame_count / elapsed_seconds;
            char tmp[128];
            sprintf(tmp, "opengl @ fps: %.2f", fps);
            glfwSetWindowTitle(window, tmp);
            frame_count = 0;
        }
        frame_count++;
    }

	void Render::CursorCallbackStatic(GLFWwindow* window, double xpos, double ypos)
	{
		Render* render = reinterpret_cast<Render*>(glfwGetWindowUserPointer(window));
		if (render)
		{
			render->cursorCallback(xpos, ypos);
		}
	}

	Render::Render()
		: m_window()
		, m_texManager()
		, m_camera()
    {
        // TODO: options

        // FSAA
        //glfwWindowHint(GLFW_SAMPLES, 16);

        /*glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);*/

		glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);

        //glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        //glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // TODO: monitor & res selection
        GLFWmonitor* mon = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(mon);

        // TODO: use mode & mon
        m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(800, 600, "Title", NULL, NULL), glfwDestroyWindow);
        if (m_window == nullptr)
            throw Commons::UnknownException("Can't create GLFW window");
        glfwMakeContextCurrent(m_window.get());
		glfwSetWindowUserPointer(m_window.get(), this);

        // GLEW
        glewExperimental = GL_TRUE;
        if (GLEW_OK != glewInit())
            throw Commons::UnknownException("Can't init GLEW");

        const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
        const GLubyte* version = glGetString(GL_VERSION); // version as a string

		LOG_DEBUG("Renderer: %s, version: %s", renderer, version);


		// Mouse settings:
		// Disabled gives unlimited mouse movement for camera
		glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(m_window.get(), CursorCallbackStatic); // TODO: not needed? (have events)


        // Alpha blending
        /*glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

        // Alpha test
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.5F);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

        // TODO: mdl manager
        /*std::vector<BRender::ModelPtr> models;
        std::ifstream strm_mdl("e:/Games/Carma/DATA/MODELS/EAGBLAK.DAT", std::ifstream::binary);
        BRender::ModelSerializer::DeserializeModels(strm_mdl, models);*/

        //mdl.reset(new StaticModel());
        //mdl->init(models[0], *this);

        // TODO: rm
        const std::string fragment_shader =
            "#version 400\n"
            "out vec4 frag_colour;"
            "uniform sampler2D u_tex1;"
            "in vec2 v_uv;"
            "void main () {"
            //"  frag_colour = texture(u_tex1, v_uv);"
            //"  frag_colour = vec4(v_uv[0], v_uv[1], 0.0, 1.0);"
			"  frag_colour = vec4(1.0, 1.0, 0.0, 1.0);"
            "}";

        

        const std::string vertex_shader =
            "#version 400\n"
            "in vec3 vp;"
            "in vec2 uv;"
            "uniform mat4 m_MVP;"
            "out vec2 v_uv;"
            "void main () {"
            "  v_uv = uv;"
            "  gl_Position = m_MVP * vec4(vp, 1.0);"
            "}";

        ShaderPtr vs(new Shader(GL_VERTEX_SHADER));
        vs->setSource(vertex_shader);
        bool c1 = vs->compile();
        std::string log;
        vs->getInfoLog(log);

        ShaderPtr fs(new Shader(GL_FRAGMENT_SHADER));
        fs->setSource(fragment_shader);
        bool c2 = fs->compile();
        fs->getInfoLog(log);


		m_shader = std::make_shared<ShaderProgram>();
        
        m_shader->attach(fs);
		m_shader->attach(vs);

        bool l = m_shader->link();
		m_shader->getInfoLog(log);
		m_shader->validate();
		m_shader->getInfoLog(log);

        uint32_t a = m_shader->getNumAttributes();
        uint32_t un = m_shader->getNumUniforms();

		m_uMVP = m_shader->getUniformLocation("m_MVP");
        uint32_t uTex1 = m_shader->getUniformLocation("u_tex1");
		m_shader->setUniformSampler2D(uTex1, 0);

        // TODO: update builtin uniforms on every shader set

		// TODO: default camera?
		m_camera = std::make_shared<Camera>();
		m_camera->setPerspective(45.F, 4.F / 3.F, 1000.F, 0.1F);
    }

    Render::~Render()
    {
    }

	void Render::cursorCallback(double xpos, double ypos)
	{
		printf("Mouse: %f, %f\n", xpos, ypos);
		// TODO: process input
	}

	void Render::updateCameraUniforms()
	{
		glm::mat4 modelMatrix; // Store the model matrix       // TODO
		modelMatrix = glm::mat4(1.0f);

		glm::mat4 mvpMatrix = m_camera->getProjection() * m_camera->getModelview() * modelMatrix;

		


		bool u = m_shader->use();
		m_shader->setUniformMatrix(m_uMVP, mvpMatrix);
	}

    void Render::render()
    {
        _update_fps_counter(m_window.get());

		updateCameraUniforms();

        // TODO: rm
        static TexturePtr tex = getTextureManager().getTexture("BGLSIDE.PIX");

        if (tex)
            tex->bind();


        float ratio;
        int width, height;
        glfwGetFramebufferSize(m_window.get(), &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45., ratio, 0.01, 10000.0);

        glTranslatef(0.F, 0.F, -3.F);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.5f, 0.5f);*/


        /*glBegin(GL_TRIANGLE_STRIP);

        glTexCoord2f(0.F, 0.F);
        glVertex3f(-0.5f, -0.5f, 0.f);

        glTexCoord2f(0.F, 1.F);
        glVertex3f(-0.5f, 0.5f, 0.f);

        glTexCoord2f(1.F, 0.F);
        glVertex3f(0.5f, -0.5f, 0.f);

        glTexCoord2f(1.F, 1.F);
        glVertex3f(0.5f, 0.5f, 0.f);

        glEnd();*/        

        if (m_rootNode)
        {
			m_rootNode->render();
        }

        //mdl->render();

    }

    bool Render::tick(float fTimeDelta)
    {
        if (glfwWindowShouldClose(m_window.get()))
            return false;
        
        /* TODO Render here */
        render();

        glfwSwapBuffers(m_window.get());
        glfwPollEvents();

        return true;
    }

    TextureManager& Render::getTextureManager()
    {
        return m_texManager;
    }

	void Render::setRootNode(RenderNodePtr& node)
	{
		m_rootNode = node;
	}

	RenderNodePtr Render::getRootNode() const
	{
		return m_rootNode;
	}
}