#pragma once
#include "Matrix.h"
#include <list>
class SBatchTransformer
{
public:
	SBatchTransformer();
	~SBatchTransformer();

	std::list<Matrix> transform(Matrix x, Matrix y, int batch_size = 1, bool order = false);
};

