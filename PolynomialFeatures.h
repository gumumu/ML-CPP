#pragma once
#include "Matrix.h"
#include <vector>
class PolynomialFeatures
{
public:
	PolynomialFeatures(int degree = 1, bool interaction_only = false, bool include_bias = true);
	~PolynomialFeatures();

	Matrix transform(const Matrix &x) const;

public:
	int degree;
	bool interaction_only;
	bool include_bias;

private:
	void polynomial_combination(int features_num, int degree, std::vector<std::vector<int>>& ret_vector_list, std::vector<int>& ret_vector) const;
};

