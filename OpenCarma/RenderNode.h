#pragma once
#include <Common.h>
#include <RenderCommon.h>

namespace OpenCarma
{
    class RenderNode;
    typedef std::shared_ptr<RenderNode> RenderNodePtr;
    typedef std::weak_ptr<RenderNode> RenderNodeWeakPtr;

    class RenderNode : public std::enable_shared_from_this<RenderNode>
    {
    public:
        RenderNode();
		explicit RenderNode(const std::string& name);
		virtual ~RenderNode() {};

        void render(const glm::mat4& matrix = glm::mat4(1.F));

        bool attachChild(RenderNodePtr& child);
        bool removeChild(RenderNodePtr& child);
        void removeAllChildren();
        
        const glm::mat4& getTranslation() const { return m_translation; }
        void setTranslation(const glm::mat4& translation) { m_translation = translation; }

        const std::string& getName() const { return m_name; }
        void setName(const std::string& name) { m_name = name; }

        bool isVisible() const { return m_isVisible; }
        void setVisible(bool visible) { m_isVisible = visible; }

    protected:
        virtual void doRender(const glm::mat4& matrix) {};

    private:
		const RenderNodeWeakPtr getParent() const;
        void setParent(const RenderNodeWeakPtr& parent);

    private:
        glm::mat4 m_translation;
        std::list<RenderNodePtr> m_children;
		RenderNodeWeakPtr m_parent;
        std::string m_name;
        bool m_isVisible;
    };    
}