#pragma once
#include "BaseTransformer.h"
class StandardScaler :
	public BaseTransformer
{
public:
	StandardScaler(bool with_mean = true, bool with_std = true);
	~StandardScaler();

	virtual void fit(const Matrix &x) ;						//ʵ�ֽӿڣ�ͨ����������x����õ�ת����ģ�ͣ�������xÿһ�����������ֵ�ͱ�׼��
	virtual Matrix transform(const Matrix &x) const;		//ʵ�ֽӿڣ�ͨ��ת����ģ��ģ�͵õ�xת����ľ��󣬼�����ÿһ��Ԫ�أ���ȥ��Ӧ�����ľ�ֵ����ȥ��׼��

private:
	bool with_mean;											//���������Ƿ�Ϊ��ֵΪ0�����Ƿ��ȥ��ֵ
	bool with_std;											//���������Ƿ�Ϊ����Ϊ1�����Ƿ��ȥ��׼��

public:
	Matrix mean;											//ģ�Ͳ�����ÿһ�������ľ�ֵ
	Matrix std;												//ģ�Ͳ�����ÿһ�������ı�׼��
};

