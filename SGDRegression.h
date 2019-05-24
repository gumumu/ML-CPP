#pragma once
#include "Matrix.h"
#include "BaseRegression.h"
#include <string>

#define CONSTANT_LEARNING_RATE 0
#define TIME_BASED_DECAY 1
#define STEP_DECAY 2
#define EXPONENTIAL_DECAY 3

class SGDRegression:public BaseRegression
{
public:
	SGDRegression(long n_epochs = 50, int batch_size = 1, double tolerance = 0.0, double eta = 0.1, double decay = 0.0, double momentum = 0.0, bool nesterov = false);
	~SGDRegression();

	virtual void fit(const Matrix &x, const Matrix &y);		//��������ݶ��½����Իع�ѵ��ģ�Ͳ���

private:
	double learning_rate_schedule(int iterations, int schedule = TIME_BASED_DECAY);	//����ÿ�ε�����ѧϰ�ʵĺ�����Ϊlearning rate schedule��iterationsΪ��ǰ��������

private:
	long n_epochs;					//�������������������
	double tolerance;				//�ݲ���ݶ�����ģС�ڵ����ݲ�ʱֹͣ������������, �ó���������SGD�˻�Ϊ�����ݶ��½�ʱ����Ч����ÿ��ѡȡȫ��ʵ�������ݶȼ���
	int batch_size;					//������С������������ʵ�������˻�Ϊ�����ݶ��½�������������һʱΪ����ݶ��½�������ΪС�����ݶ��½�
	double eta;						//��ʼѧϰ��,������
	double decay;					//˥���ʣ�����ѧϰ�ʵ�����������
	double momentum;				//���������������ӿ�������ֹ��
	bool nesterov;					//�Ƿ�ʹ��nesterov����ģ��
	bool warm_start;				//�Ƿ���ϴ�ͣ�µĵط�����ѵ��
	std::string penalty;			//����������
};

