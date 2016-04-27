#include "main.hpp"

using namespace std;

using namespace DEM;
using namespace DEM::Core;
using namespace DEM::Collections;
using namespace DEM::Math;
using namespace DEM::System;
using namespace DEM::AI;

class ArcBallControl : public Actor
{
	public:
		PerspectiveCamera *camera;
		float width, height;
		float oldX, oldY, deltaX, deltaY;
		Vector2 position;

		ArcBallControl(PerspectiveCamera *camera, float width, float height)
			: Actor()
		{
			this->camera = camera;
			this->width = width;
			this->height = height;
			this->oldX = 0.0f;
			this->oldY = 0.0f;
			this->deltaX = 0.0f;
			this->deltaY = 0.0f;
		}

		void Render() {}

		void Update()
		{
			if (std::rand() % 100 < 3)
			{
				position.set(static_cast<float>(std::rand() % 100) / 100.0f, static_cast<float>(std::rand() % 100) / 100.0f);
			}

			float x = -1.0f + 2.0f * (position.x / width);
			float y = -1.0f + 2.0f * (position.y / height);
			deltaX = x - oldX;
			deltaY = y - oldY;
			oldX = x;
			oldY = y;

			if (deltaX < 0.0f)
			{
				camera->target.x += 0.1f;
			}
			else
			{
				camera->target.x -= 0.1f;
			}

			if (deltaY < 0.0f)
			{
				camera->target.y += 0.1f;
			}
			else
			{
				camera->target.y -= 0.1f;
			}
		}

	private:
};

int main(int argc, char** argv)
{
	DeusExMachina *app = DeusExMachina::Instance(new ProjectSettings());
	
	(*app)([](DeusExMachina *app){
		Profiler::Begin();

		Renderer*				renderer	= app->getRenderer();
		Scene*					scene		= renderer->getScene();
		PerspectiveCamera*		camera		= static_cast<PerspectiveCamera*>(renderer->getCamera());

		renderer->loadSkybox("Assets/skyboxes/skybox/left.jpg", "Assets/skyboxes/skybox/right.jpg", "Assets/skyboxes/skybox/top.jpg", "Assets/skyboxes/skybox/bottom.jpg",
			"Assets/skyboxes/skybox/front.jpg", "Assets/skyboxes/skybox/back.jpg");

		scene->add("Assets/scenes/sceneTest.ini");

		scene->add(new ArcBallControl(camera, app->settings()->width, app->settings()->height));

		cout << "Resources loaded in " << Profiler::End() << "s" << endl;
	});

	DeusExMachina::Destroy();
	return 0;
}