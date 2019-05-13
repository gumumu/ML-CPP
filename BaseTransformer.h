#pragma once
#include "Matrix.h"
/*
接口类：定义转换器基本接口
*/
class BaseTransformer
{
public:
	BaseTransformer();
	~BaseTransformer();

	virtual void fit(const Matrix &x) = 0;					//接口：通过超参数和x计算得到转换器模型
	virtual Matrix transform(const Matrix &x) const = 0;	//接口：通过转换器模型模型得到x转换后的矩阵
	virtual Matrix fit_transform(const Matrix &x);		//接口：fit+transform
};

