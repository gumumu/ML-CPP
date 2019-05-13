#pragma once
#include "Matrix.h"
#include "BaseTransformer.h"

/*
SBatchTransformer：随机从矩阵取batch_size大小的batch子矩阵 转换器
*/
class SBatchTransformer:public BaseTransformer
{
public:
	SBatchTransformer(int batch_size = 1, bool order = false);
	~SBatchTransformer();

	virtual void fit(const Matrix &x);						//通过超参数和x计算得到转换器模型batch_indexs
	virtual Matrix transform(const Matrix &x) const;		//通过batch_indexs模型得到x的batch矩阵

public:
	std::vector<int> batch_indexs;							//模型，即一个随机batch_size大小的序号队列
	int base_index;											//模型参数，随机batch_size大小的序号队列在batch_indexs的起始位置

private:
	int batch_size;								//转换器超参数，batch的大小
	bool order;									//是否按照原来的顺序得到序号队列
};

