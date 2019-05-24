#include "Ridge.h"



Ridge::Ridge(double alpha):alpha(alpha)
{
}


Ridge::~Ridge()
{
}

void Ridge::fit(const Matrix & x, const Matrix & y)
{
	Matrix x_ext = extend_x(x);
	Matrix A(x_ext.getColNum());
	A.set(0, 0, 0.0);
	module = ((x_ext.Trans() * x_ext) + (A * alpha)).Inverse()*x_ext.Trans()*y;
	double min_loss = (x_ext* module - y).vector_norm(false) / y.getRowNum();
	std::cout << "<------ fit finished ------>\n" << "min_loss:\n" << min_loss << "\nmodule:\n" << module << "<------ fit finished ------>\n";
}
