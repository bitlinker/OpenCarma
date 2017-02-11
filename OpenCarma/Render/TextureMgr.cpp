#include <TextureMgr.h>

using namespace Commons::Render;

namespace OpenCarma
{
    namespace Render
    {
		class PixmapPack
		{
		public:
			// TODO
		private:
			std::map<std::string, Texture2dPtr> mTextures;
		};

		TextureMgr::TextureMgr(Context* context)
			: mContext(context)
		{
			// TODO: load palettes
		}

        // TODO: with palette?
        // TODO: throw or bool?
        void TextureMgr::registerPixelmapPack(const std::string& packName)
        {
            // TODO
        }

        void TextureMgr::unregisterPixelmapPack(const std::string& packName)
        {
            // TODO
        }

		Texture2dPtr TextureMgr::getTexture(const std::string& name)
		{
			Texture2dPtr texture(new Texture2d(mContext));
			//ScopeBind bind(texture);

			//texture->setData();

			return nullptr;
		}
    }
}
