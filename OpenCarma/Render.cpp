#include <Render.h>
#include <Exception/Exception.h>
#include <Logger/Log.h>

// TODO: rm
#include <StaticModel.h>
#include <Serialization/ModelSerializer.h>
#include <fstream>

namespace Commons
{
	namespace Render
	{
		// TODO: rm
		//StaticModelPtr mdl;

		//// TODO
		//void _update_fps_counter(GLFWwindow* window) {
		//	static double previous_seconds = glfwGetTime();
		//	static int frame_count;
		//	double current_seconds = glfwGetTime();
		//	double elapsed_seconds = current_seconds - previous_seconds;
		//	if (elapsed_seconds > 0.25) {
		//		previous_seconds = current_seconds;
		//		double fps = (double)frame_count / elapsed_seconds;
		//		char tmp[128];
		//		sprintf(tmp, "opengl @ fps: %.2f", fps);
		//		glfwSetWindowTitle(window, tmp);
		//		frame_count = 0;
		//	}
		//	frame_count++;
		//}

		//void Render::CursorCallbackStatic(GLFWwindow* window, double xpos, double ypos)
		//{
		//	Render* render = reinterpret_cast<Render*>(glfwGetWindowUserPointer(window));
		//	if (render)
		//	{
		//		render->cursorCallback(xpos, ypos);
		//	}
		//}

		Render::Render()
			: m_texMgr()
			, m_mdlMgr()
			, m_mtlMgr()
		{
			// Alpha blending
			/*glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

			// Alpha test
			::glEnable(GL_ALPHA_TEST);
			::glAlphaFunc(GL_GREATER, 0.5F);

			::glEnable(GL_DEPTH_TEST);
			::glEnable(GL_CULL_FACE);

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
		}

		Render::~Render()
		{
		}

		void Render::updateCameraUniforms(const CameraPtr& camera)
		{
			glm::mat4 modelMatrix; // Store the model matrix       // TODO
			modelMatrix = glm::mat4(1.0f);

			glm::mat4 mvpMatrix = camera->getProjection() * camera->getModelview() * modelMatrix;


			bool u = m_shader->use();
			m_shader->setUniformMatrix(m_uMVP, mvpMatrix);
		}

		// TODO: clear func, state funcs

		void Render::render(const CameraPtr& camera, const RenderNodePtr& rootNode, const RenderWindow& window)
		{
			//_update_fps_counter(m_window.get());

			updateCameraUniforms(camera);

			// TODO: rm
			static TexturePtr tex = getTextureManager().getTexture("BGLSIDE.PIX");

			if (tex)
				tex->bind();


			// TODO: viewport from framebuffer, cache
			float ratio;
			uint32_t width, height;
			window.getFramebufferSize(width, height);
			ratio = width / (float)height;
			::glViewport(0, 0, width, height);
			::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// TODO: use culling here?
			glm::mat4 camMatrix = camera->getProjection() * camera->getModelview();
			rootNode->render(camMatrix);
		}
	}
}