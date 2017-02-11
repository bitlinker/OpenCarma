#include <iostream>

#include <Render/RenderWindow.h>
#include <Render/Initializer.h>
#include <Logger/Log.h>
#include <Exception/Exception.h>
//#include <AxisDrawable.h>
//#include <FreeFlyCameraController.h>
//#include <TextReader.h>
//#include <OpponentTxt.h>

#include <TextureMgr.h>
#include <MaterialMgr.h>
#include <ModelMgr.h>
#include <ActorMgr.h>
//#include <StaticModel.h>

//#include <Serialization/ModelSerializer.h>
//#include <Serialization/PixmapSerializer.h>
//#include <Serialization/MaterialSerializer.h>
//#include <Serialization/ActorSerializer.h>
#include <Exception/Exception.h>

using namespace Commons;
using namespace Commons::Render;

int main(int argc, char **argv)
{
	using namespace Commons;
    using namespace OpenCarma;
    using namespace OpenCarma::Render;

    try
    {
		LOG_INFO("Initializing Carma");
		std::string carmaPath;
		if (argc > 1)
		{
			carmaPath = argv[1];
		}
		
		WindowParams params;
		params.width = 1024;
		params.height = 768;
		params.title = "Carma";
        params.isFullscreen = false;
        params.contextMajor = 2;
        params.contextMinor = 0;

        ScopedInitializer init;
		RenderWindow window(params);


		Context* context = window.getContextPtr();
		TextureMgr textureMgr(context);
		//textureMgr.registerPixelmapPack();
		
		MaterialMgr materialMgr(context);
		ModelMgr modelMgr(context);
		ActorMgr actorMgr(context);

		RenderNodePtr rootNode(new RenderNode("root"));
		RenderNodePtr track = actorMgr.inflateActorTree("citya1");
		rootNode->attachChild(track);

		CameraPtr camera = Camera::MakePerspectiveCamera(55.F, 4.F / 3.F, 1000.F, 0.01F);

		window.getFramebuffer();
		//Render render;
		// TODO:
		//render(node, camera, framebuffer);

        //// Texture loader
        //CarmaTextureLoaderPtr carmaLoader(new TextureMgr());
        //Commons::Render::SharedTextureMgr textureMgr(&context);
        //textureMgr.addLoader(carmaLoader);
        //carmaLoader->registerPixelmapPack(carmaPath + "/DATA/PIXELMAP/EAGREDL8.PIX");       
        //Commons::Render::SharedTexturePtr tex = textureMgr.getTexture("test");
        //// TODO: flics also here
        //
		//OpenCarma::Render::Render carmaRender; // TODO: single

  //      Commons::Render::RenderNodePtr axis = std::make_shared<OpenCarma::Render::AxisDrawable>();
  //      axis->setVisible(true);
  //      rootNode->attachChild(axis);


		//Commons::Render::CameraPtr camera = std::make_shared<Commons::Render::Camera>();
		//// TODO: constructor?
		//camera->setPerspective(55.F, 4.F / 3.F, 1000.F, 0.01F);
		//OpenCarma::Render::FreeFlyCameraController controller(camera);
  //      //render.getTextureManager().load(pixelmaps, palettes[0]);
		//	
		//double oldTime = window.getCurTime();
		//bool isClosed = false;
		while (window.tick())
		{
		//	double curTime = window.getCurTime();
		//	float delta = static_cast<float>(curTime - oldTime);
		//	oldTime = curTime;

		//	controller.update(delta);
		//	context.render(camera, rootNode, window);
			window.swapBuffers();
		}
  //      
        std::cout << "Carma finished" << std::endl;
        return 0;
    }
    catch (const Exception& e)
    {
        std::cout << "Exception occurred: " << e.what() << std::endl;
		return -1;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Exception occurred: " << e.what() << std::endl;
        return -1;
    }
}