
#include "core.h"
#include "game_scene.h"

int main(int argc, char** argv)
{	
	GameScene gameScene;
	Core core;

	core.attachComponent(&gameScene);

	core.initialize();
	core.startup();
	core.loadContent();

	core.reset();

	core.run();

	core.unloadContent();
	core.shutdown();
	core.cleanup();

	return 0;
}
