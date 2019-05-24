#pragma once
#include "BaseTransformer.h"
class StandardScaler :
	public BaseTransformer
{
public:
	StandardScaler(bool with_mean = true, bool with_std = true);
	~StandardScaler();

	virtual void fit(const Matrix &x) ;						//实现接口：通过超参数和x计算得到转换器模型，即对于x每一个特征计算均值和标准差
	virtual Matrix transform(const Matrix &x) const;		//实现接口：通过转换器模型模型得到x转换后的矩阵，即对于每一个元素，减去相应特征的均值并除去标准差

private:
	bool with_mean;											//超参数，是否化为均值为0，即是否减去均值
	bool with_std;											//超参数，是否化为方差为1，即是否除去标准差

public:
	Matrix mean;											//模型参数，每一个特征的均值
	Matrix std;												//模型参数，每一个特征的标准差
};

