#pragma once
#include <Render/RenderCommon.h>
#include <Render/Context.h>
#include <Render/Texture2d.h>
#include <Objects/Material.h>

namespace OpenCarma
{
	namespace Render
	{
		class Material
		{
		public:
			Material(const OpenCarma::BRender::MaterialPtr& mat);
			~Material();

            void use(Commons::Render::Context* context);

		private:

            // TODO: needed?
            OpenCarma::BRender::MaterialPtr mMaterial;

            Commons::Render::Texture2dPtr mTexture;
            bool mDoubleSided;
            uint32_t mColor;
			// TODO:
			// texture
			// color
			// tex matrix
			// render flags (double sided, force z, etc...)
		};

		typedef std::shared_ptr<Material> MaterialPtr;
	}
}