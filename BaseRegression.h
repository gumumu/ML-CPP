#pragma once
#include "Matrix.h"
class BaseRegression
{
public:
	BaseRegression();
	~BaseRegression();

	virtual Matrix predict(const Matrix &x) const;				//����ѵ���õ�ģ�Ͳ�������Ԥ��
	virtual double score(const Matrix &x, const Matrix &y_true) const;	//����÷֣�Ĭ��Ϊr2_socre

protected:
	virtual Matrix extend_x(const Matrix &x) const;

public:
	Matrix module;
};

