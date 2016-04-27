#ifndef AI_HPP
#define AI_HPP

#include <iostream>
#include <vector>

#pragma comment(lib, "../Debug/DeusExMachinaLearning.lib")
#include "../DeusExMachineLearning/DEML.hpp"

#define DEM_NNL_CLASSIFICATION_ERROR -1000.0

namespace DEM
{
	namespace AI
	{
		template <typename T>
		class NeuralNetworkLinear
		{
			public:
				enum NEURAL_TRAINING_METHOD
				{
					PLA = 0,
					ROSENBLATT
				};

				enum NEURAL_ACTIVATION_METHOD
				{
					SIGN = 0,
					SIGMOID,
					HYPERBOLIC_TAN
				};

				NeuralNetworkLinear(unsigned perceptronCount, std::vector<T> datas = std::vector<T>(), std::vector<double> dataClasses = std::vector<double>(), NEURAL_TRAINING_METHOD trainingMethod = PLA, NEURAL_ACTIVATION_METHOD activationMethod = SIGN)
				{
					m_datas = datas;
					m_classes = dataClasses;
					m_trainingMethod = trainingMethod;
					m_activationMethod = activationMethod;
					_model = 0;
					setup(perceptronCount);
				}

				~NeuralNetworkLinear()
				{
					if (_model != 0)
					{
						deml_linear_model_free(_model);
					}
				}

				void setup(unsigned perceptronCount)
				{
					_perceptronCount = perceptronCount;
					_model = deml_linear_model_create(_perceptronCount);
				}

				std::vector<double> operator()(unsigned stride = 1, std::vector<T> datas = std::vector<T>(), std::vector<double> dataClasses = std::vector<double>())
				{
					if (datas.size()) { setDatas(datas); }
					if (dataClasses.size()){ setDataClasses(dataClasses); }

					std::vector<double> solutions;

					_activation activation = 0;
					switch (m_activationMethod)
					{
						case SIGN:
							activation = &sign;
						break;

						case SIGMOID:
							activation = &sigmoid;
						break;

						case HYPERBOLIC_TAN:
							activation = &tanHyperbolic;
						break;
					}

					for (unsigned j = 0; j < m_datas.size(); j += stride)
					{
						switch (m_trainingMethod)
						{
							case PLA:
								deml_linear_model_fit_pla(&m_datas[j], &m_classes[0], _model, _perceptronCount, stride, activation);
							break;

							case ROSENBLATT:
								deml_linear_model_fit_rosenblatt(&m_datas[j], &m_classes[0], _model, _perceptronCount, stride, activation);
							break;
						}

						double solution = deml_linear_model_classify(&m_datas[j], _model, stride, activation);

						solutions.emplace_back(solution);
					}

					return solutions;
				}

				std::vector<T> getDatas() const { return m_datas; }
				void setDatas(std::vector<T> datas) { m_datas = datas; }

				std::vector<double> getDataClasses() const { return m_classes; }
				void setDataClasses(std::vector<double> dataClasses) { m_classes = dataClasses; }

				NEURAL_TRAINING_METHOD getTrainingMethod() const { return m_trainingMethod; }
				void setTrainingMethod(NEURAL_TRAINING_METHOD trainingMethod) { m_trainingMethod = trainingMethod; }

				NEURAL_ACTIVATION_METHOD getActivationMethod() const { return m_activationMethod; }
				void setActivationMethod(NEURAL_ACTIVATION_METHOD activationMethod) { m_activationMethod = activationMethod; }

			private:
				double*									_model;
				unsigned								_perceptronCount;

				std::vector<T>							m_datas;
				std::vector<double>						m_classes;
				NEURAL_TRAINING_METHOD					m_trainingMethod;
				NEURAL_ACTIVATION_METHOD				m_activationMethod;

		};
	};
};

#endif