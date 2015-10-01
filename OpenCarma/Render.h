#pragma once

#include <memory>
#include <Render/RenderCommon.h>
#include <TextureManager.h>
#include <Render/RenderNode.h>
#include <Render/Camera.h>
#include <Render/Shader.h>
#include <Render/ShaderProgram.h>
#include <Render/RenderWindow.h>

namespace Commons
{
	// TODO: divide into common & carma?
	namespace Render
	{
		// TODO
		class ModelPtr
		{
		};
		class MaterialPtr
		{
		};

		// TODO
		class ModelManager
		{
		public:
			ModelPtr getModel(const std::string name)
			{
				return ModelPtr();
			}
		};

		class MaterialManager
		{
		public:
			MaterialPtr getMaterial(const std::string name)
			{
				return MaterialPtr();
			}
		};

		class Render
		{
		public:
			Render();
			~Render();

			bool tick(float fTimeDelta);
			// TODO: and framebuffer
			void render(const CameraPtr& camera, const RenderNodePtr& rootNode, const RenderWindow& window);

			// TODO: create all GL-related resources here...
			// Use some loader as parameter
			TexturePtr createTexture();
			ShaderPtr createShader();
			ShaderProgramPtr createShaderProgram();

			// TODO: replace
			TextureManager& getTextureManager() { return m_texMgr; }
			MaterialManager& getMaterialManager() { return m_mtlMgr; }
			ModelManager& getModelManager() { return m_mdlMgr; }


		private:
			void updateCameraUniforms(const CameraPtr& camera);
			//void cursorCallback(double xpos, double ypos);
			//static void CursorCallbackStatic(GLFWwindow* window, double xpos, double ypos);

		private:
			// TODO: move out?
			TextureManager m_texMgr;
			ModelManager m_mdlMgr;
			MaterialManager m_mtlMgr;


			// TODO: custom for every mesh
			ShaderProgramPtr m_shader;
			uint32_t m_uMVP;
		};
	}
}