#pragma once

#include <Common.h>
#include <Objects/Actor.h>
#include <Streams/IOStream.h>
#include <Serialization/ChunkReader.h>
#include <functional>
#include <stack>

namespace OpenCarma
{
    namespace BRender
    {
		class ChunkWriter;

        class BR_API ActorSerializer : protected ChunkReader
        {
        public:
            typedef std::function<void(const ActorPtr&)> TReadCallback;
            typedef std::function<const ActorPtr()> TWriteCallback; // Return null to finish

        public:
            ActorSerializer();
            virtual ~ActorSerializer() {};

            void read(const Commons::IOStreamPtr& stream, TReadCallback callback);
            void write(const Commons::IOStreamPtr& stream, TWriteCallback callback);

        protected:
            virtual bool onChunkRead(const ChunkHeader& header, Commons::StreamReader& reader);

		private:
			void checkCurActor();
			void writeActor(ChunkWriter& writer, const ActorPtr actor);

        private:
			std::vector<ActorPtr> mActorRoots;
			std::stack<ActorPtr> mActorsStack;
            ActorPtr mCurActor;
            TReadCallback mReadCallback;
        };
    }
}
