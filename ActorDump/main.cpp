#include <iostream>
#include <Streams/FileStream.h>
#include <Serialization/ActorSerializer.h>
#include <Exception/Exception.h>

using namespace Commons;
using namespace OpenCarma::BRender;

void dumpActor(const ActorPtr& actor, uint32_t level)
{
	for (uint32_t i = 0; i < level; ++i) std::cout << "  ";
	std::cout <<
		"Actor: " << actor->getName() <<
		", model: " << actor->getModel() <<
		", mat: " << actor->getMaterial() <<
		", flags: " << actor->getFlags() <<
		", BBox: " << actor->getBbox().empty() <<
		", HStart: " << actor->getHierarchyStartFlag() <<
		", Unk.flag: " << actor->getUnknownFlag() <<
		std::endl;

	const auto children = actor->getChildren();
	for (auto it = children.begin(); it != children.end(); ++it)
		dumpActor(*it, level + 1);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: ActorDump [actor_file]" << std::endl;
		return -1;
	}

	std::string actorPath(argv[1]);
	try
	{
		ActorSerializer actorSerializer;
		IOStreamPtr strm_act(new FileStream(actorPath, FileStream::MODE_READ));
		ActorPtr actor = actorSerializer.read(strm_act);
		dumpActor(actor, 0);
	}
	catch (const SerializationException se)
	{
		std::cout << "Serialization exception: " << se.what() << std::endl;
		return -2;
	}
	catch (const IOException& ioe)
	{
		std::cout << "IO Exception: " << ioe.what() << std::endl;
		return -1;
	}
	return 0;
}