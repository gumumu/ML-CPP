#pragma once
#include "Matrix.h"
class BaseRegression
{
public:
	BaseRegression();
	~BaseRegression();

	virtual Matrix predict(const Matrix &x) const;				//利用训练好的模型参数进行预测
	virtual double score(const Matrix &x, const Matrix &y_true) const;	//计算得分，默认为r2_socre

protected:
	virtual Matrix extend_x(const Matrix &x) const;

public:
	Matrix module;
};

