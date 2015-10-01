#include <TextureManager.h>
#include <cassert>

namespace Commons
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

		TexturePtr TextureManager::getTexture(const std::string& name)
		{
			TexturePtr result;
			TTexturesMap::const_iterator it = m_textures.find(name);
			if (it != m_textures.end())
			{
				result = it->second.lock();
			}

			if (result == nullptr)
			{
				result = TexturePtr(new Texture());
				// TODO: load it
			}

			return result;
		}
	}
}