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

	void fit(const Matrix &x, const Matrix &y, long n_epochs = 50, int batch_size = 1, double tolerance_ = 0.0);		//利用随机梯度下降线性回归训练模型参数
	Matrix predict(const Matrix &x);				//利用训练好的模型参数进行预测
	double score(const Matrix &x, const Matrix &y_true);	//计算得分，默认为r2_socre

private:
	Matrix extend_x(const Matrix &x);				//扩展矩阵，即加上全部值为1.0的到第一列，为了和截距对应
	double learning_rate_schedule(int iterations, int schedule = TIME_BASED_DECAY);	//决定每次迭代的学习率的函数称为learning rate schedule，iterations为当前迭代次数

public:
	Matrix module;					//模型参数，待学习
	long n_epochs;					//迭代最大轮数，超参数
	double tolerance;				//容差，当梯度向量模小于等于容差时停止迭代，超参数, 该超参数仅当SGD退化为批量梯度下降时才有效，即每次选取全部实例进行梯度计算

	double eta;						//初始学习率,超参数
	double decay;					//衰减率，用于学习率调整，超参数
	double momentum;				//动量，超参数，加快收敛防止振荡
	bool nesterov;					//是否使用nesterov动量模型
};

