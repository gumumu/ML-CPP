#include "PolynomialFeatures.h"



PolynomialFeatures::PolynomialFeatures(int degree, bool interaction_only, bool include_bias):degree(degree),interaction_only(interaction_only),include_bias(include_bias)
{
}


PolynomialFeatures::~PolynomialFeatures()
{
}

void PolynomialFeatures::fit(const Matrix & x)
{
	int features_num = x.getColNum();
	for (int d = include_bias ? 0 : 1; d <= degree; d++)
	{
		std::list<std::list<int>> combination_list;
		std::list<int> combination;
		polynomial_combination(features_num, d, interaction_only,  combination_list, combination);
		degree_combination_list.push_back(combination_list);
	}
}

Matrix PolynomialFeatures::transform(const Matrix & x) const
{
	int row_num = x.getRowNum();
	int col_num = 0;
	for (std::list<std::list<std::list<int>>>::const_iterator it_first = degree_combination_list.begin(); it_first != degree_combination_list.end(); ++it_first)
	{
		col_num += ((std::list<std::list<int>>)*it_first).size();
	
	}

	Matrix ret_m(row_num, col_num);
	int i = 0;
	int index = 0;
	for (std::list<std::list<std::list<int>>>::const_iterator it_first = degree_combination_list.begin(); it_first != degree_combination_list.end(); ++it_first,++i)
	{
		if ((!include_bias && i == 0) || (include_bias && i == 1)) {
			ret_m.set_row_col(x, -1, -1, index, index + x.getColNum() - 1);
			index += x.getColNum();
		}
		else
		{
			std::list<std::list<int>> combination_list = *it_first;
			for (std::list<std::list<int>>::const_iterator it_second = combination_list.begin(); it_second != combination_list.end(); ++it_second)
			{
				std::list<int> combination = *it_second;		
				Matrix pow_m(1, combination.size());
				int k = 0;
				for (std::list<int>::const_iterator it_third = combination.begin(); it_third != combination.end(); ++it_third,++k)
				{
					pow_m.set(0, k, *it_third);
				}
				ret_m.set_row_col(x.matpow(pow_m).product(1), -1, -1, index, index);
				index++;
			}
		}
	}
	return ret_m;
}

void PolynomialFeatures::polynomial_combination(int features_num, int degree, bool interaction_only, std::list<std::list<int>>& combination_list, std::list<int>& combination, bool is_abandon) const
{
	if (features_num < 1) return;
	//if features_num==1,获得并加入一个组合，并结束本条线的递归
	if (features_num == 1)
	{
		if (interaction_only && (is_abandon || degree > 1)) return;							//丢弃自己和自己组合的项
		std::list<int> one_combination(combination);
		one_combination.push_back(degree);
		combination_list.push_back(one_combination);
		return;
	}
	//if features_num>1,递归features_num - 1, degree - i
	for (int i = degree; i >= 0; i--)
	{
		if (interaction_only && (is_abandon || i > 1)) polynomial_combination(features_num - 1, degree - i, interaction_only, combination_list, combination, true); //丢弃自己和自己组合的项
		else
		{
			std::list<int> one_combination(combination);
			one_combination.push_back(i);
			polynomial_combination(features_num - 1, degree - i, interaction_only, combination_list, one_combination);
		}
	}
}
