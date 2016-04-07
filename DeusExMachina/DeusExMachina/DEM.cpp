#include "DEM.hpp"

using namespace DEM;
using namespace DEM::Core;

DeusExMachina* DeusExMachina::sm_instance = 0;

DeusExMachina::DeusExMachina(ProjectSettings *settings)
{
	m_ubo = 0;
	m_settings = settings;

	m_system = System::System::Instance();

	CameraSettings camSettings = settings->cameraSettings;

	if (settings->type == DEM_PROJECT_3D)
	{
		m_renderer = new Renderer(new PerspectiveCamera(camSettings.fov, camSettings.aspect, camSettings.cnear, camSettings.cfar), new Scene("New Scene"));
	}
	else
	{
		m_renderer = new Renderer(new OrthographicCamera(camSettings.position, camSettings.width, camSettings.height), new Scene("New Scene"));
	}

	m_system->initUiAPI();
	m_system->initAudioAPI();
}

DeusExMachina::~DeusExMachina()
{
	delete m_renderActorsPipeline;
	delete m_updateActorsPipeline;
	delete m_updateActorComponentsPipeline;
}

DeusExMachina* DeusExMachina::Instance(ProjectSettings *settings)
{
	if (sm_instance == 0)
	{
		sm_instance = new DeusExMachina(settings);
	}

	return sm_instance;
}

void DeusExMachina::Destroy()
{
	if (sm_instance)
	{
		delete sm_instance;
	}
}

System::System* DeusExMachina::getSystem() const
{
	return m_system;
}

void DeusExMachina::operator()(void(*OnDisplayContextInitialized)(DeusExMachina*))
{
	for (DEM_UINT i = 0; i < m_renderer->getScene()->size(); ++i)
	{
		m_renderer->executeCmd(new RCActorComponentsStart(i));
	}

	m_renderActorsPipeline = new RenderActorsPipeline(this);
	m_updateActorsPipeline = new UpdateActorsPipeline(this);
	m_updateActorComponentsPipeline = new UpdateActorComponentsPipeline(this);

	m_renderActorsPipeline->create(OnDisplayContextInitialized);
	m_updateActorsPipeline->create();
	m_updateActorComponentsPipeline->create();

	m_renderActorsPipeline->run();
	m_updateActorsPipeline->run();
	m_updateActorComponentsPipeline->run();
}