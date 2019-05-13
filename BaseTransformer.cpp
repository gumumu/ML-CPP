#include "BaseTransformer.h"



BaseTransformer::BaseTransformer()
{
}


BaseTransformer::~BaseTransformer()
{
}

Matrix BaseTransformer::fit_transform(const Matrix & x)
{
	fit(x);
	return transform(x);
}
