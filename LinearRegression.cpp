#include "LinearRegression.h"



LinearRegression::LinearRegression():module(0)
{
}


LinearRegression::~LinearRegression()
{
}

void LinearRegression::fit(const Matrix &x, const Matrix &y)
{
	Matrix x_ext = extend_x(x);
	module = (x_ext.Trans()*x_ext).Inverse()*x_ext.Trans()*y;
	double min_loss = (x_ext* module - y).vector_norm(false)/y.getRowNum();
	std::cout << "<------ fit finished ------>\n" << "min_loss:\n" << min_loss << "\nmodule:\n" << module << "<------ fit finished ------>\n";
}

Matrix LinearRegression::predict(const Matrix & x)
{
	Matrix x_ext = extend_x(x);
	return x_ext*module;
}

double LinearRegression::score(const Matrix & x, const Matrix & y_true)
{
	Matrix y = predict(x);
	double numerator = (y - y_true).matpow(2).all_sum();
	double denominator = (y - (y.all_sum() / y.getRowNum())).matpow(2).all_sum();
	if (IS_DOUBLE_ZERO(denominator)) return 0.0;
	else return 1.0 - numerator / denominator;
}

Matrix LinearRegression::extend_x(const Matrix & x)
{
	Matrix x_ext(x.getRowNum(), x.getColNum() + 1);
	for (int i = 0; i < x_ext.getRowNum(); i++)
	{
		for (int j = 0; j < x_ext.getColNum(); j++)
		{
			if (j == 0)
			{
				x_ext.set(i, j, 1.0);
			}
			else
			{
				x_ext.set(i, j, x.get(i, j - 1));
			}
		}
	}
	return x_ext;
}
