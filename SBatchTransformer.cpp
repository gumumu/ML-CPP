#include "SBatchTransformer.h"
#include <stdlib.h>
#include <algorithm>



SBatchTransformer::SBatchTransformer(int batch_size, bool order):batch_size(batch_size),order(order)
{
}


SBatchTransformer::~SBatchTransformer()
{
}

void SBatchTransformer::fit(const Matrix & x)
{
	int n = x.getRowNum();
	if (batch_size < 0 || batch_size > n) throw "batch_size´íÎó";
	batch_indexs.resize(n);
	for (int i = 0; i < n; i++)	batch_indexs[i] = i;

	base_index = 0;
	int radom_size = batch_size;
	if (batch_size > n / 2) {
		base_index = n - batch_size;
		radom_size = n - batch_size;
	}
	for (int i = 0; i < radom_size; i++)
	{
		int w = rand() % (n - i) + i;
		int t = batch_indexs[i];
		batch_indexs[i] = batch_indexs[w];
		batch_indexs[w] = t;
	}
	if (order && batch_size > 1 && batch_size != n)
	{
		std::sort(batch_indexs.begin() + base_index, batch_indexs.begin() + base_index + batch_size);
	}
}

Matrix SBatchTransformer::transform(const Matrix & x) const
{
	Matrix ret_m(0, x.getColNum());
	for (int i = base_index; i < base_index + batch_size; i++)
	{
		ret_m = ret_m.getMergeMatrix(x.getSubMatrix(batch_indexs[i], batch_indexs[i], -1, -1));
	}
	return ret_m;
}
