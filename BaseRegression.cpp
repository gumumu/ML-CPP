#include "BaseRegression.h"



BaseRegression::BaseRegression():module(0)
{
}


BaseRegression::~BaseRegression()
{
}

Matrix BaseRegression::predict(const Matrix & x) const
{
	return extend_x(x) * module;
}

double BaseRegression::score(const Matrix & x, const Matrix & y_true) const
{
	Matrix y = predict(x);
	double numerator = (y - y_true).matpow(2).all_sum();
	double denominator = (y - (y.all_sum() / y.getRowNum())).matpow(2).all_sum();
	if (IS_DOUBLE_ZERO(denominator)) return 0.0;
	else return 1.0 - numerator / denominator;
}

Matrix BaseRegression::extend_x(const Matrix & x) const
{
	Matrix ict(x.getRowNum(), 1);
	ict = 1.0;
	return ict.getMergeMatrix(x, false);
}
