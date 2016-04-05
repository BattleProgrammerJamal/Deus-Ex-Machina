#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <iostream>
#include <vector>
#include <ctime>

#include "Collections.hpp"
#include "Component.hpp"
#include "Crypto.hpp"
#include "Transform.hpp"

namespace DEM
{
	namespace Core
	{
		class Actor
		{
			public:
				Transform*		transform;

				Actor(std::string name = "Actor");
				Actor(const Actor& a);
				virtual ~Actor();
				
				std::vector<Core::Component*> getComponents() const;
				
				std::string getName() const;
				void setName(const std::string& name);

				DEM_UINT getUid() const;

				DEM_UINT getId() const;

				Actor& addComponent(Core::Component *comp);

				Actor* getParent() const;
				void setParent(Actor *actor);

				std::vector<Actor*> getChildren() const;
				void setChildren(std::vector<Actor*> children);

				void addChild(Actor *actor);

				void removeChildById(DEM_UINT id);
				void removeChildByUid(DEM_UINT uid);
				void removeChildByName(std::string name);

				Actor* findChildById(DEM_UINT id);
				Actor* findChildByUid(DEM_UINT uid);
				Actor* findChildByName(std::string name);


				virtual void Render()
				{
				}

				virtual void Update()
				{
				}

			protected:
				Actor*							m_parent;
				std::vector<Actor*>				m_children;
				std::vector<Core::Component*>	m_components;
				std::string						m_name;
				DEM_UINT						m_uid;
				static DEM_UINT					sm_id;
				DEM_UINT						m_id;
		};
	};
};

#endif