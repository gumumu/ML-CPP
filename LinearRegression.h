#pragma once
#include "Matrix.h"

class LinearRegression
{
public:
	LinearRegression();
	~LinearRegression();

	
	void fit(const Matrix &x, const Matrix &y);		//������̬�������Իع�ѵ��ģ�Ͳ���
	Matrix predict(const Matrix &x);				//����ѵ���õ�ģ�Ͳ�������Ԥ��

	double score(const Matrix &x, const Matrix &y_true);	//����÷֣�Ĭ��Ϊr2_socre

private:
	Matrix extend_x(const Matrix &x);

public:
	Matrix module;
};

