#pragma once

#include <Common.h>
#include <Objects/Material.h>
#include <Streams/IOStream.h>
#include <Serialization/ChunkReader.h>
#include <functional>

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API MaterialSerializer : protected ChunkReader
        {
        public:
            typedef std::function<void(const MaterialPtr&)> TReadCallback;
            typedef std::function<const MaterialPtr()> TWriteCallback; // Return null to finish

        public:
            MaterialSerializer();
            virtual ~MaterialSerializer() {};

            void read(const Commons::IOStreamPtr& stream, TReadCallback callback);
            void write(const Commons::IOStreamPtr& stream, TWriteCallback callback);

        protected:
            virtual bool onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader);

        private:
            void checkCurMat();

        private:
            MaterialPtr mCurMaterial;
            TReadCallback mReadCallback;
        };
    }
}
