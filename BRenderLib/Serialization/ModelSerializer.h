#pragma once
#include <Common.h>
#include <Objects/Model.h>
#include <Streams/IOStream.h>
#include <Serialization/ChunkReader.h>
#include <functional>

namespace OpenCarma
{
    namespace BRender
    {
        class BR_API ModelSerializer : protected ChunkReader
        {
        public:
            typedef std::function<void(const ModelPtr&)> TReadCallback;
            typedef std::function<const ModelPtr()> TWriteCallback; // Return null to finish

        public:
            ModelSerializer();
            virtual ~ModelSerializer() {};

            void read(const Commons::IOStreamPtr& stream, TReadCallback callback);
            void write(const Commons::IOStreamPtr& stream, TWriteCallback callback);

        protected:
            virtual bool onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader);

        private:
            void checkCurModel();

        private:
            ModelPtr mCurModel;
            TReadCallback mReadCallback;
        };
    }
}
