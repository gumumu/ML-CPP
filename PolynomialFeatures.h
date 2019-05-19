#pragma once
#include "Matrix.h"
#include "BaseTransformer.h"
#include <list>

/*
PolynomialFeatures����������ʽ��� ת����
*/
class PolynomialFeatures:public BaseTransformer
{
public:
	PolynomialFeatures(int degree = 1, bool interaction_only = false, bool include_bias = true);
	~PolynomialFeatures();

	virtual void fit(const Matrix &x);					//ͨ����������x����õ�ת����ģ��
	virtual Matrix transform(const Matrix &x) const;	//ͨ��ģ�͵õ�x��������ʽ���ת�������

public:
	std::list<std::list<std::list<int>>> degree_combination_list;		//ת����ģ�ͣ�������С�ڵ���degree�����ڵ���0����1�Ķ���ʽ���
	

private:
	int degree;						//Ĭ��Ϊ1��ת������������������ʽ��϶�
	bool interaction_only;			//Ĭ��Ϊfalse�����ָ��ΪTrue����ô�Ͳ����������Լ����Լ���ϵ���
	bool include_bias;				//Ĭ��Ϊtrue�����ΪTrue�Ļ�����ô�ͻ���ȫ���ж�Ϊ0��ϵ�1��һ�

private:
	//�õ���Ϊdegree����������Ϊfeatures_num���еĶ���ʽָ����Ϸ���combination_list������degree=2��features_num=2�������[2,0],[1,1],[0,2]��is_all_zero��ʾ���combination�Ƿ�ȫΪ0
	//�Ա�ʶ���ҽ�ֻ���Լ���ϵĶ���ʽɾ����Ĭ��ֵΪfalse��������ɾ�������Լ����Լ���ϵ���, is_abandon��������·�Ƿ���
	void polynomial_combination(int features_num, int degree, bool interaction_only, std::list<std::list<int>>& combination_list, std::list<int>& combination, bool is_abandon = false) const;
};

