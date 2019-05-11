#include "SBatchTransformer.h"
#include <stdlib.h>
#include <algorithm>



SBatchTransformer::SBatchTransformer()
{
}


SBatchTransformer::~SBatchTransformer()
{
}

std::list<Matrix> SBatchTransformer::transform(Matrix x, Matrix y, int batch_size, bool order)
{
	int n = x.getRowNum();
	if (batch_size <=0 || batch_size > n) throw "batch_size´íÎó";
	int *a = new int[n];

	for (int i = 0; i < n; i++)
		a[i] = i;

	int base_index = 0;
	int radom_size = batch_size;
	if (batch_size > n / 2) {
		base_index = n - batch_size;
		radom_size = n - batch_size;
	}

	for (int i = 0; i < radom_size; i++)
	{
		int w = rand() % (n - i) + i;
		int t = a[i];
		a[i] = a[w];
		a[w] = t;
	}

	if (order && batch_size != 1 && batch_size != n)
	{
		std::sort(a + base_index,a + base_index + batch_size);
	}
	Matrix new_x(x.getSubMatrix(a[base_index], a[base_index], -1, -1));
	Matrix new_y(y.getSubMatrix(a[base_index], a[base_index], -1, -1));
	for (int i = base_index + 1; i < base_index + batch_size; i++)
	{
		new_x = new_x.getMergeMatrix(x.getSubMatrix(a[i], a[i], -1, -1));
		new_y = new_y.getMergeMatrix(y.getSubMatrix(a[i], a[i], -1, -1));
	}
	std::list<Matrix> ret;
	ret.push_back(new_x);
	ret.push_back(new_y);

	return ret;
}
