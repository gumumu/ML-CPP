#include "Matrix.h"
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

Matrix::Matrix()
{
	rowNum = 0;
	colNum = 0;
	item = new double[0];
}

Matrix::Matrix(int m, int n)
{
	if (m < 0 || n < 0)
	{
		throw "Matrix:�����С����Ϊ��";
	}
	rowNum = m;
	colNum = n;
	item = new double[m*n];
	for (int i = 0; i < m*n; i++) 
	{
		item[i] = 0;
	}
}

Matrix::Matrix(int n)
{
	if (n < 0)
	{
		throw "Matrix:�����С����Ϊ��";
	}
	rowNum = n;
	colNum = n;
	item = new double[n*n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				item[i*n + j] = 1.0;
			else
				item[i*n + j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix &M)
{
	rowNum = M.rowNum;
	colNum = M.colNum;
	item = new double[rowNum*colNum];
	for (int i = 0; i < rowNum*colNum; i++)
	{
		item[i] = M.item[i];
	}
}

Matrix::Matrix(double * items, int m, int n)
{
	if (m < 0 || n < 0)
	{
		throw "Matrix:�����С����Ϊ��";
	}
	rowNum = m;
	colNum = n;
	item = new double[m*n];
	for (int i = 0; i < rowNum*colNum; i++)
	{
		item[i] = items[i];
	}
}

Matrix::~Matrix()
{
	delete[] item;
}

Matrix Matrix::FromFile(std::string file)
{
	ifstream read(file);
	if (!read.is_open())
	{
		throw "Matrix::δ�ܴ��ļ�";
	}
	int rows = 0;
	string line;
	vector<double> nums;
	while (getline(read, line))
	{
		istringstream record(line);
		double num = 0.0;
		while (record >> num)  nums.push_back(num);
		rows++;
	}
	return Matrix(&(*nums.begin()), rows, nums.size() / rows);
}

int Matrix::getRowNum() const
{
	return rowNum;
}

int Matrix::getColNum() const
{
	return colNum;
}

Matrix Matrix::Trans() const
{
	Matrix m(colNum,rowNum);
	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			m.item[i*rowNum + j] = item[j*colNum + i];
		}
	}
	return m;
}

double Matrix::get(int i, int j) const
{
	if (i >= rowNum || j >= colNum || i<0 || j<0)
	{
		throw "get����Խ��";
	}
	return item[i*colNum + j];
}

void Matrix::set(int i, int j, double val)
{
	if (i >= rowNum || j >= colNum || i < 0 || j < 0)
	{
		throw "set����Խ��";
	}
	item[i*colNum + j] = val;
}

void Matrix::set_row_col(const Matrix & m, int row_low, int row_up, int col_low, int col_up)
{
	int row_low_index = row_low < 0 ? 0 : row_low % rowNum;
	int row_up_index = row_up < 0 ? rowNum - 1 : row_up % rowNum;
	int col_low_index = col_low < 0 ? 0 : col_low % colNum;
	int col_up_index = col_up < 0 ? colNum - 1 : col_up % colNum;
	
	if (m.rowNum*m.colNum != (row_up_index - row_low_index + 1)*(col_up_index - col_low_index + 1))
	{
		throw "�������ã�Ԫ������һ��";
	}
	int index = 0;
	for (int i = row_low_index; i <= row_up_index; i++)
	{
		for (int j = col_low_index; j <= col_up_index; j++, index++)
		{
			item[i*colNum + j] = m.item[index];
		}
	}
}

Matrix Matrix::getSubMatrix(int row_low, int row_up, int col_low, int col_up) const
{
	int row_low_index = row_low < 0 ? 0 : row_low % rowNum;
	int row_up_index = row_up < 0 ? rowNum-1 : row_up % rowNum;
	int col_low_index = col_low < 0 ? 0 : col_low % colNum;
	int col_up_index = col_up < 0 ? colNum - 1 : col_up % colNum;
	
	Matrix m_ret(row_up_index - row_low_index + 1, col_up_index - col_low_index + 1);
	int index = 0;
	for (int i = row_low_index; i <= row_up_index; i++)
	{
		for (int j = col_low_index; j <= col_up_index; j++, index++)
		{
			m_ret.item[index] = item[i*colNum + j];
		}
	}
	return m_ret;
}

Matrix Matrix::getMergeMatrix(const Matrix & second, bool is_v) const
{
	if (is_v)
	{
		if (colNum != second.colNum)
		{
			throw "������һ�²��ɴ�ֱ�ϲ�";
		}
		Matrix m_ret(rowNum + second.rowNum, colNum);
		for (int i = 0; i < m_ret.rowNum*m_ret.colNum; i++)
		{
			m_ret.item[i] = i < rowNum*colNum ? item[i] : second.item[i - rowNum*colNum];
		}
		return m_ret;
	}
	else
	{
		if (rowNum != second.rowNum)
		{
			throw "������һ�²���ˮƽ�ϲ�";
		}
		Matrix m_ret(rowNum, colNum + second.colNum);
		int index = 0;
		for (int i = 0; i < m_ret.rowNum; i++)
		{
			for (int j = 0; j < m_ret.colNum; j++, index++)
			{
				if (j < colNum)
				{
					m_ret.item[index] = item[i*colNum + j];
				}
				else
				{
					m_ret.item[index] = second.item[i*second.colNum + j - colNum];
				}
			}
		}
		return m_ret;
	}
}

Matrix Matrix::operator+(const Matrix & m) const
{
	Matrix m_ret(rowNum, colNum);
	if (m.rowNum == rowNum && m.colNum == colNum)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] + m.item[i];
		}
	}
	else if (m.rowNum == rowNum && m.colNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] + m.item[i/colNum];
		}
	}
	else if (m.colNum == colNum && m.rowNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] + m.item[i%colNum];
		}
	}
	else
	{
		throw "���ɼ�";
	}
	return m_ret;
}

Matrix Matrix::operator-(const Matrix & m) const
{
	Matrix m_ret(rowNum, colNum);
	if (m.rowNum == rowNum && m.colNum == colNum)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] - m.item[i];
		}
	}
	else if (m.rowNum == rowNum && m.colNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] - m.item[i / colNum];
		}
	}
	else if (m.colNum == colNum && m.rowNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] - m.item[i%colNum];
		}
	}
	else
	{
		throw "���ɼ�";
	}
	return m_ret;
}

Matrix Matrix::operator+(const double f) const
{
	Matrix m_ret(rowNum, colNum);
	for (int i = 0; i < rowNum*colNum; i++)
	{
		m_ret.item[i] = item[i] + f;
	}
	return m_ret;
}

Matrix Matrix::operator-(const double f) const
{
	Matrix m_ret(rowNum, colNum);
	for (int i = 0; i < rowNum*colNum; i++)
	{
		m_ret.item[i] = item[i] - f;
	}
	return m_ret;
}

Matrix Matrix::operator*(const Matrix & m) const
{
	if (m.rowNum != colNum)
	{
		throw "���ɳ�";
	}
	Matrix m_ret(rowNum, m.colNum);
	for (int i = 0; i < rowNum; i++)
	{
		for (int j = 0; j < m.colNum; j++)
		{
			double sum_col_row = 0;
			for (int k = 0; k < colNum; k++)
			{
				sum_col_row += item[i*colNum + k] * m.item[k*m.colNum + j];
			}
			m_ret.item[i*m.colNum + j] = sum_col_row;
		}
	}
	return m_ret;
}

Matrix Matrix::operator*(const double f) const
{
	Matrix m_ret(rowNum, colNum);
	for (int i = 0; i < rowNum*colNum; i++)
	{
		m_ret.item[i] = item[i]*f;
	}
	return m_ret;
}

Matrix Matrix::operator/(const double f) const
{
	if (IS_DOUBLE_ZERO(f))
	{
		throw "����Ϊ0�����ɳ�";
	}
	Matrix m_ret(rowNum, colNum);
	for (int i = 0; i < rowNum*colNum; i++)
	{
		m_ret.item[i] = item[i] / f;
	}
	return m_ret;
}

Matrix Matrix::operator/(const Matrix & m) const
{
	Matrix m_ret(rowNum, colNum);
	if (m.rowNum == rowNum && m.colNum == colNum)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			if(IS_DOUBLE_ZERO(m.item[i])) throw "����Ϊ0�����ɳ�";
			m_ret.item[i] = item[i] / m.item[i];
		}
	}
	else if (m.rowNum == rowNum && m.colNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			if (IS_DOUBLE_ZERO(m.item[i / colNum])) throw "����Ϊ0�����ɳ�";
			m_ret.item[i] = item[i] / m.item[i / colNum];
		}
	}
	else if (m.colNum == colNum && m.rowNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			if (IS_DOUBLE_ZERO(m.item[i%colNum])) throw "����Ϊ0�����ɳ�";
			m_ret.item[i] = item[i] - m.item[i%colNum];
		}
	}
	else
	{
		throw "���ɳ�";
	}
	return m_ret;
}

Matrix & Matrix::operator=(const Matrix & m)
{
	colNum = m.colNum;
	rowNum = m.rowNum;
	if (item != nullptr) delete[] item;
	item = new double[colNum*rowNum];
	for (int i = 0; i < colNum*rowNum; i++)
	{
		item[i] = m.item[i];
	}
	return *this;
}

Matrix & Matrix::operator=(const double f)
{
	for (int i = 0; i < rowNum*colNum; i++)
	{
		item[i] = f;
	}
	return *this;
}

Matrix Matrix::Inverse() const
{
	if (rowNum != colNum)
	{
		throw "������";
	}
	Matrix m_ret(rowNum);
	Matrix m_source(*this);
	//�ӵ�һ�е����һ�л�Ϊ�Խ�Ԫ��Ϊ1�ĵ�λ����
	for (int i = 0; i < colNum; i++)
	{
		double pivot = 0.0;
		//�����жԽ�Ԫ�ؿ�ʼ�ҵ�һ������Ԫ�أ��������жԻ�
		for (int j = i; j < rowNum; j++)
		{
			if (!IS_DOUBLE_ZERO(m_source.item[j*colNum + i]))
			{
				pivot = m_source.item[j*colNum + i];
				m_source.RowSwap(j, i);
				m_ret.RowSwap(j, i);
				break;
			}
		}
		//���û�У������Ϊ������󲻿���
		if (IS_DOUBLE_ZERO(pivot))
		{
			throw "������";
		}
		//���Խ�Ԫ�ػ�Ϊ1
		double multiply = 1.0 / pivot;
		m_source.RowSwap(i, -1, multiply);
		m_ret.RowSwap(i, -1, multiply);

		//��������0�ǶԽ�Ԫ�ػ�Ϊ0
		for (int j = 0; j < rowNum; j++)
		{
			if (!IS_DOUBLE_ZERO(m_source.item[j*colNum + i]) && j!=i)
			{
				double multiply = -1* m_source.item[j*colNum + i];
				m_source.RowSwap(i, j, multiply);
				m_ret.RowSwap(i, j, multiply);
			}
		}
	}
	return m_ret;
}

Matrix Matrix::Reciprocal() const
{
	Matrix m_ret(rowNum, colNum);
	for (int i = 0; i < rowNum*colNum; i++)
	{
		if(IS_DOUBLE_ZERO(item[i])) throw "��Ԫ��Ϊ0�����ɵ�";
		m_ret.item[i] = 1/item[i];
	}
	return m_ret;
}

double Matrix::vector_norm(bool is_sqrt) const
{
	if (colNum != 1 && rowNum != 1)
	{
		throw "�������������ɼ���ģ";
	}
	double norm = 0.0;
	for (int i = 0; i < rowNum*colNum; i++)
	{
		norm += pow(item[i], 2);
	}
	if(is_sqrt) norm = sqrt(norm);
	return norm;
}

Matrix Matrix::sum(int axis) const
{
	if (axis == 1)
	{
		Matrix ret_m(rowNum, 1);
		for (int i = 0; i < rowNum; i++)
		{
			double one_row_sum = 0.0;
			for (int j = 0; j < colNum; j++)
			{
				one_row_sum += item[i*colNum + j];
			}
			ret_m.item[i] = one_row_sum;
		}
		return ret_m;
	}
	else
	{
		Matrix ret_m(1, colNum);
		for (int i = 0; i < colNum; i++)
		{
			double one_col_sum = 0.0;
			for (int j = 0; j < rowNum; j++)
			{
				one_col_sum += item[j*colNum + i];
			}
			ret_m.item[i] = one_col_sum;
		}
		return ret_m;
	}
}

double Matrix::all_sum() const
{
	double sum = 0.0;
	for (int i = 0; i < rowNum*colNum; i++)
	{
		sum += item[i];
	}
	return sum;
}

Matrix Matrix::product(int axis) const
{
	if (axis == 1)
	{
		Matrix ret_m(rowNum, 1);
		for (int i = 0; i < rowNum; i++)
		{
			double one_row_product = 1.0;
			for (int j = 0; j < colNum; j++)
			{
				one_row_product *= item[i*colNum + j];
			}
			ret_m.item[i] = one_row_product;
		}
		return ret_m;
	}
	else
	{
		Matrix ret_m(1, colNum);
		for (int i = 0; i < colNum; i++)
		{
			double one_col_product = 1.0;
			for (int j = 0; j < rowNum; j++)
			{
				one_col_product *= item[j*colNum + i];
			}
			ret_m.item[i] = one_col_product;
		}
		return ret_m;
	}
}

double Matrix::all_product() const
{
	double product = 1.0;
	for (int i = 0; i < rowNum*colNum; i++)
	{
		product *= item[i];
	}
	return product;
}

Matrix Matrix::matpow(double p) const
{
	Matrix m_ret(rowNum, colNum);
	for (int i = 0; i < rowNum*colNum; i++)
	{
		m_ret.item[i] = pow(item[i], p);
	}
	return m_ret;
}

Matrix Matrix::matpow(int p) const
{
	Matrix m_ret(rowNum, colNum);
	for (int i = 0; i < rowNum*colNum; i++)
	{
		m_ret.item[i] = pow(item[i],p);
	}
	return m_ret;
}

Matrix Matrix::matpow(const Matrix & m, bool int_pow) const
{
	Matrix m_ret(rowNum, colNum);
	if (m.rowNum == rowNum && m.colNum == colNum)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			if(int_pow)	m_ret.item[i] = pow(item[i],(int)m.item[i]);
			else m_ret.item[i] = pow(item[i], m.item[i]);
		}
	}
	else if (m.rowNum == rowNum && m.colNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			if(int_pow) m_ret.item[i] = pow(item[i], (int)m.item[i / colNum]);
			else m_ret.item[i] = pow(item[i], m.item[i / colNum]);
		}
	}
	else if (m.colNum == colNum && m.rowNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			if(int_pow) m_ret.item[i] = pow(item[i], (int)m.item[i%colNum]);
			else m_ret.item[i] = pow(item[i], m.item[i%colNum]);
		}
	}
	else
	{
		throw "���ɵ��";
	}
	return m_ret;
}

Matrix Matrix::dot(const Matrix & m) const
{

	Matrix m_ret(rowNum, colNum);
	if (m.rowNum == rowNum && m.colNum == colNum)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] * m.item[i];
		}
	}
	else if (m.rowNum == rowNum && m.colNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] * m.item[i / colNum];
		}
	}
	else if (m.colNum == colNum && m.rowNum == 1)
	{
		for (int i = 0; i < rowNum*colNum; i++)
		{
			m_ret.item[i] = item[i] * m.item[i%colNum];
		}
	}
	else
	{
		throw "���ɵ��";
	}
	return m_ret;
}

void Matrix::RowSwap(int i, int j, double multiply)
{
	if (i >= rowNum || i < 0)
	{
		throw "����Խ��";
	}
	double *i_row = &item[i*colNum];
	if (j >= rowNum  || j < 0)
	{
		for (int i = 0; i < colNum; i++)
		{
			i_row[i] = i_row[i] * multiply;
		}
	}
	else
	{
		double *j_row = &item[j*colNum];
		for (int i = 0; i < colNum; i++)
		{
			j_row[i] = j_row[i] + i_row[i]* multiply;
		}
	}
}

void Matrix::RowSwap(int i, int j)
{
	if (i >= rowNum || j >= rowNum || i < 0 || j < 0)
	{
		throw "����Խ��";
	}
	if (i == j) return;
	double *i_row = &item[i*colNum];
	double *j_row = &item[j*colNum];
	for (int i = 0; i < colNum; i++)
	{
		double temp = i_row[i];
		i_row[i] = j_row[i];
		j_row[i] = temp;
	}
}

std::ostream & operator<<(std::ostream & os, const Matrix & m)
{
	for (int i = 0; i < m.rowNum; i++)
	{
		for (int j = 0; j < m.colNum; j++)
			os << std::setw(10) << std::fixed << std::setprecision(12) << m.item[i*m.colNum + j] << " ";
		os << "\n";
	}
	os.flush();
	return os;
}
