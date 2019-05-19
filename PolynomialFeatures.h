#pragma once
#include "Matrix.h"
#include "BaseTransformer.h"
#include <list>

/*
PolynomialFeatures：特征多项式组合 转换器
*/
class PolynomialFeatures:public BaseTransformer
{
public:
	PolynomialFeatures(int degree = 1, bool interaction_only = false, bool include_bias = true);
	~PolynomialFeatures();

	virtual void fit(const Matrix &x);					//通过超参数和x计算得到转换器模型
	virtual Matrix transform(const Matrix &x) const;	//通过模型得到x特征多项式组合转换后矩阵

public:
	std::list<std::list<std::list<int>>> degree_combination_list;		//转换器模型，即所有小于等于degree，大于等于0或者1的多项式组合
	

private:
	int degree;						//默认为1，转换器超参数，最大多项式组合度
	bool interaction_only;			//默认为false，如果指定为True，那么就不会有特征自己和自己结合的项
	bool include_bias;				//默认为true，如果为True的话，那么就会有全部列度为0结合的1那一项。

private:
	//得到度为degree，参数个数为features_num所有的多项式指数组合放入combination_list，比如degree=2，features_num=2，则会有[2,0],[1,1],[0,2]，is_all_zero表示组合combination是否全为0
	//以便识别且将只跟自己组合的多项式删除，默认值为false即不进行删除特征自己和自己结合的项, is_abandon代表本条线路是否丢弃
	void polynomial_combination(int features_num, int degree, bool interaction_only, std::list<std::list<int>>& combination_list, std::list<int>& combination, bool is_abandon = false) const;
};

