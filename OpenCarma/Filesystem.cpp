#include <Filesystem.h>

using namespace Commons;

namespace OpenCarma
{
    static bool IsFileExists(const std::string& fileName)
    {
        FILE *f = ::fopen(fileName.c_str(), "rb");
        if (f) {
            ::fclose(f);
            return true;
        }
        return false;
    }

    Filesystem::Filesystem(const std::string& carmaPath)
        : mCarmaPath(carmaPath)
        , mPaths()
    {
        // TODO
        bool isHighres = true;

        mPaths.push_back(carmaPath + "/DATA/REG/SHADETAB");
        mPaths.push_back(carmaPath + "/DATA/SHADETAB");

        mPaths.push_back(carmaPath + "/DATA/ACTORS");

        mPaths.push_back(carmaPath + "/DATA/REG/PIXELMAP");
        mPaths.push_back(carmaPath + "/DATA/PIXELMAP");

        if (isHighres)
            mPaths.push_back(carmaPath + "/DATA/64x48x8/PIXELMAP");
        else
            mPaths.push_back(carmaPath + "/DATA/32x20x8/PIXELMAP");

        mPaths.push_back(carmaPath + "/DATA/REG/MATERIAL");
        mPaths.push_back(carmaPath + "/DATA/MATERIAL");

        mPaths.push_back(carmaPath + "/DATA/REG/MODELS");
        mPaths.push_back(carmaPath + "/DATA/MODELS");
    }

    IOStreamPtr Filesystem::openResource(const std::string& name)
    {
        // TODO: exclude reg; typed resources
        // Try all folders in order of priority
        auto it = mPaths.begin();
        const auto itEnd = mPaths.end();
        while (it != itEnd)
        {
            std::string filepath = *it + "/" + name;
            if (IsFileExists(filepath))
            {
                return std::make_shared<FileStream>(filepath, FileStream::MODE_READ);
            }
            ++it;
        }
        // not found...
        return nullptr;
    }    
}