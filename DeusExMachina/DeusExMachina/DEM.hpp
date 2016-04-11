#ifndef DEM_HPP
#define DEM_HPP

#define DEM_DEBUG 0

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <STB/stb_image.h>

#include "System.hpp"
#include "File.hpp"
#include "Pipeline.hpp"
#include "Component.hpp"
#include "Resource.hpp"
#include "Model.hpp"
#include "Image.hpp"
#include "Asset.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "LambertMaterial.hpp"
#include "PhongMaterial.hpp"
#include "Light.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"
#include "Geometry.hpp"
#include "SphereGeometry.hpp"
#include "MorphTargetGeometry.hpp"
#include "Transform.hpp"
#include "Actor.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

namespace DEM
{
	static const char* name = "Deus Ex Machina";
	static DEM_UINT version_major = 1;
	static DEM_UINT version_minor = 0;

	enum ProjetRendererType
	{
		DEM_PROJECT_2D = 0,
		DEM_PROJECT_3D
	};

	struct CameraSettings
	{
		Math::Vector2 position;
		float width;
		float height;
		float fov;
		float aspect;
		float cnear;
		float cfar;

		CameraSettings()
		{
			position.set(0.0f, 0.0f);
			width = 1024.0f;
			height = 768.0f;
			fov = Math::rad<float>(45.0f);
			aspect = 1024.0f / 768.0f;
			cnear = 0.1f;
			cfar = 100000.0f;
		}
	};

	struct ProjectSettings
	{
		ProjetRendererType type;
		CameraSettings cameraSettings;
		std::string title;
		DEM_UINT width;
		DEM_UINT height;
		bool fullscreen;

		ProjectSettings()
		{
			type = DEM_PROJECT_3D;
			title = "Deus Ex Machina";
			fullscreen = false;
			width = 1024;
			height = 768;
			cameraSettings.width = width;
			cameraSettings.height = height;
		}

		~ProjectSettings()
		{
		}
	};

	class RenderActorsPipeline;
	class UpdateActorsPipeline;
	class UpdateActorComponentsPipeline;
	class SFMLWindowHandlerPipeline;

	class KeyboardEvent
	{
		public:
			virtual void operator()(sf::Keyboard::Key key) = 0;
	};

	class DeusExMachina
	{
		public:
			~DeusExMachina();

			static DeusExMachina* Instance(ProjectSettings *settings = 0);

			static void Destroy();
			
			System::System* getSystem() const;

			Core::Renderer* getRenderer() { return m_renderer; }

			void operator()(void (*OnDisplayContextInitialized)(DeusExMachina*) = 0);

			ProjectSettings* settings() const { return m_settings; }
			void setSettings(ProjectSettings *settings) { m_settings = settings; }

			GLuint getUBO() const
			{
				return m_ubo;
			}

			void setUBO(GLuint ubo)
			{
				m_ubo = ubo;
			}

			void addKeyboardEventListener(KeyboardEvent *kbEvent)
			{
				m_keyboardListeners.emplace_back(kbEvent);
			}

			std::vector<KeyboardEvent*> getKeyboardListeners() const
			{
				return m_keyboardListeners;
			}

		private:
			DeusExMachina(ProjectSettings *settings);

			static DeusExMachina*			sm_instance;
			std::vector<KeyboardEvent*>		m_keyboardListeners;
			ProjectSettings*				m_settings;
			System::System*					m_system;
			Core::Renderer*					m_renderer;
			RenderActorsPipeline*			m_renderActorsPipeline;
			UpdateActorsPipeline*			m_updateActorsPipeline;
			UpdateActorComponentsPipeline*	m_updateActorComponentsPipeline;
			GLuint							m_ubo;
	};

	class RenderActorsPipeline : public Core::Pipeline
	{
		public:
			RenderActorsPipeline(DeusExMachina *_app)
				: Core::Pipeline()
			{
				app = _app;
			}

			void RenderActorsPipeline::operator()(void(*OnDisplayContextInitialized)(DeusExMachina*))
			{
				sf::ContextSettings settings;
				settings.depthBits = 24;
				settings.stencilBits = 8;
				settings.antialiasingLevel = 4;
				settings.majorVersion = OPENGL_MAJOR_VERSION;
				settings.minorVersion = OPENGL_MINOR_VERSION;

				ProjectSettings *parameters = app->settings();

				if (!parameters->fullscreen)
				{
					window = new sf::Window(sf::VideoMode(parameters->width, parameters->height), parameters->title.c_str(), sf::Style::Default, settings);
				}
				else
				{
					window = new sf::Window(sf::VideoMode(), parameters->title.c_str(), sf::Style::Fullscreen, settings);
				}

				glewExperimental = GL_TRUE;
				if (glewInit() != GLEW_OK)
				{
					std::cerr << "Unable to initialize GLEW" << std::endl;
				}

				GLint numExtensions;
				glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
				int index = 0;
				for (index = 0; index < numExtensions; ++index)
				{
					glGetStringi(GL_EXTENSIONS, index);
				}

				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);

#if defined(DEM_DEBUG) && DEM_DEBUG == 1
				std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
				std::cout << "GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
				std::cout << "GPU Version : " << glGetString(GL_RENDERER) << std::endl;
#endif

				static const DEM_UINT UBO_SIZE = sizeof(float) * (16 + 16);

				GLuint ubo = app->getUBO();
				glGenBuffers(1, &ubo);
				glBindBuffer(GL_UNIFORM_BUFFER, ubo);
				glBufferData(GL_UNIFORM_BUFFER, UBO_SIZE, 0, GL_STREAM_DRAW);
				glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo);
				glBindBuffer(GL_UNIFORM_BUFFER, ubo);

				if (OnDisplayContextInitialized != 0)
				{
					OnDisplayContextInitialized(app);
				}

				DEM::Core::Renderer *renderer = app->getRenderer();
				DEM::Core::Scene *scene = renderer->getScene();
				DEM::Core::Camera *camera = renderer->getCamera();

				for (DEM_UINT i = 0; i < scene->size(); ++i)
				{
					renderer->executeCmd(new DEM::Core::RCActorComponentsStart(i));
				}

				while (state())
				{
					if (window->pollEvent(evt))
					{
						TwEventSFML(&evt, SFML_VERSION_MAJOR, SFML_VERSION_MINOR);

						if (evt.type == sf::Event::Closed || (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Escape))
						{
							Pipeline::command(Core::KILL_ALL);
						}

						if (evt.type == sf::Event::Resized)
						{
							sf::Vector2u windowSize = window->getSize();
							parameters->width = windowSize.x;
							parameters->height = windowSize.y;
							glViewport(0, 0, parameters->width, parameters->height);
						}

						if (evt.type == sf::Event::KeyPressed)
						{
							for (KeyboardEvent *kbEvent : app->getKeyboardListeners())
							{
								(*kbEvent)(evt.key.code);
							}
						}
					}
					
					/*
					glBindBuffer(GL_UNIFORM_BUFFER, ubo);
					glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * 16, camera->getView().ptr_value());
					glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float) * 16, sizeof(float) * 16, camera->getProj().ptr_value());
					glBindBuffer(GL_UNIFORM_BUFFER, 0);
					*/

					glViewport(0, 0, parameters->width, parameters->height);
					glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

					for (DEM_UINT i = 0; i < app->getRenderer()->getScene()->size(); ++i)
					{
						app->getRenderer()->executeCmd(new Core::RCActorRender(i));
					}

					sf::Vector2u size = window->getSize();
					TwWindowSize(size.x, size.y);
					TwDraw();

					window->display();
				}
			}

			void RenderActorsPipeline::create(void(*OnDisplayContextInitialized)(DeusExMachina*))
			{
				m_proc = new std::thread(&RenderActorsPipeline::operator(), this, OnDisplayContextInitialized);
			}

			void RenderActorsPipeline::run()
			{
				m_proc->join();
			}

		private:
			DeusExMachina*	app;
			sf::Window*		window;
			sf::Event		evt;
	};

	class UpdateActorsPipeline : public Core::Pipeline
	{
		public:
			UpdateActorsPipeline(DeusExMachina *_app)
				: Core::Pipeline()
			{
				app = _app;
			}

			void UpdateActorsPipeline::operator()()
			{
				while (state())
				{
					for (DEM_UINT i = 0; i < app->getRenderer()->getScene()->size(); ++i)
					{
						app->getRenderer()->executeCmd(new Core::RCActorUpdate(i));
					}
				}
			}

			void UpdateActorsPipeline::create()
			{
				m_proc = new std::thread(&UpdateActorsPipeline::operator(), this);
			}

			void UpdateActorsPipeline::run()
			{
				m_proc->join();
			}

		private:
			DeusExMachina*	app;
	};

	class UpdateActorComponentsPipeline : public Core::Pipeline
	{
		public:
			UpdateActorComponentsPipeline(DeusExMachina *_app)
				: Core::Pipeline()
			{
				app = _app;
			}

			void UpdateActorComponentsPipeline::operator()()
			{
				while (state())
				{
					for (DEM_UINT i = 0; i < app->getRenderer()->getScene()->size(); ++i)
					{
						Core::Actor *actor = app->getRenderer()->getScene()->get(i);
						if (actor)
						{
							for (DEM_UINT j = 0; j < actor->getComponents().size(); ++j)
							{
								app->getRenderer()->executeCmd(new Core::RCActorComponentUpdate(i, j));
							}
						}
					}
				}
			}

			void UpdateActorComponentsPipeline::create()
			{
				m_proc = new std::thread(&UpdateActorComponentsPipeline::operator(), this);
			}

			void UpdateActorComponentsPipeline::run()
			{
				m_proc->join();
			}

		private:
			DeusExMachina*	app;
	};
};

#endif