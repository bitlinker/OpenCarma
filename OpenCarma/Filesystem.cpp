#include <Filesystem.h>

#include <windows.h>

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

	// TODO: fs utils class; commons
	bool Filesystem::EnumerateFiles(const std::string path, bool isRecursive, std::vector<std::string>& files)
	{
		WIN32_FIND_DATAA findFileData;
		HANDLE hFind = ::FindFirstFileA((path + "\\*").c_str(), &findFileData);
		if (hFind == INVALID_HANDLE_VALUE) { return false; }
		do 
		{
			std::string curName(findFileData.cFileName);
			std::string fullPath = path + "\\" + std::string(findFileData.cFileName);
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (!isRecursive) continue;
				if (curName == "." || curName == "..") continue;

				if (!EnumerateFiles(fullPath, isRecursive, files))
				{
					::FindClose(hFind);
					return false;
				}
			}
			else
			{
				files.push_back(fullPath);
			}
		} while (::FindNextFileA(hFind, &findFileData));
		::FindClose(hFind);

		return true;
	}

    Filesystem::Filesystem(const std::string& carmaPath)
        : mCarmaPath(carmaPath)
        , mPaths()
    {
        // TODO
        bool isHighres = true;

		// Full path workaround
		mPaths.push_back(carmaPath);

		// TODO: rm reg!
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