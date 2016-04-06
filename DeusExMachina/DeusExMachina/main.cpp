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
		PerspectiveCamera *camera = static_cast<PerspectiveCamera*>(renderer->getCamera());

		camera->eye.z = 10.0f;

		Geometry *geo = new Geometry({
			new Vertex(Vector3(-1.0f, 1.0f, 0.0f)),
			new Vertex(Vector3(-1.0f, -1.0f, 0.0f)),
			new Vertex(Vector3(1.0f, 1.0f, 0.0f)),
			new Vertex(Vector3(1.0f, -1.0f, 0.0f))
		}, { 0, 1, 2, 3 });
		Material *mat = new PhongMaterial(Color(1.0f, 1.0f, 0.0f, 1.0f), Color(0.0f, 1.0f, 0.0f, 1.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 50.0f);
		mat->baseColor.set(0.0f, 1.0f, 0.0f, 1.0f);
		Mesh *m = new Mesh(geo, mat, "Test");
		m->drawStyle = GL_TRIANGLE_STRIP;
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