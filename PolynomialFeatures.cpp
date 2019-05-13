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
		std::vector<std::vector<int>> ret_vector_list;
		std::vector<int> ret_vector;
		polynomial_combination(features_num, d, ret_vector_list, ret_vector);
		if (interaction_only && d > 1)
		{
			std::vector<std::vector<int>>::iterator it;
			for (it = ret_vector_list.begin(); it != ret_vector_list.end();)
			{
				std::vector<int> ret_v = *it;
				for (int j = 0; j < ret_v.size(); j++)
				{
					if (ret_v[j] == d)
					{
						it = ret_vector_list.erase(it);
						goto end_continue;
					}
				}
				++it;
			end_continue:
				continue;
			}
		}
		all_ret_vector_list.push_back(ret_vector_list);
	}
}

Matrix PolynomialFeatures::transform(const Matrix & x) const
{
	int row_num = x.getRowNum();
	Matrix ret_m(row_num,0);
	for (int i = 0; i < all_ret_vector_list.size(); i++)
	{
		if((!include_bias && i == 0) || (include_bias && i==1)) ret_m = ret_m.getMergeMatrix(x, false);
		else
		{
			std::vector<std::vector<int>> ret_vector_list = all_ret_vector_list[i];
			for (int j = 0; j < ret_vector_list.size(); j++)
			{
				std::vector<int> ret_v = ret_vector_list[j];
				Matrix onecol_m(row_num, 1);
				onecol_m = 1.0;
				for (int k = 0; k < ret_v.size(); k++)
				{
					onecol_m = onecol_m.matpow(x.getSubMatrix(-1, -1, k, k).matpow(ret_v[k]));
				}
				ret_m = ret_m.getMergeMatrix(onecol_m, false);
			}
		}
	}
	return ret_m;
}

void PolynomialFeatures::polynomial_combination(int features_num, int degree, std::vector<std::vector<int>>& ret_vector_list, std::vector<int>& ret_vector) const
{
	if (features_num < 1) return;
	//if features_num==1,获得并加入一个组合，并结束本条线的递归
	if (features_num == 1)
	{
		std::vector<int> ret_v;
		ret_v.insert(ret_v.end(), ret_vector.begin(), ret_vector.end());
		ret_v.push_back(degree);
		ret_vector_list.push_back(ret_v);
		return;
	}
	//if features_num>1,递归features_num - 1, degree - i
	for (int i = degree; i >= 0; i--)
	{
		std::vector<int> ret_v;
		ret_v.insert(ret_v.end(), ret_vector.begin(), ret_vector.end());
		ret_v.push_back(i);
		polynomial_combination(features_num - 1, degree - i, ret_vector_list, ret_v);
	}
}
