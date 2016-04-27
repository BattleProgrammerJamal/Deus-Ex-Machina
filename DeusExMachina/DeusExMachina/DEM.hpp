#ifndef DEM_HPP
#define DEM_HPP

#define DEM_DEBUG 0

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <glew.h>
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <STB/stb_image.h>

#include "AntTweakBar/AntTweakBar.h"

#include "System.hpp"
#include "Math.hpp"
#include "AI.hpp"
#include "File.hpp"
#include "FileCSV.hpp"
#include "FileINI.hpp"
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
#include "ConvolutionMaterial.hpp"
#include "Light.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"
#include "Geometry.hpp"
#include "SphereGeometry.hpp"
#include "PlaneGeometry.hpp"
#include "MorphTargetGeometry.hpp"
#include "Transform.hpp"
#include "Actor.hpp"
#include "Audio.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

#define DEM_DEFAULT_CONFIG_PATH "Assets/system/config.ini"

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
		Math::Vector3 eye;
		Math::Vector3 target;
		Math::Vector3 up;

		CameraSettings()
		{
			position.set(0.0f, 0.0f);
			width = 1024.0f;
			height = 768.0f;
			fov = Math::rad<float>(45.0f);
			aspect = 1024.0f / 768.0f;
			cnear = 0.1f;
			cfar = 100000.0f;
			eye.set(0.0f, 0.0f, 2.0f);
			target.set(0.0f, 0.0f, 0.0f);
			up.set(0.0f, 1.0f, 0.0f);
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
			Core::FileINI *config = new Core::FileINI(DEM_DEFAULT_CONFIG_PATH);
			
			if ((*config)["Project"].at(0)->value == "2D")
			{
				type = DEM_PROJECT_2D;
			}
			else
			{
				type = DEM_PROJECT_3D;
			}
			title = (*config)["Project"].at(1)->value;
			if ((*config)["Project"].at(2)->value == "enable")
			{
				fullscreen = true;
			}
			else
			{
				fullscreen = false;
			}
			
			width = static_cast<DEM_UINT>(std::atof((*config)["Camera"].at(0)->value.c_str()));
			height = static_cast<DEM_UINT>(std::atof((*config)["Camera"].at(1)->value.c_str()));
			cameraSettings.width = static_cast<float>(std::atof((*config)["Camera"].at(0)->value.c_str()));
			cameraSettings.height = static_cast<float>(std::atof((*config)["Camera"].at(1)->value.c_str()));
			cameraSettings.fov = Math::rad<float>(static_cast<float>(std::atof((*config)["Camera"].at(2)->value.c_str())));
			cameraSettings.aspect = cameraSettings.width / cameraSettings.height;
			cameraSettings.cnear = static_cast<float>(std::atof((*config)["Camera"].at(3)->value.c_str()));
			cameraSettings.cfar = static_cast<float>(std::atof((*config)["Camera"].at(4)->value.c_str()));
			std::vector<std::string> eyeElts = StringUtility::Split(config->sections.at(2)->getByKey("eye")->value, ',');
			std::vector<std::string> targetElts = StringUtility::Split(config->sections.at(2)->getByKey("target")->value, ',');
			std::vector<std::string> upElts = StringUtility::Split(config->sections.at(2)->getByKey("up")->value, ',');
			cameraSettings.eye = Math::Vector3(static_cast<float>(std::atof(eyeElts.at(0).c_str())), static_cast<float>(std::atof(eyeElts.at(1).c_str())), static_cast<float>(std::atof(eyeElts.at(2).c_str())));
			cameraSettings.target = Math::Vector3(static_cast<float>(std::atof(targetElts.at(0).c_str())), static_cast<float>(std::atof(targetElts.at(1).c_str())), static_cast<float>(std::atof(targetElts.at(2).c_str())));
			cameraSettings.up = Math::Vector3(static_cast<float>(std::atof(upElts.at(0).c_str())), static_cast<float>(std::atof(upElts.at(1).c_str())), static_cast<float>(std::atof(upElts.at(2).c_str())));

			delete config;
		}

		~ProjectSettings()
		{
		}
	};

	class RenderActorsPipeline;
	class UpdateActorsPipeline;
	class UpdateActorComponentsPipeline;
	class SFMLWindowHandlerPipeline;

	class InputEvent
	{
		public:
			virtual void operator()() = 0;
	};

	class KeyboardEvent : public InputEvent
	{
		public:
			sf::Keyboard::Key key;

			virtual void operator()() = 0;
	};

	class MouseMoveEvent : public InputEvent
	{
		public:
			Math::Vector2 position;

			virtual void operator()() = 0;
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

			void addEventListener(InputEvent *evt)
			{
				m_inputListeners.emplace_back(evt);
			}

			std::vector<InputEvent*> getEventListeners() const
			{
				return m_inputListeners;
			}

		private:
			DeusExMachina(ProjectSettings *settings);

			static DeusExMachina*			sm_instance;
			std::vector<InputEvent*>		m_inputListeners;
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

				TwInit(TW_OPENGL, (void*)0);

				static const DEM_UINT UBO_SIZE = sizeof(float) * (16 + 16);

				GLuint ubo = app->getUBO();
				glGenBuffers(1, &ubo);
				glBindBuffer(GL_UNIFORM_BUFFER, ubo);
				glBufferData(GL_UNIFORM_BUFFER, UBO_SIZE, 0, GL_STREAM_DRAW);
				glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo);
				glBindBuffer(GL_UNIFORM_BUFFER, ubo);

				DEM::Core::Renderer *renderer = app->getRenderer();
				DEM::Core::Scene *scene = renderer->getScene();
				DEM::Core::Camera *camera = renderer->getCamera();

				renderer->initSkybox();

				if (OnDisplayContextInitialized != 0)
				{
					OnDisplayContextInitialized(app);
				}

				for (DEM_UINT i = 0; i < scene->size(); ++i)
				{
					DEM_UINT id = scene->getByIndex(i)->getId();
					renderer->executeCmd(new DEM::Core::RCActorComponentsStart(id));
				}

				while (state())
				{
					if (window->pollEvent(evt))
					{
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
							for (InputEvent *event : app->getEventListeners())
							{
								KeyboardEvent *kbEvt = static_cast<KeyboardEvent*>(event);
								if (kbEvt)
								{
									kbEvt->key = evt.key.code;
									(*kbEvt)();
								}
							}
						}

						if (evt.type == sf::Event::MouseMoved)
						{
							for (InputEvent *event : app->getEventListeners())
							{
								MouseMoveEvent *mouseMoveEvt = static_cast<MouseMoveEvent*>(event);
								if (mouseMoveEvt)
								{
									mouseMoveEvt->position.set((float)evt.mouseMove.x, (float)evt.mouseMove.y);
									(*mouseMoveEvt)();
								}
							}
						}

						TwEventSFML(&evt, SFML_VERSION_MAJOR, SFML_VERSION_MINOR);
					}
					
					glBindBuffer(GL_UNIFORM_BUFFER, ubo);
					glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * 16, camera->getView().ptr_value());
					glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float) * 16, sizeof(float) * 16, camera->getProj().ptr_value());
					glBindBuffer(GL_UNIFORM_BUFFER, 0);

					glViewport(0, 0, parameters->width, parameters->height);
					glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

					renderer->renderSkybox();

					for (DEM_UINT i = 0; i < app->getRenderer()->getScene()->size(); ++i)
					{
						DEM_UINT id = scene->getByIndex(i)->getId();
						renderer->executeCmd(new Core::RCActorRender(id));
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
						DEM_UINT id = app->getRenderer()->getScene()->getByIndex(i)->getId();
						app->getRenderer()->executeCmd(new Core::RCActorUpdate(id));
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
						DEM_UINT id = app->getRenderer()->getScene()->getByIndex(i)->getId();
						Core::Actor *actor = app->getRenderer()->getScene()->get(id);
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