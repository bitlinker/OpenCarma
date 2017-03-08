#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <Streams/FileStream.h>

namespace OpenCarma
{
    class Filesystem
    {
    public:
        Filesystem(const std::string& carmaPath);
        Commons::IOStreamPtr openResource(const std::string& name);

		static bool EnumerateFiles(const std::string path, bool isRecursive, std::vector<std::string>& files);

    private:
        std::string mCarmaPath;
        std::vector<std::string> mPaths;
    };
}