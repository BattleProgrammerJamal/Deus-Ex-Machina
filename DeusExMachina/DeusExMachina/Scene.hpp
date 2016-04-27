#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <vector>
#include <string>

#include "FileINI.hpp"
#include "Actor.hpp"
#include "Color.hpp"

#define DEM_SCENE_POOL_RESERVE 100

namespace DEM
{
	namespace Core
	{
		class Scene
		{
			public:
				Scene(const std::string& name = "Scene");
				Scene(const std::string& path, const std::string& name);
				Scene(const Scene& scene);
				virtual ~Scene();

				DEM_UINT size() const;

				Scene& add(Actor *actor);
				Scene& add(const std::string& sceneFilePath);
				Actor* get(std::string name);
				Actor* get(DEM_UINT id);
				Actor* getByIndex(DEM_UINT id);
				std::vector<Actor*>::iterator* findById(DEM_UINT id);
				std::vector<Actor*>::iterator* findByName(std::string name);
				Scene& remove(Actor *actor);

				DEM_UINT getId() const;

				std::string getName() const;
				void setName(const std::string& name);

				std::vector<Actor*> getChildren() const;

			private:
				void _dynamicReserve();

				static DEM_UINT			sm_id;
				DEM_UINT				m_id;
				std::string				m_name;
				std::vector<Actor*>		m_children;
		};
	};
};

#endif