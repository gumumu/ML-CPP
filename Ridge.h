#pragma once
#include "BaseRegression.h"
class Ridge:public BaseRegression
{
public:
	Ridge(double alpha = 1.0);
	~Ridge();

	virtual void fit(const Matrix &x, const Matrix &y);		//利用岭回归（L2正则化版的线性回归）训练模型参数

private:
	double alpha;	//超参数，L2正则化强度
};

