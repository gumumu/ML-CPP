#pragma once
#include "BaseRegression.h"
class Ridge:public BaseRegression
{
public:
	Ridge(double alpha = 1.0);
	~Ridge();

	virtual void fit(const Matrix &x, const Matrix &y);		//������ع飨L2���򻯰�����Իع飩ѵ��ģ�Ͳ���

private:
	double alpha;	//��������L2����ǿ��
};

