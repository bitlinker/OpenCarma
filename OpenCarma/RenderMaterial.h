#pragma once
#include <Render/RenderCommon.h>
#include <Render/ShaderProgram.h>
#include <Render/Texture.h>
#include <Objects/Material.h>
#include <Render.h>

namespace OpenCarma
{
	namespace Render
	{
		// TODO: namespace Render?
		class RenderMaterial
		{
		public:
			RenderMaterial(const BRender::MaterialPtr& material, Commons::Render::Render& render);
			~RenderMaterial();

			void set();
			// TODO: store shader, shader state(uniform values), textures

		private:
			Commons::Render::ShaderProgramPtr m_shader;
			std::vector<Commons::Render::TexturePtr> m_textures;
		};

		typedef std::shared_ptr<RenderMaterial> RenderMaterialPtr;
	}
}