#include "main.hpp"

using namespace std;

using namespace DEM;
using namespace DEM::Core;
using namespace DEM::Collections;
using namespace DEM::Math;
using namespace DEM::System;

int main(int argc, char** argv)
{
	ProjectSettings *settings = new ProjectSettings;
	DeusExMachina *app = DeusExMachina::Instance(settings);

	Renderer *renderer = app->getRenderer();
	Scene *scene = renderer->getScene();

	Mesh *m = new Mesh("Jamal");
	scene->add(m);
	Mesh *n = new Mesh("Ordos");
	m->addChild(n);

	(*app)();

	DeusExMachina::Destroy();
	delete settings;
	
#if defined(DEM_DEBUG) && DEM_DEBUG == 1
	system("pause");
#endif
	return 0;
}