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
			// TODO:
			// texture
			// color
			// tex matrix
			// render flags (double sided, force z, etc...)
		};

		typedef std::shared_ptr<Material> MaterialPtr;
	}
}