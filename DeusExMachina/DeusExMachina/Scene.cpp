#include "Scene.hpp"

using namespace DEM::Core;

DEM_UINT Scene::sm_id = 0;

#include "LambertMaterial.hpp"
#include "Mesh.hpp"

Scene::Scene(const std::string& name)
{
	m_id = sm_id;
	sm_id++;
	m_name = name;
	m_children.reserve(DEM_SCENE_POOL_RESERVE);
}

Scene::Scene(const std::string& path, const std::string& name)
{
	m_id = sm_id;
	sm_id++;
	m_name = name;
	m_children.reserve(DEM_SCENE_POOL_RESERVE);
	add(path);
}

Scene::Scene(const Scene& scene)
{
	m_id = sm_id;
	sm_id++;
	m_name = scene.m_name;
	m_children = scene.m_children;
	m_children.reserve(DEM_SCENE_POOL_RESERVE);
}

Scene::~Scene()
{
	for (Actor *actor : m_children)
	{
		delete actor;
		actor = 0;
	}
}

DEM_UINT Scene::size() const
{
	return m_children.size();
}

Scene& Scene::add(Actor *actor)
{
	_dynamicReserve();
	m_children.emplace_back(actor);
	return *this;
}

Scene& Scene::add(const std::string& sceneFilePath)
{
	FileINI *sceneFile = new FileINI(sceneFilePath);

	for (DEM_UINT i = 0; i < sceneFile->sections.size(); ++i)
	{
		FileINI::FSection *section = sceneFile->sections.at(i);
		std::string name = section->name;

		if (section->getByKey("name") != 0)
		{
			setName(section->getByKey("name")->value);
		}

		if (section->getByKey("type") == 0) { continue; }
		switch (Types::parse(section->getByKey("type")->value))
		{
			case Types::MESH:
				{
					Geometry *geometry = 0;
					Material *material = 0;
					Mesh *m = 0;

					if (section->getByKey("geometry")->value == "SphereGeometry")
					{
						geometry = new SphereGeometry(static_cast<float>(std::atof(section->getByKey("radius")->value.c_str())), 16, 16);
					}
					else
					{
						if (section->getByKey("geometry")->value == "PlaneGeometry")
						{
							geometry = new PlaneGeometry(static_cast<DEM_UINT>(std::atoi(section->getByKey("rows")->value.c_str())), static_cast<DEM_UINT>(std::atoi(section->getByKey("cols")->value.c_str())), static_cast<float>(std::atof(section->getByKey("width")->value.c_str())), static_cast<float>(std::atof(section->getByKey("height")->value.c_str())));
						}
					}

					if (section->getByKey("material")->value == "LambertMaterial")
					{
						std::vector<std::string> ambientElts = StringUtility::Split(section->getByKey("ambient")->value, ',');
						Math::Color ambient = Math::Color(static_cast<float>(std::atof(ambientElts.at(0).c_str())), static_cast<float>(std::atof(ambientElts.at(1).c_str())), static_cast<float>(std::atof(ambientElts.at(2).c_str())), static_cast<float>(std::atof(ambientElts.at(3).c_str())));
						std::vector<std::string> diffuseElts = StringUtility::Split(section->getByKey("diffuse")->value, ',');
						Math::Color diffuse = Math::Color(static_cast<float>(std::atof(diffuseElts.at(0).c_str())), static_cast<float>(std::atof(diffuseElts.at(1).c_str())), static_cast<float>(std::atof(diffuseElts.at(2).c_str())), static_cast<float>(std::atof(diffuseElts.at(3).c_str())));

						material = new LambertMaterial(ambient, diffuse);

						material->loadTexture(section->getByKey("texture")->value);
					}

					m = new Mesh(geometry, material, name);
					std::vector<std::string> positionElts = StringUtility::Split(section->getByKey("position")->value, ',');
					std::vector<std::string> rotationElts = StringUtility::Split(section->getByKey("rotation")->value, ',');
					std::vector<std::string> scaleElts = StringUtility::Split(section->getByKey("scale")->value, ',');
					m->transform->position = Math::Vector3(static_cast<float>(std::atof(positionElts.at(0).c_str())), static_cast<float>(std::atof(positionElts.at(1).c_str())), static_cast<float>(std::atof(positionElts.at(2).c_str())));
					Math::Vector3 rotEuler = Math::Vector3(static_cast<float>(std::atof(rotationElts.at(0).c_str())), static_cast<float>(std::atof(rotationElts.at(1).c_str())), static_cast<float>(std::atof(rotationElts.at(2).c_str())));
					rotEuler.x = Math::rad(rotEuler.x);
					rotEuler.y = Math::rad(rotEuler.y);
					rotEuler.z = Math::rad(rotEuler.z);
					m->transform->rotation = Math::Quaternion(Math::Vector3(0.0f, 0.0f, 1.0f), rotEuler.z) * Math::Quaternion(Math::Vector3(1.0f, 0.0f, 0.0f), rotEuler.x) * Math::Quaternion(Math::Vector3(0.0f, 1.0f, 0.0f), rotEuler.y);
					m->transform->scale = Math::Vector3(static_cast<float>(std::atof(scaleElts.at(0).c_str())), static_cast<float>(std::atof(scaleElts.at(1).c_str())), static_cast<float>(std::atof(scaleElts.at(2).c_str())));
					m_children.emplace_back(m);
				}
			break;

			case Types::MODEL_OBJ:
				{
					Model *model = new Model(section->getByKey("src")->value);

					Material *material = 0;
					Mesh *m = 0;

					if (section->getByKey("material")->value == "LambertMaterial")
					{
						std::vector<std::string> ambientElts = StringUtility::Split(section->getByKey("ambient")->value, ',');
						Math::Color ambient = Math::Color(static_cast<float>(std::atof(ambientElts.at(0).c_str())), static_cast<float>(std::atof(ambientElts.at(1).c_str())), static_cast<float>(std::atof(ambientElts.at(2).c_str())), static_cast<float>(std::atof(ambientElts.at(3).c_str())));
						std::vector<std::string> diffuseElts = StringUtility::Split(section->getByKey("diffuse")->value, ',');
						Math::Color diffuse = Math::Color(static_cast<float>(std::atof(diffuseElts.at(0).c_str())), static_cast<float>(std::atof(diffuseElts.at(1).c_str())), static_cast<float>(std::atof(diffuseElts.at(2).c_str())), static_cast<float>(std::atof(diffuseElts.at(3).c_str())));

						material = new LambertMaterial(ambient, diffuse);

						material->loadTexture(section->getByKey("texture")->value);
					}

					m = model->Instanciate(0);
					std::vector<std::string> positionElts = StringUtility::Split(section->getByKey("position")->value, ',');
					std::vector<std::string> rotationElts = StringUtility::Split(section->getByKey("rotation")->value, ',');
					std::vector<std::string> scaleElts = StringUtility::Split(section->getByKey("scale")->value, ',');
					m->transform->position = Math::Vector3(static_cast<float>(std::atof(positionElts.at(0).c_str())), static_cast<float>(std::atof(positionElts.at(1).c_str())), static_cast<float>(std::atof(positionElts.at(2).c_str())));
					Math::Vector3 rotEuler = Math::Vector3(static_cast<float>(std::atof(rotationElts.at(0).c_str())), static_cast<float>(std::atof(rotationElts.at(1).c_str())), static_cast<float>(std::atof(rotationElts.at(2).c_str())));
					rotEuler.x = Math::rad(rotEuler.x); 
					rotEuler.y = Math::rad(rotEuler.y); 
					rotEuler.z = Math::rad(rotEuler.z);
					m->transform->rotation = Math::Quaternion(Math::Vector3(0.0f, 0.0f, 1.0f), rotEuler.z) * Math::Quaternion(Math::Vector3(1.0f, 0.0f, 0.0f), rotEuler.x) * Math::Quaternion(Math::Vector3(0.0f, 1.0f, 0.0f), rotEuler.y);
					m->transform->scale = Math::Vector3(static_cast<float>(std::atof(scaleElts.at(0).c_str())), static_cast<float>(std::atof(scaleElts.at(1).c_str())), static_cast<float>(std::atof(scaleElts.at(2).c_str())));
					m->setName(name);
					m->setMaterial(material);
					m_children.emplace_back(m);
				}
			break;

			case Types::DIRECTIONAL_LIGHT:
				{
					std::vector<std::string> lightDirElts = StringUtility::Split(section->getByKey("direction")->value, ',');
					Math::Vector3 lightDirection = Math::Vector3(static_cast<float>(std::atof(lightDirElts.at(0).c_str())), static_cast<float>(std::atof(lightDirElts.at(1).c_str())), static_cast<float>(std::atof(lightDirElts.at(2).c_str())));
					std::vector<std::string> lightColElts = StringUtility::Split(section->getByKey("color")->value, ',');
					Math::Color lightColor = Math::Color(static_cast<float>(std::atof(lightColElts.at(0).c_str())), static_cast<float>(std::atof(lightColElts.at(1).c_str())), static_cast<float>(std::atof(lightColElts.at(2).c_str())), static_cast<float>(std::atof(lightColElts.at(3).c_str())));
				
					DirectionalLight *dLight = new DirectionalLight(Math::Vector3(), lightDirection);
					dLight->color = lightColor;
					dLight->setName(name);
					m_children.emplace_back(dLight);
				}
			break;

			case Types::POINT_LIGHT:
				{
					std::vector<std::string> lightPosElts = StringUtility::Split(section->getByKey("position")->value, ',');
					Math::Vector3 lightPosition = Math::Vector3(static_cast<float>(std::atof(lightPosElts.at(0).c_str())), static_cast<float>(std::atof(lightPosElts.at(1).c_str())), static_cast<float>(std::atof(lightPosElts.at(2).c_str())));
					std::vector<std::string> lightColElts = StringUtility::Split(section->getByKey("color")->value, ',');
					Math::Color lightColor = Math::Color(static_cast<float>(std::atof(lightColElts.at(0).c_str())), static_cast<float>(std::atof(lightColElts.at(1).c_str())), static_cast<float>(std::atof(lightColElts.at(2).c_str())), static_cast<float>(std::atof(lightColElts.at(3).c_str())));

					PointLight *pLight = new PointLight(lightPosition);
					pLight->color = lightColor;
					pLight->setName(name);
					m_children.emplace_back(pLight);
				}
			break;

			case Types::SOUND:
				{
					Sound *sound = new Sound();
					sound->load(section->getByKey("src")->value);
					sound->setName(name);
					m_children.emplace_back(sound);
				}
			break;

			case Types::MUSIC:
				{
					Music *music = new Music(section->getByKey("src")->value);
					music->load(section->getByKey("src")->value);
					music->setName(name);
					m_children.emplace_back(music);
				}
			break;
		}
	}

	delete sceneFile;
	return *this;
}

Actor* Scene::get(std::string name)
{
	for (DEM_UINT i = 0; i < m_children.size(); ++i)
	{
		if (m_children.at(i)->getName() == name)
		{
			return m_children.at(i);
		}
	}
	return 0;
}

Actor* Scene::get(DEM_UINT id)
{
	for (DEM_UINT i = 0; i < m_children.size(); ++i)
	{
		Actor *actor = m_children.at(i);
		if (actor)
		{
			if (actor->getId() == id)
			{
				return actor;
			}
		}
	}
	return 0;
}

Actor* Scene::getByIndex(DEM_UINT id)
{
	return m_children.at(id);
}

std::vector<Actor*>::iterator* Scene::findById(DEM_UINT id)
{
	std::vector<Actor*>::iterator &it = m_children.begin();
	for (; it != m_children.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			return &it;
		}
	}
	return 0;
}

std::vector<Actor*>::iterator* Scene::findByName(std::string name)
{
	std::vector<Actor*>::iterator &it = m_children.begin();
	for (; it != m_children.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			return &it;
		}
	}
	return 0;
}

Scene& Scene::remove(Actor *actor)
{
	if (!actor) { return *this; }

	std::vector<Actor*>::iterator it = m_children.begin(), rslt;
	bool found = false;
	for (; it != m_children.end(); ++it)
	{
		if ((*it)->getId() == actor->getId())
		{
			rslt = it;
			found = true;
			break;
		}
	}
	if (found)
	{
		m_children.erase(rslt, rslt + 1);
	}
	return *this;
}

DEM_UINT Scene::getId() const
{
	return m_id;
}

std::string Scene::getName() const
{
	return m_name;
}

void Scene::setName(const std::string& name)
{
	m_name = name;
}

std::vector<Actor*> Scene::getChildren() const
{
	return m_children;
}

void Scene::_dynamicReserve()
{
	if (m_children.size() == (m_children.capacity() - 1))
	{
		m_children.reserve(DEM_SCENE_POOL_RESERVE);
	}
}