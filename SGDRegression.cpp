#include "SGDRegression.h"
#include "SBatchTransformer.h"
#include <stdlib.h>



SGDRegression::SGDRegression(double eta, double decay, double momentum, bool nesterov):eta(eta), decay(decay), momentum(momentum), nesterov(nesterov), n_epochs(50), tolerance(0.0)
{
}


SGDRegression::~SGDRegression()
{
}

void SGDRegression::fit(const Matrix &x, const Matrix &y, long epochs , int batch_size, double tolerance_)
{
	this->n_epochs = epochs;
	int m = x.getRowNum();
	Matrix x_ext = extend_x(x);

	if(m == batch_size) this->tolerance = tolerance_;
	int batch_num = ceil((1.0*m) / (1.0*batch_size));
	module = Matrix(x_ext.getColNum(), 1);
	Matrix module_test(x_ext.getColNum(), 1);

	Matrix gradients_momentum(x_ext.getColNum(), 1);

	srand((unsigned int)time(NULL));
	SBatchTransformer sb(batch_size);

	double min_loss = DBL_MAX;
	for (long i = 0; i < n_epochs; i++)
	{
		for (int j = 0; j < batch_num; j++)
		{
			Matrix xi_random = sb.fit_transform(x_ext);
			Matrix yi_randow = sb.transform(y);

			double leta = learning_rate_schedule(i*batch_num + j);
			Matrix gradients(0);
			if (nesterov)  //nesterov动量梯度下降
			{
				Matrix module_test_after = module_test - gradients_momentum * momentum * leta;
				gradients = (xi_random.Trans()*(xi_random*module_test_after - yi_randow))*(2.0/xi_random.getRowNum());
			}
			else  //momentum动量梯度下降
			{
				gradients = (xi_random.Trans()*(xi_random*module_test - yi_randow))*(2.0 /xi_random.getRowNum());
			}
			gradients_momentum = gradients_momentum * momentum + gradients;
			double gradients_norm = gradients_momentum.vector_norm();
			if (gradients_norm <= tolerance) goto fit_end;
			module_test = module_test - gradients_momentum * leta;

			double loss = (x_ext* module_test - y).vector_norm(false)/y.getRowNum();
			std::cout << i * batch_num + j << ": loss(" << loss << ")  eta(" << leta << ")  gradients(" << gradients_norm << ")" << std::endl;
			if (loss < min_loss)
			{
				min_loss = loss;
				module = module_test;
			}
		}	
	}
	fit_end:
	std::cout << "<------ fit finished ------>\n" << "min_loss:\n" << min_loss << "\nmodule:\n" << module << "<------ fit finished ------>\n";
}

double SGDRegression::learning_rate_schedule(int iterations, int schedule)
{
	double leta = eta;

	switch (schedule)
	{
	case CONSTANT_LEARNING_RATE:
		break;
	case TIME_BASED_DECAY:
		leta = eta / (1 + decay * iterations);
		break;
	case EXPONENTIAL_DECAY:
		leta = eta * exp(-decay * iterations);
		break;
	default:
		break;
	}

	return leta;
}

