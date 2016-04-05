#include "main.hpp"

using namespace std;

using namespace DEM;
using namespace DEM::Core;
using namespace DEM::Collections;
using namespace DEM::Math;
using namespace DEM::System;

class Rotator : public DEM::Core::Component
{
	public:
		Rotator()
			: DEM::Core::Component()
		{
		}

		void Start()
		{
			getParent()->transform->setScale(DEM::Math::Vector3(0.3f, 0.3f, 0.3f));
		}

		void Update()
		{
			getParent()->transform->Rotate(DEM::Math::Vector3(0.0f, 1.0f, 0.0f), 0.005f);
		}
};

int main(int argc, char** argv)
{
	ProjectSettings *settings = new ProjectSettings;
	DeusExMachina *app = DeusExMachina::Instance(settings);

	(*app)([](DeusExMachina *app){
		Renderer *renderer = app->getRenderer();
		Scene *scene = renderer->getScene();

		Mesh *m = new Mesh(new Geometry(), new Material(), "Test");
		m->addComponent(new Rotator());
		scene->add(m);
	});

	DeusExMachina::Destroy();
	delete settings;
	
#if defined(DEM_DEBUG) && DEM_DEBUG == 1
	system("pause");
#endif
	return 0;
}