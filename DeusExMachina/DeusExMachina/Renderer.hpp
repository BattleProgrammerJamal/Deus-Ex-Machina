#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <strstream>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Scene.hpp"
#include "Camera.hpp"

#include "Transform.hpp"

#include "Geometry.hpp"
#include "Material.hpp"

#define DEM_RENDER_DEBUG 0

#define DEM_SKYBOX_TEXTURE_UNIT 15

#define DEFAULT_SKYBOX_VS "Assets/shaders/skybox.vs"
#define DEFAULT_SKYBOX_FS "Assets/shaders/skybox.fs"

namespace DEM
{
	namespace Core
	{
		class Mesh;
		struct RenderCommand;

		class Renderer
		{
			public:
				Renderer(Camera *camera, Scene *scene);
				virtual ~Renderer();

				
				Renderer& addScene(Scene *scene);
				
				Renderer& loadScene(DEM_UINT index);

				Renderer& executeCmd(RenderCommand *cmd);

				Renderer& RenderActor(DEM_UINT index);
				Renderer& UpdateActor(DEM_UINT index);
				Renderer& StartComponents(Actor *actor);
				Renderer& UpdateComponent(Actor *actor, DEM_UINT index);
				
				Camera* getCamera();
				void setCamera(Camera* camera);

				Scene* getScene();
				void setScene(Scene* scene);

				bool isSkyboxEnabled() const;
				void enableSkybox();
				void disableSkybox();

				void initSkybox();
				void loadSkybox(const std::string& right, const std::string& left, const std::string& up, const std::string& down, const std::string& forward, const std::string& back);

				void renderSkybox();

				Material* getSkyboxMaterial() const;
				
			private:
				Camera*					m_camera;
				Scene*					m_scene;
				Geometry*				m_skyboxGeometry;
				Material*				m_skyboxMaterial;
				bool					m_enableSkybox;
				DEM_UINT				m_currentSceneIndex;
				std::vector<Scene*>		m_scenes;
		};

		struct RenderCommand
		{
			RenderCommand(){}
			virtual void operator()(Renderer *renderer) = 0;

			virtual std::string str() const { return "RC"; }
		};

		struct RCActorRender : public RenderCommand
		{
			DEM_UINT actorIndex;
			RCActorRender(DEM_UINT _actorIndex) : RenderCommand(){ actorIndex = _actorIndex; }
			void operator()(Renderer *renderer)
			{
				renderer->RenderActor(actorIndex);
#if defined(DEM_RENDER_DEBUG) && (DEM_RENDER_DEBUG == 1)
				std::cout << std::endl << "Command executed : " << str() << std::endl; 
#endif
			}

			std::string str() const { std::strstream out; out << "RCActorRender = Actor Index : " << actorIndex; out << '\0'; return out.str(); }
		};

		struct RCActorUpdate : public RenderCommand
		{
			DEM_UINT actorIndex;
			RCActorUpdate(DEM_UINT _actorIndex) : RenderCommand(){ actorIndex = _actorIndex; }
			void operator()(Renderer *renderer)
			{
				renderer->UpdateActor(actorIndex);

#if defined(DEM_RENDER_DEBUG) && (DEM_RENDER_DEBUG == 1)
				std::cout << std::endl << "Command executed : " << str() << std::endl;
#endif
			}

			std::string str() const { std::strstream out; out << "RCActorUpdate = Actor Index : " << actorIndex; out << '\0'; return out.str(); }
		};

		struct RCActorComponentsStart : public RenderCommand
		{
			DEM_UINT actorIndex;
			RCActorComponentsStart(DEM_UINT _actorIndex) : RenderCommand(){ actorIndex = _actorIndex; }
			void operator()(Renderer *renderer)
			{
				Actor *actor = renderer->getScene()->get(actorIndex);
				if (actor)
				{
					renderer->StartComponents(actor);
				}

#if defined(DEM_RENDER_DEBUG) && (DEM_RENDER_DEBUG == 1)
				std::cout << "Command executed : " << str() << std::endl;
#endif
			}

			std::string str() const { std::strstream out; out << "RCActorComponentsStart = Actor Index : " << actorIndex; out << '\0'; return out.str(); }
		};

		struct RCActorComponentUpdate : public RenderCommand
		{
			DEM_UINT actorIndex;
			DEM_UINT componentIndex;
			RCActorComponentUpdate(DEM_UINT _actorIndex, DEM_UINT _componentIndex) : RenderCommand(){ actorIndex = _actorIndex; componentIndex = _componentIndex; }
			void operator()(Renderer *renderer)
			{
				Actor *actor = renderer->getScene()->get(actorIndex);
				if (actor)
				{
					renderer->UpdateComponent(actor, componentIndex);
				}

#if defined(DEM_RENDER_DEBUG) && (DEM_RENDER_DEBUG == 1)
				std::cout << "Command executed : " << str() << std::endl;
#endif
			}

			std::string str() const { std::strstream out; out << "RCActorCommandUpdate = Actor Index : " << actorIndex << "; Component Index : " << componentIndex; out << '\0'; return out.str(); }
		};
	};
};

#endif