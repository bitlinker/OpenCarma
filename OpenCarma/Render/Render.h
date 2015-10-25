#pragma once

#include <memory>
#include <Render/RenderCommon.h>
#include <Render/RenderNode.h>
#include <Render/Camera.h>
#include <Render/Shader.h>
#include <Render/ShaderProgram.h>
#include <Render/Texture.h>
#include <Render/RenderWindow.h>

#include <Render/StaticModel.h>

// Carma-specific stuff:
#include <TextureManager.h>

#include <PlainShaderProgram.h>

namespace OpenCarma
{
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
			//void render(const CameraPtr& camera, const RenderNodePtr& rootNode, const RenderWindow& window);
			void render();

			// TODO: create all GL-related resources here...
			// Use some loader as parameter
			Commons::Render::TexturePtr createTexture();
			Commons::Render::ShaderPtr createShader();
			Commons::Render::ShaderProgramPtr createShaderProgram();

			StaticModelPtr createStaticModel(const std::string& filename);
			Commons::Render::TexturePtr createTexture(const std::string& filename);

			// TODO: replace
			TextureManager& getTextureManager() { return m_texMgr; }
			MaterialManager& getMaterialManager() { return m_mtlMgr; }
			ModelManager& getModelManager() { return m_mdlMgr; }

			PlainShaderProgramPtr& getPlainShaderProgram() { return m_plainShader; }
		private:
			//void updateCameraUniforms(const Commons::Render::CameraPtr& camera);
			//void cursorCallback(double xpos, double ypos);
			//static void CursorCallbackStatic(GLFWwindow* window, double xpos, double ypos);

		private:
			// TODO: move out?
			TextureManager m_texMgr;
			ModelManager m_mdlMgr;
			MaterialManager m_mtlMgr;

			PlainShaderProgramPtr m_plainShader;
		};
	}
}