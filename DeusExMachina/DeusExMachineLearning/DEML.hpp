#ifndef DEML_HPP
#define DEML_HPP

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define DEML_FIT_MAXIMUM	500
#define DEML_BIAS			1.0
#define DEML_ALPHA			0.1

/**
					Params
	---------------------------------------------------
	DEML_ALPHA		Learning Step
	X				Input Value
	Y				Input Class
	G				Solution

					Formulas
	----------------------------------------------------
	Perceptron Learning Algorithm				(G(x) != Y : Bad Classification)
					W = W + alpha * Y * X
	Rosenblatt
					W = W + alpha * (Y - G) * X
*/

extern "C"
{
	typedef __declspec(dllexport) double(*_activation)(double x);

	__declspec(dllexport) double sign(double x);
	__declspec(dllexport) double sigmoid(double x);
	__declspec(dllexport) double tanHyperbolic(double x);

	__declspec(dllexport) double* deml_linear_model_create(unsigned size);
	__declspec(dllexport) double deml_linear_model_classify(double *X, double *W, unsigned size, _activation activation);
	__declspec(dllexport) double deml_linear_model_predict(double *X, double *W, unsigned size);
	__declspec(dllexport) void deml_linear_model_fit_pla(double *X, double *Y, double *W, unsigned size, unsigned inputSize, _activation activation);
	__declspec(dllexport) void deml_linear_model_fit_rosenblatt(double *X, double *Y, double *W, unsigned size, unsigned inputSize, _activation activation);
	__declspec(dllexport) void deml_linear_model_free(double *W);
}

#endif