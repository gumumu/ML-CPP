#include "LinearRegression.h"



LinearRegression::LinearRegression()
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