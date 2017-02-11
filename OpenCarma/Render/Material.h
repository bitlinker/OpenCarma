#pragma once
#include <Render/RenderCommon.h>
#include <Render/Context.h>

namespace OpenCarma
{
	namespace Render
	{
		class Material
		{
		public:
			Material();
			~Material();


		private:
			//Commons::Render::ShaderProgramPtr m_shader;
			//std::vector<Commons::Render::TexturePtr> m_textures;
		};

		typedef std::shared_ptr<Material> MaterialPtr;
	}
}