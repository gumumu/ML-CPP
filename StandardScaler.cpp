#include "StandardScaler.h"



StandardScaler::StandardScaler(bool with_mean, bool with_std):with_mean(with_mean), with_std(with_std)
{
}


StandardScaler::~StandardScaler()
{
}

void StandardScaler::fit(const Matrix & x)
{
	mean = x.sum() / x.getRowNum();
	std = (((x - mean).matpow(2).sum()) / x.getRowNum()).matpow(0.5);
}

Matrix StandardScaler::transform(const Matrix & x) const
{
	if (with_mean && with_std)
	{
		return (x - mean) / std;
	}
	else if(with_mean)
	{
		return (x - mean);
	}
	else if (with_std)
	{
		return (x / std);
	}
	else
	{
		return x;
	}
}
