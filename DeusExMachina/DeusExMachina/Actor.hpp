#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <iostream>
#include <vector>
#include <ctime>

#include "Collections.hpp"
#include "Component.hpp"
#include "Crypto.hpp"

namespace DEM
{
	namespace Core
	{
		class Actor
		{
			public:
				Actor(std::string name = "Actor");
				Actor(const Actor& a);
				virtual ~Actor();
				
				std::vector<Core::Component*> getComponents() const;
				
				std::string getName() const;
				void setName(const std::string& name);

				DEM_UINT getUid() const;

				DEM_UINT getId() const;

				Actor& addComponent(Core::Component *comp);

				virtual void Render()
				{
				}

				virtual void Update()
				{
				}

			protected:
				std::vector<Core::Component*>	m_components;
				std::string						m_name;
				DEM_UINT						m_uid;
				static DEM_UINT					sm_id;
				DEM_UINT						m_id;
		};
	};
};

#endif