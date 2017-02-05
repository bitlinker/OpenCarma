#pragma once
#include <Common.h>

namespace OpenCarma
{
	namespace BRender
	{
        class BR_API Model
		{
        public:
            class BR_API Vertex3f
            {
            public:
                float mValue[3];
            };

            class BR_API Vertex2f
            {
            public:
                float mValue[2];
            };

            class BR_API Face
            {
            public:
                uint16_t mV[3];
                uint8_t mUnknown[3]; // TODO: Normal???
            };

		public:
            Model()
                : mName()
                , mVertices()
                , mUv()
                , mFaces()
                , mMaterials()
                , mFaceMats()
            {
            }

            void setName(const std::string& name) { mName = name; }
            const std::string& getName() const { return mName; }

            std::vector<Vertex3f>& getVertices() { return mVertices; }
            std::vector<Vertex2f>& getUVs() { return mUv; }
            std::vector<Face>& getFaces() { return mFaces; }
            std::vector<std::string>& getMaterials() { return mMaterials; }
            std::vector<uint16_t>& getFaceMats() { return mFaceMats; }

        private:
            //uint16_t mUnkonwn; // TODO: rm?? check
            std::string mName;
            std::vector<Vertex3f> mVertices;
            std::vector<Vertex2f> mUv;
            std::vector<Face> mFaces;
            std::vector<std::string> mMaterials;
            std::vector<uint16_t> mFaceMats; // 1-based
		};

        typedef std::shared_ptr<Model> ModelPtr;
	}
}
