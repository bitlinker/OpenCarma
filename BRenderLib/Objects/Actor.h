#pragma once
#include <Common.h>

namespace OpenCarma
{
    namespace BRender
    {
        class Actor;
        typedef std::shared_ptr<Actor> ActorPtr;
        typedef std::weak_ptr<Actor> ActorWeakPtr;

        class BR_API Actor
        {
        public:
            enum {
                BR_ACTOR_NONE,
                BR_ACTOR_MODEL,
                BR_ACTOR_LIGHT,
                BR_ACTOR_CAMERA,
                _BR_ACTOR_RESERVED,
                BR_ACTOR_BOUNDS,
                BR_ACTOR_BOUNDS_CORRECT,
                BR_ACTOR_CLIP_PLANE,
                BR_ACTOR_MAX
            };

            enum {
                BR_RSTYLE_DEFAULT,
                BR_RSTYLE_NONE,
                BR_RSTYLE_POINTS,
                BR_RSTYLE_EDGES,
                BR_RSTYLE_FACES,
                BR_RSTYLE_BOUNDING_POINTS,
                BR_RSTYLE_BOUNDING_EDGES,
                BR_RSTYLE_BOUNDING_FACES,
                BR_RSTYLE_MAX
            };
        public:
            Actor()
                : mFlags(0)
                , mName()
                , mTransform()
                , mModel()
                , mMaterial()
                , mBbox()
                , mParent()
                , mChildren()
            {
            }

            void setFlags(uint16_t flags) { mFlags = flags; }
            uint16_t getFlags() const { return mFlags; }

            void setName(const std::string& name) { mName = name; }
            const std::string& getName() const { return mName; }

            void setTransform(const Matrix34& matrix) { mTransform = matrix; }
            const Matrix34 getTransform() { return mTransform; }
            
            void setModel(const std::string& model) { mModel = model; }
            const std::string& getModel() const { return mModel; }

            void setMaterial(const std::string& material) { mMaterial = material; }
            const std::string& getMaterial() const { return mMaterial; }

            void setBbox(const BBox& box) { mBbox = box; }
            const BBox& getBbox() const { return mBbox; }

            void setParent(const ActorWeakPtr& parent) { mParent = parent; }
            const ActorWeakPtr& getParent() const { return mParent; }
            
            void clearChildren() { mChildren.clear(); }
            void addChild(const ActorPtr& child) { mChildren.push_back(child); }
            const std::vector<ActorPtr>& getChildren() const { return mChildren; }

        private:
            uint16_t mFlags;
            std::string mName;
            Matrix34 mTransform;
            std::string mModel;
            std::string mMaterial;           
            BBox mBbox;
            ActorWeakPtr mParent;
            std::vector<ActorPtr> mChildren;
        };
    }
}