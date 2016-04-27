#include "DEML.hpp"

__declspec(dllexport) double sign(double x)
{
	if (x > 0.0)
	{
		return 1.0;
	}
	return -1.0;
}

__declspec(dllexport) double sigmoid(double x)
{
	static double K = 1.0;
	return 1.0 / (1.0 + exp(-K * x));
}

__declspec(dllexport) double tanHyperbolic(double x)
{
	return tanh(x);
}

__declspec(dllexport) double* deml_linear_model_create(unsigned size)
{
	srand((unsigned)time(0));
	double *model = (double*)malloc(sizeof(double) * size);
	for (unsigned i = 0; i < size; ++i)
	{
		model[i] = -1.0 + 2.0 * (((double)(rand() % 100)) / 100.0);
	}
	return model;
}

__declspec(dllexport) double deml_linear_model_classify(double *X, double *W, unsigned size, _activation activation)
{
	double value = DEML_BIAS;
	for (unsigned i = 0; i < size; ++i)
	{
		value = value + X[i] * W[i];
	}
	value = activation(value);
	return value;
}

__declspec(dllexport) double deml_linear_model_predict(double *X, double *W, unsigned size)
{
	double value = DEML_BIAS;
	for (unsigned i = 0; i < size; ++i)
	{
		value = value + X[i] * W[i];
	}
	return value;
}

__declspec(dllexport) void deml_linear_model_fit_pla(double *X, double *Y, double *W, unsigned size, unsigned inputSize, _activation activation)
{
	srand((unsigned)time(0));

	bool error = true;
	unsigned count = 0;
	do
	{
		error = false;

		unsigned indexClass = rand() % inputSize;
		unsigned indexInput = rand() % size;
		double G = deml_linear_model_classify(X, W, size, activation);

		if (G != X[indexInput])
		{
			W[indexInput] = W[indexInput] + DEML_ALPHA * Y[indexClass] * X[indexInput];
		}

		++count;
	} while (error && count < DEML_FIT_MAXIMUM);
}

__declspec(dllexport) void deml_linear_model_fit_rosenblatt(double *X, double *Y, double *W, unsigned size, unsigned inputSize, _activation activation)
{
	srand((unsigned)time(0));

	bool error = true;
	unsigned count = 0;
	do
	{
		error = false;

		unsigned indexClass = rand() % inputSize;
		unsigned indexInput = rand() % size;
		double G = deml_linear_model_classify(X, W, size, activation);

		if (G != X[indexInput])
		{
			W[indexInput] = W[indexInput] + DEML_ALPHA * (Y[indexClass] - G) * X[indexInput];
		}

		++count;
	} while (error && count < DEML_FIT_MAXIMUM);
}

__declspec(dllexport) void deml_linear_model_free(double *W)
{
	free(W);
	W = 0;
}