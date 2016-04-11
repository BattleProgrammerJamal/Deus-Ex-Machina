#include "main.hpp"

using namespace std;

using namespace DEM;
using namespace DEM::Core;
using namespace DEM::Collections;
using namespace DEM::Math;
using namespace DEM::System;

class MTAnimator : public Component
{
	public:
		MTAnimator()
			: Component()
		{
		}

		void Start(){}

		void Update()
		{
			float t = static_cast<Mesh*>(m_parent)->getClock()->seconds();
			m_parent->transform->setRotation(Quaternion(Vector3(0.0f, 1.0f, 0.0f), 2.0f * sin(t)));
		}
};

class KeyboardHandler : public KeyboardEvent
{
	void operator()(sf::Keyboard::Key key)
	{
		DeusExMachina *app = DeusExMachina::Instance();
		Renderer *renderer = app->getRenderer();
		Scene *scene = renderer->getScene();

		if (key == sf::Keyboard::Left)
		{
			Actor *m_parent = scene->get("Test");
			if (typeid(*m_parent) == typeid(Mesh))
			{
				Mesh *parentMesh = static_cast<Mesh*>(m_parent);
				if (typeid(*parentMesh->getGeometry()) == typeid(MorphTargetGeometry))
				{
					MorphTargetGeometry *mtGeometry = static_cast<MorphTargetGeometry*>(parentMesh->getGeometry());
					vector<MorphTarget*> morphTargets = mtGeometry->getMorphTargets();

					morphTargets.at(0)->weight -= 0.05f;
					if (morphTargets.at(0)->weight < 0.0f) { morphTargets.at(0)->weight = 0.0f; }
				}
			}
		}

		if (key == sf::Keyboard::Right)
		{
			Actor *m_parent = scene->get("Test");
			if (typeid(*m_parent) == typeid(Mesh))
			{
				Mesh *parentMesh = static_cast<Mesh*>(m_parent);
				if (typeid(*parentMesh->getGeometry()) == typeid(MorphTargetGeometry))
				{
					MorphTargetGeometry *mtGeometry = static_cast<MorphTargetGeometry*>(parentMesh->getGeometry());
					vector<MorphTarget*> morphTargets = mtGeometry->getMorphTargets();

					morphTargets.at(0)->weight += 0.05f;
					if (morphTargets.at(0)->weight > 1.0f) { morphTargets.at(0)->weight = 1.0f; }
				}
			}
		}
	}
};

void TW_CALL AngerPoseChoice(void *data)
{

}

int main(int argc, char** argv)
{
	ProjectSettings *settings = new ProjectSettings;
	DeusExMachina *app = DeusExMachina::Instance(settings);

	(*app)([](DeusExMachina *app){
		Renderer *renderer = app->getRenderer();
		Scene *scene = renderer->getScene();
		PerspectiveCamera *camera = static_cast<PerspectiveCamera*>(renderer->getCamera());

		app->addKeyboardEventListener(new KeyboardHandler());

		camera->target.y = 5.0f;
		camera->eye.y = 4.0f;
		camera->eye.z = 8.0f;

		DirectionalLight *dLight = new DirectionalLight(Vector3(), Vector3(0.0f, 0.0f, 1.0f));
		dLight->color.set(1.0f, 1.0f, 0.0f, 1.0f);
		dLight->intensity = 0.5f;
		scene->add(dLight);

		Model *neutralPoseModel = new Model("Assets/models/neutral.obj");
		Model *angerPoseModel = new Model("Assets/models/anger.obj");
		Model *sadPoseModel = new Model("Assets/models/sad.obj");
		Model *surprisedPoseModel = new Model("Assets/models/surprised.obj");
		Mesh *neutralPose = neutralPoseModel->Instanciate(2);
		Mesh *angerPose = angerPoseModel->Instanciate(2);
		Mesh *sadPose = sadPoseModel->Instanciate(2);
		Mesh *surprisedPose = surprisedPoseModel->Instanciate(2);

		std::vector<MorphTarget*> morphTargets;
		morphTargets.push_back(new MorphTarget(surprisedPose->getGeometry(), 0.5f));
		morphTargets.push_back(new MorphTarget(sadPose->getGeometry(), 0.5f));
		morphTargets.push_back(new MorphTarget(angerPose->getGeometry(), 0.33f));
		MorphTargetGeometry *geo = new MorphTargetGeometry(neutralPose->getGeometry(), morphTargets);

		Material *mat = new LambertMaterial(Color(1.0f, 0.0f, 0.0f, 1.0f), Color(0.0f, 1.0f, 0.0f, 1.0f));
		Shader *shdr = new Shader("Assets/shaders/morphtarget.vs", "Assets/shaders/morphtarget.fs");
		shdr->load();
		mat->setShaderProgram(shdr);
		mat->loadTexture("Assets/textures/lava2.jpg");
		Mesh *m = new Mesh(geo, mat, "Test");
		m->setChildren(neutralPose->getChildren());
		m->drawStyle = GL_TRIANGLES;
		m->addComponent(new MTAnimator());
		scene->add(m);

		TwBar *bar = TwNewBar("User Interface");
		TwAddButton(bar, "Anger Pose", AngerPoseChoice, 0, "");
	});

	DeusExMachina::Destroy();
	delete settings;
	return 0;
}