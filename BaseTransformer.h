#pragma once
#include "Matrix.h"
/*
�ӿ��ࣺ����ת���������ӿ�
*/
class BaseTransformer
{
public:
	BaseTransformer();
	~BaseTransformer();

	virtual void fit(const Matrix &x) = 0;					//�ӿڣ�ͨ����������x����õ�ת����ģ��
	virtual Matrix transform(const Matrix &x) const = 0;	//�ӿڣ�ͨ��ת����ģ��ģ�͵õ�xת����ľ���
	virtual Matrix fit_transform(const Matrix &x);		//�ӿڣ�fit+transform
};

