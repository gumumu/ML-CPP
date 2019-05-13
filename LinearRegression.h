#pragma once
#include "Matrix.h"
#include "BaseRegression.h"

class LinearRegression:public BaseRegression
{
public:
	LinearRegression();
	~LinearRegression();

	void fit(const Matrix &x, const Matrix &y);		//利用正态方程线性回归训练模型参数
};

