#pragma once
#include <Render/Texture.h>
#include <map>

namespace OpenCarma
{
	namespace Render
	{
		class TextureManager // TODO: really common?
		{
		public:
			TextureManager();
			~TextureManager();

			Commons::Render::TexturePtr getTexture(const std::string& name);

		private:
			typedef std::map<std::string, Commons::Render::TextureWeakPtr> TTexturesMap;
			TTexturesMap m_textures;
		};
	}
}