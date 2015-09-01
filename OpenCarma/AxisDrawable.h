#pragma once
#include "RenderNode.h"

namespace OpenCarma
{
	class AxisDrawable : public RenderNode
	{
	public:
		AxisDrawable();
		virtual ~AxisDrawable();

	protected:
		virtual void doRender(const glm::mat4& matrix);
	};
}
