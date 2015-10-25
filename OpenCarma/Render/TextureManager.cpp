#include <TextureManager.h>
#include <cassert>

namespace OpenCarma
{
	namespace Render
	{
		TextureManager::TextureManager()
			: m_textures()
		{
		}

		TextureManager::~TextureManager()
		{
		}

		Commons::Render::TexturePtr TextureManager::getTexture(const std::string& name)
		{
			Commons::Render::TexturePtr result;
			TTexturesMap::const_iterator it = m_textures.find(name);
			if (it != m_textures.end())
			{
				result = it->second.lock();
			}

			if (result == nullptr)
			{
				result = Commons::Render::TexturePtr(new Commons::Render::Texture());
				// TODO: load it
			}

			return result;
		}
	}
}