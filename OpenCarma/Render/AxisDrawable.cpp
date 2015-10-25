#include <Render/RenderCommon.h>
#include <AxisDrawable.h>

namespace OpenCarma
{
    namespace Render
    {
        AxisDrawable::AxisDrawable()
        {
        }

        AxisDrawable::~AxisDrawable()
        {
        }

        void AxisDrawable::doRender(const glm::mat4& matrix)
        {
            glPushAttrib(GL_ALL_ATTRIB_BITS);
            //glDisable(GL_TEXTURE_2D);
            glDisable(GL_DEPTH_TEST);

            // TODO: legacy API
            glBegin(GL_LINES);
            {
                glColor3ub(255, 0, 0);
                glTexCoord2f(1.F, 0.F);
                glVertex3f(0.F, 0.F, 0.F);
                glVertex3f(1.F, 0.F, 0.F);

                glColor3ub(0, 255, 0);
                glTexCoord2f(0.F, 1.F);
                glVertex3f(0.F, 0.F, 0.F);
                glVertex3f(0.F, 1.F, 0.F);

                glColor3ub(0, 0, 255);
                glTexCoord2f(1.F, 1.F);
                glVertex3f(0.F, 0.F, 0.F);
                glVertex3f(0.F, 0.F, 1.F);
            }
            glEnd();

            glPopAttrib();
        }
    }
}
