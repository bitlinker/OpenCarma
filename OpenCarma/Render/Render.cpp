#include <Render.h>
#include <Exception/Exception.h>
#include <Logger/Log.h>

// TODO: rm
#include <StaticModel.h>
#include <Serialization/ModelSerializer.h>
#include <fstream>

namespace OpenCarma
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
			m_plainShader = std::make_shared<PlainShaderProgram>();
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

		

			// TODO: update builtin uniforms on every shader set
		}

		Render::~Render()
		{
		}

		//void Render::updateCameraUniforms(const CameraPtr& camera)
		//{
		//	glm::mat4 modelMatrix; // Store the model matrix       // TODO
		//	modelMatrix = glm::mat4(1.0f);

		//	glm::mat4 mvpMatrix = camera->getProjection() * camera->getModelview() * modelMatrix;


		//	bool u = m_shader->use();
		//	m_shader->setUniformMatrix(m_uMVP, mvpMatrix);
		//}

		// TODO: clear func, state funcs

		void Render::render()
		{
			//_update_fps_counter(m_window.get());

			//updateCameraUniforms(camera);

			// TODO: rm
			//static TexturePtr tex = getTextureManager().getTexture("BGLSIDE.PIX");

			//if (tex)
			//	tex->bind();


			//// TODO: viewport from framebuffer, cache
			//float ratio;
			//uint32_t width, height;
			//window.getFramebufferSize(width, height);
			//ratio = width / (float)height;
			//::glViewport(0, 0, width, height);
			//::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//// TODO: use culling here?
			//glm::mat4 camMatrix = camera->getProjection() * camera->getModelview();
			//rootNode->render(camMatrix);
		}

		StaticModelPtr Render::createStaticModel(const std::string& filename)
		{
			// TODO:
			return nullptr;
		}

		Commons::Render::TexturePtr Render::createTexture(const std::string& filename)
		{
			// TODO:
			return nullptr;
		}
	}
}