#pragma once
#include <Render/RenderNode.h>

namespace OpenCarma
{
    namespace Render
    {
        class AxisDrawable : public Commons::Render::RenderNode
        {
        public:
            AxisDrawable();
            virtual ~AxisDrawable();

        protected:
            virtual void doRender(const glm::mat4& matrix);
        };
    }
}
