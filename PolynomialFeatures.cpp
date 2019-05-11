#include "PolynomialFeatures.h"



PolynomialFeatures::PolynomialFeatures(int degree, bool interaction_only, bool include_bias):degree(degree),interaction_only(interaction_only),include_bias(include_bias)
{
}


PolynomialFeatures::~PolynomialFeatures()
{
}

Matrix PolynomialFeatures::transform(const Matrix & x) const
{
	int row_num = x.getRowNum();
	Matrix ret_m(row_num,0);
	for (int d = include_bias ? 0 : 1; d <= degree; d++)
	{
		std::vector<std::vector<int>> ret_vector_list;
		std::vector<int> ret_vector;
		polynomial_combination(x.getColNum(), d, ret_vector_list, ret_vector);
		for (int i = 0; i < ret_vector_list.size(); i++)
		{
			std::vector<int> ret_v = ret_vector_list[i];
			Matrix onecol_m(row_num, 1);
			onecol_m = 1.0;
			for (int j = 0; j < ret_v.size(); j++)
			{
				if (interaction_only && d > 1 && ret_v[j] == d) goto not_merge;
				onecol_m = onecol_m.matpow(x.getSubMatrix(-1, -1, j, j).matpow(ret_v[j]));
			}
			ret_m = ret_m.getMergeMatrix(onecol_m, false);
		not_merge:
			continue;
		}
	}
	return ret_m;
}

void PolynomialFeatures::polynomial_combination(int features_num, int degree, std::vector<std::vector<int>>& ret_vector_list, std::vector<int>& ret_vector) const
{
	if (features_num < 1) return;
	if (features_num == 1)
	{
		std::vector<int> ret_v;
		ret_v.insert(ret_v.end(), ret_vector.begin(), ret_vector.end());
		ret_v.push_back(degree);
		ret_vector_list.push_back(ret_v);
		return;
	}
	for (int i = degree; i >= 0; i--)
	{
		std::vector<int> ret_v;
		ret_v.insert(ret_v.end(), ret_vector.begin(), ret_vector.end());
		ret_v.push_back(i);
		polynomial_combination(features_num - 1, degree - i, ret_vector_list, ret_v);
	}
}
