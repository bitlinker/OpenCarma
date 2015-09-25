#include <iostream>
#include <Render.h>
#include <Scene.h>
#include <StaticModel.h>
#include <Init.h>
#include <Log.h>
#include <Exception/Exception.h>
#include <AxisDrawable.h>
#include <FreeFlyCameraController.h>



#include <TextReader.h>
#include <OpponentDescription.h>

/*static bool ReadOpponentsTxt(TextReader& reader)
{
    uint32_t numOpponents = reader.readUInt32();
    for (uint32_t i = 0; i < numOpponents; ++i)
    {
        OpponentDescription descr;
        descr.read(reader);
    }

    std::string endMarker;
    reader.readLine(endMarker);

    if (endMarker != "END")
        return false;

    return true;
}*/

#include <TextFiles/SoundTxt.h>
#include <fstream>
#include <iostream>

//blkeagle.txt

int main(int argc, char **argv)
{
	std::string carmaPath;
	if (argc > 1)
	{
		carmaPath = argv[1];
	}

	std::string inFileName = carmaPath + "/DATA/SOUND/SOUND.TXT";
	std::ifstream iStrm;
	iStrm.open(inFileName, std::ios_base::in);
	if (!iStrm.is_open())
	{
		std::cout << "Can't open file for reading: " << inFileName << std::endl;
		return -1;
	}

	using namespace OpenCarma;
	TextReader reader(iStrm, TextDecoder::DT_CARMA1);

	SoundTxt soundTxt(reader);
	auto entries = soundTxt.getEntries();
	
	return 0;
}

//
//#include <Serialization/ModelSerializer.h>
//#include <Serialization/TextureSerializer.h>
//#include <Serialization/MaterialSerializer.h>
//#include <Serialization/ActorSerializer.h>
//#include <Exception.h>
//#include <fstream>
//
//int main(int argc, char **argv)
//{
//    using namespace OpenCarma;
//    using namespace OpenCarma::BRender;
//
//    try
//    {
//		LOG_INFO("Initializing Carma");
//
//		// TODO: parse arguments properly
//		std::string carmaPath;
//		if (argc > 1)
//		{
//			carmaPath = argv[1];
//		}
//		
//        Init init;
//        Render render;
//
//        // TODO Load mdl
//        std::vector<ModelPtr> models;
//        std::ifstream strm_model(carmaPath + "/DATA/MODELS/EAGBLAK.DAT", std::ifstream::binary);
//        ModelSerializer::DeserializeModels(strm_model, models);
//
//        std::vector<PixmapPtr> palettes;
//        std::ifstream strm_palette(carmaPath + "/DATA/REG/PALETTES/DRRENDER.PAL", std::ifstream::binary);
//        TextureSerializer::DeserializePixelmap(strm_palette, palettes);
//        assert(!palettes.empty());
//    
//        std::vector<PixmapPtr> pixelmaps;
//        std::ifstream strm_pixmaps(carmaPath + "/DATA/PIXELMAP/EAGREDL8.PIX", std::ifstream::binary);
//        TextureSerializer::DeserializePixelmap(strm_pixmaps, pixelmaps);
//
//        std::vector<MaterialPtr> materials;
//        std::ifstream strm_material(carmaPath + "/DATA/MATERIAL/AGENTO.MAT", std::ifstream::binary);
//        MaterialSerializer::DeserializeMaterial(strm_material, materials);
//        
//        std::vector<ActorPtr> actors;
//        std::ifstream strm_act(carmaPath + "/DATA/ACTORS/BUSTER.ACT", std::ifstream::binary);
//        ActorSerializer::DeserializeActor(strm_act, actors);
//
//        //ScenePtr scene(std::make_shared<Scene>());
//		RenderNodePtr rootNode = std::make_shared<RenderNode>("root");
//        StaticModelPtr mdl(std::make_shared<StaticModel>());
//        mdl->init(models[0], render); // TODO: constructor; not init
//
//        rootNode->attachChild(std::dynamic_pointer_cast<RenderNode>(mdl));
//		mdl->setTranslation(glm::translate(5.F, 0.F, 0.F));
//
//		RenderNodePtr axis = std::make_shared<AxisDrawable>();
//		//mdl->setVisible(false);
//		rootNode->attachChild(axis);
//
//        render.setRootNode(rootNode);
//
//
//		CameraPtr camera = std::make_shared<Camera>();
//		// TODO: constructor?
//		camera->setPerspective(55.F, 4.F / 3.F, 1000.F, 0.01F);
//		FreeFlyCameraController controller(camera);
//		render.setCamera(camera);
//        //render.getTextureManager().load(pixelmaps, palettes[0]);
//			
//		double oldTime = glfwGetTime();
//		bool isClosed = false;
//		do
//		{
//			double curTime = glfwGetTime();
//			float delta = static_cast<float>(curTime - oldTime);
//			oldTime = curTime;
//
//			controller.update(delta);
//			isClosed = !render.tick(delta);
//		} while (!isClosed);
//        
//        std::cout << "Carma finished" << std::endl;
//        return 0;
//    }
//   /* catch (const Exception& e)
//    {
//        std::cout << "Exception occurred: " << e.what() << std::endl;
//        return -1;
//    }*/
//    catch (const std::runtime_error& e)
//    {
//        std::cout << "Exception occurred: " << e.what() << std::endl;
//        return -1;
//    }
//}