#pragma once
#include "Matrix.h"

#define CONSTANT_LEARNING_RATE 0
#define TIME_BASED_DECAY 1
#define STEP_DECAY 2
#define EXPONENTIAL_DECAY 3

class SGDRegression
{
public:
	SGDRegression(double eta = 0.1, double decay = 0.0, double momentum = 0.0, bool nesterov = false);
	~SGDRegression();

	void fit(const Matrix &x, const Matrix &y, long n_epochs = 50, int batch_size = 1, double tolerance_ = 0.0);		//��������ݶ��½����Իع�ѵ��ģ�Ͳ���
	Matrix predict(const Matrix &x);				//����ѵ���õ�ģ�Ͳ�������Ԥ��
	double score(const Matrix &x, const Matrix &y_true);	//����÷֣�Ĭ��Ϊr2_socre

private:
	Matrix extend_x(const Matrix &x);				//��չ���󣬼�����ȫ��ֵΪ1.0�ĵ���һ�У�Ϊ�˺ͽؾ��Ӧ
	double learning_rate_schedule(int iterations, int schedule = TIME_BASED_DECAY);	//����ÿ�ε�����ѧϰ�ʵĺ�����Ϊlearning rate schedule��iterationsΪ��ǰ��������

public:
	Matrix module;					//ģ�Ͳ�������ѧϰ
	long n_epochs;					//�������������������
	double tolerance;				//�ݲ���ݶ�����ģС�ڵ����ݲ�ʱֹͣ������������, �ó���������SGD�˻�Ϊ�����ݶ��½�ʱ����Ч����ÿ��ѡȡȫ��ʵ�������ݶȼ���

	double eta;						//��ʼѧϰ��,������
	double decay;					//˥���ʣ�����ѧϰ�ʵ�����������
	double momentum;				//���������������ӿ�������ֹ��
	bool nesterov;					//�Ƿ�ʹ��nesterov����ģ��
};
