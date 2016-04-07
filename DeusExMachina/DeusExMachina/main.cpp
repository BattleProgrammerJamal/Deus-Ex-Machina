#include "main.hpp"

using namespace std;

using namespace DEM;
using namespace DEM::Core;
using namespace DEM::Collections;
using namespace DEM::Math;
using namespace DEM::System;

class Rotator : public Component
{
	public:
		Vector3 velocity;

		Rotator(Vector3 _velocity)
			: Component()
		{
			velocity = _velocity;
		}

		void Start()
		{
		}

		void Update()
		{
			float t = static_cast<Mesh*>(m_parent)->getClock()->seconds();

			m_parent->transform->Translate(Vector3(velocity.x * 0.001f * cos(4.0f * t), 0.0f, velocity.z * 0.001f * sin(4.0f * t)));
			m_parent->transform->setRotation(Quaternion(Vector3(1.0f, 0.0f, 1.0f), velocity.length() * sin(t)));
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

		Geometry *geo = new SphereGeometry(3.0f, 32, 32);
		Material *mat = new LambertMaterial(Color(1.0f, 0.0f, 0.0f, 1.0f), Color(0.0f, 1.0f, 0.0f, 1.0f));
		mat->loadTexture("Assets/textures/lava2.jpg");
		mat->baseColor.set(0.0f, 1.0f, 0.0f, 1.0f);
		Mesh *m = new Mesh(geo, mat, "Test");
		m->drawStyle = GL_TRIANGLE_STRIP;
		m->addComponent(new Rotator(Vector3(0.1f, 0.5f, 2.0f)));
		m->transform->setScale(Vector3(0.2f, 0.2f, 0.2f));
		scene->add(m);

		for (DEM_UINT i = 0; i < 100; ++i)
		{
			Mesh *m2 = new Mesh(*m);
			m2->transform->setScale(Vector3(0.3f, 0.3f, 0.3f));
			m2->addComponent(new Rotator(Vector3(4 * cos(static_cast<float>(rand() % 10)), 
				3 * -sin(static_cast<float>(rand() % 10)), 
				2 * cos(static_cast<float>(rand() % 10)))));
			scene->add(m2);
		}
	});

	DeusExMachina::Destroy();
	delete settings;
	return 0;
}