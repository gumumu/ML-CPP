#pragma once
#include "Matrix.h"
#include "BaseTransformer.h"

/*
SBatchTransformer������Ӿ���ȡbatch_size��С��batch�Ӿ��� ת����
*/
class SBatchTransformer:public BaseTransformer
{
public:
	SBatchTransformer(int batch_size = 1, bool order = false);
	~SBatchTransformer();

	virtual void fit(const Matrix &x);						//ͨ����������x����õ�ת����ģ��batch_indexs
	virtual Matrix transform(const Matrix &x) const;		//ͨ��batch_indexsģ�͵õ�x��batch����

public:
	std::vector<int> batch_indexs;							//ģ�ͣ���һ�����batch_size��С����Ŷ���
	int base_index;											//ģ�Ͳ��������batch_size��С����Ŷ�����batch_indexs����ʼλ��

private:
	int batch_size;								//ת������������batch�Ĵ�С
	bool order;									//�Ƿ���ԭ����˳��õ���Ŷ���
};

