#pragma once
#include "Matrix.h"
#include "BaseRegression.h"

class LinearRegression:public BaseRegression
{
public:
	LinearRegression();
	~LinearRegression();

	void fit(const Matrix &x, const Matrix &y);		//������̬�������Իع�ѵ��ģ�Ͳ���
};

