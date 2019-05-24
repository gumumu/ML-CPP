#pragma once
#include "Matrix.h"
class BaseRegression
{
public:
	BaseRegression();
	~BaseRegression();

	//����ӿ�
	virtual void fit(const Matrix &x, const Matrix &y) = 0;

	//�ṩĬ��ʵ�ֵ��麯��
	virtual Matrix predict(const Matrix &x) const;				//����ѵ���õ�ģ�Ͳ�������Ԥ��
	virtual double score(const Matrix &x, const Matrix &y_true) const;	//����÷֣�Ĭ��Ϊr2_socre

protected:
	//�ṩĬ��ʵ�ֵ��麯��
	virtual Matrix extend_x(const Matrix &x) const;

public:
	//ģ�Ͳ���
	Matrix module;
};

