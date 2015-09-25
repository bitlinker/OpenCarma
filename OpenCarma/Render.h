#pragma once

#include <memory>
#include <RenderCommon.h>
#include <TextureManager.h>
#include <RenderNode.h>
#include <Camera.h>
#include <Shader.h>
#include <ShaderProgram.h>

namespace OpenCarma
{
    class Render
    {
    public:
        Render();
        ~Render();

        bool tick(float fTimeDelta);
        void render();

        void setRootNode(RenderNodePtr& node);
        RenderNodePtr getRootNode() const;

		void setCamera(const CameraPtr& camera) { m_camera = camera; }
		CameraPtr getCamera() const { return m_camera; }

        // TODO: replace
        TextureManager& getTextureManager();

	private:
		void updateCameraUniforms();
		void cursorCallback(double xpos, double ypos);
		static void CursorCallbackStatic(GLFWwindow* window, double xpos, double ypos);

    private:
        std::shared_ptr<GLFWwindow> m_window;
        TextureManager m_texManager;
		RenderNodePtr m_rootNode;
		CameraPtr m_camera;


		// TODO: custom for every mesh
		ShaderProgramPtr m_shader;
		uint32_t m_uMVP;
    };
}