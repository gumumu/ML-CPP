#pragma once
#include "Matrix.h"

class LinearRegression
{
public:
	LinearRegression();
	~LinearRegression();

	
	void fit(const Matrix &x, const Matrix &y);		//利用正态方程线性回归训练模型参数
	Matrix predict(const Matrix &x);				//利用训练好的模型参数进行预测

	double score(const Matrix &x, const Matrix &y_true);	//计算得分，默认为r2_socre

private:
	Matrix extend_x(const Matrix &x);

public:
	Matrix module;
};

