#include "RenderNode.h"

namespace OpenCarma
{
    RenderNode::RenderNode()
        : m_translation()
        , m_children()
        , m_parent()
        , m_name()
        , m_isVisible(true)
    {
    }

	RenderNode::RenderNode(const std::string& name)
		: m_translation()
		, m_children()
		, m_parent()
		, m_name(name)
		, m_isVisible(true)
	{
	}	

    void RenderNode::render(const glm::mat4& matrix)
    {
        if (m_isVisible)
        {
            // TODO: identity matrix optimization
            glm::mat4& nodeMatrix = matrix * m_translation;

            doRender(nodeMatrix);
            for (auto child : m_children)
            {
                child->render(nodeMatrix);
            }
        }
    }

    bool RenderNode::attachChild(RenderNodePtr& child)
    {
        if (child)
        {
            m_children.push_back(child);
            child->setParent(shared_from_this());
            return true;
        }

        return false;
    }

    bool RenderNode::removeChild(RenderNodePtr& child)
    {
        auto it = m_children.begin();
        auto itEnd = m_children.end();
        while (it != itEnd)
        {
            if (*it == child)
            {
                child->setParent(RenderNodeWeakPtr(shared_from_this()));
                m_children.erase(it);
                return true;
            }
        }

        return false;        
    }

    void RenderNode::removeAllChildren()
    {
        for (auto child : m_children)
        {
            child->setParent(RenderNodeWeakPtr());
        }
        m_children.clear();
    }

    const RenderNodeWeakPtr RenderNode::getParent() const
    {
        return m_parent;
    }

    void RenderNode::setParent(const RenderNodeWeakPtr& parent)
    {
        m_parent = parent;
    }
}