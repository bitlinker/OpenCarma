#pragma once
#include <Common.h>

namespace OpenCarma
{
	namespace BRender
	{
        /*
        * Material description is here:
        * http://rr2000.toshiba-3.com/R4/BRENDER/TEBK_43.HTM
        */
        class BR_API Material
		{
        public:
            enum Flags
            {
                BR_MATF_LIGHT = 0x00000001,
                BR_MATF_PRELIT = 0x00000002,

                BR_MATF_SMOOTH = 0x00000004,

                BR_MATF_ENVIRONMENT_I = 0x00000008,
                BR_MATF_ENVIRONMENT_L = 0x00000010,
                BR_MATF_PERSPECTIVE = 0x00000020,
                BR_MATF_DECAL = 0x00000040,

                BR_MATF_I_FROM_U = 0x00000080,
                BR_MATF_I_FROM_V = 0x00000100,
                BR_MATF_U_FROM_I = 0x00000200,
                BR_MATF_V_FROM_I = 0x00000400,

                BR_MATF_ALWAYS_VISIBLE = 0x00000800,
                BR_MATF_TWO_SIDED = 0x00001000,

                BR_MATF_FORCE_Z_0 = 0x00002000,

                BR_MATF_DITHER = 0x00004000
            };

            // TODO:
            // BR_MATF_SMOOTH == GOURAND; https://en.wikipedia.org/wiki/Gouraud_shading
            // Normals interpolation
            // either specified for each vertex or found by averaging the surface normals of the polygons that meet at each vertex
            // Or flat shading...

            // Phong model:
            // ambient + diffuse + specular * power?

		public:
            Material::Material()
                : mName()
                , mColor()
                , mAmbient(0.F)
                , mDiffuse(0.F)
                , mSpecular(0.F)
                , mSpecularPower(0.F)
                , mFlags(BR_MATF_SMOOTH | BR_MATF_LIGHT)
                , mIndexBase(0)
                , mIndexRange(0)
                , mShadetab()
                , mPixelmap()
                , mTransform()
            {
            }

            const std::string& getName() const { return mName; }
            void setName(const std::string& name) { mName = name; }

            const std::string& getPixmap() const { return mPixelmap; }
            void setPixmap(const std::string& name) { mPixelmap = name; }

            const std::string& getShadetab() const { return mShadetab; }
            void setShadetab(const std::string& name) { mShadetab = name; }

            uint32_t getFlags() const { return mFlags; }
            void setFlags(uint32_t value) { mFlags = value; }

            void setColor(const Color& color) { mColor = color; }
            const Color& getColor() const { return mColor; }

            void setIndexedColor(uint8_t base, uint8_t range) { mIndexBase = base; mIndexRange = range; }
            uint8_t getIndexedBase() const { return mIndexBase; }
            uint8_t getIndexedRange() const { return mIndexRange; }

            void setPhong(float ambient, float diffuse, float specular, float specularPower)
            {
                mAmbient = ambient;
                mDiffuse = diffuse;
                mSpecular = specular;
                mSpecularPower = specularPower;
            }
            void setAmbient(float ambient) { mAmbient = ambient; }
            void setDiffuse(float diffuse) { mDiffuse = diffuse; }
            void setSpecular(float specular) { mSpecular = specular; }
            void setSpecularPower(float power) { mSpecularPower = power; }
            float getAmbient() const { return mAmbient; }
            float getDiffuse() const { return mDiffuse; }
            float getSpecular() const { return mSpecular; }
            float getSpecularPower() const { return mSpecularPower; }

            const Matrix23& getTransform() const { return mTransform; }
            void setTransform(const Matrix23& transform) { mTransform = transform; }
            
        public:
            std::string mName;
            Color mColor;
            float mAmbient;
            float mDiffuse;
            float mSpecular;
            float mSpecularPower;
            uint32_t mFlags;
            uint8_t mIndexBase;
            uint8_t mIndexRange;
            std::string mShadetab;
            std::string mPixelmap;
            Matrix23 mTransform;
		};

        typedef std::shared_ptr<Material> MaterialPtr;
	}
}
