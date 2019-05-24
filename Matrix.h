#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#define OVERFLOWED 1E-12
#define IS_DOUBLE_ZERO(d)  (fabs(d) < OVERFLOWED)

class Matrix
{
public:
	Matrix();									//默认构造函数
	Matrix(int m, int n);						//构建一个m*n的全零矩阵
	Matrix(int n);								//构建一个n*n的单位矩阵
	Matrix(const Matrix &M);					//拷贝构造函数，深拷贝
	Matrix(double* items, int m, int n);		//根据数组拷贝一个矩阵
	~Matrix();
	static Matrix FromFile(std::string file);	//从一个文件中构造矩阵
	int getRowNum() const;						//返回矩阵的行数
	int getColNum() const;						//返回矩阵的列数

	Matrix Trans() const;						//得到矩阵转置

	double get(int i, int j) const;             //返回矩阵第i行j列元素
	void set(int i, int j, double val);         //设置矩阵第i行j列元素
	void set_row_col(const Matrix &m, int row_low, int row_up, int col_low, int col_up); //通过m设置矩阵行从row_low到第row_up，列从col_low到col_up，当值为负时表示尽量取最多,m的元素数应该等于要设置的元素数

	Matrix getSubMatrix(int row_low, int row_up, int col_low, int col_up) const;		//返回子矩阵，行从第row_low到第row_up，列从col_low到col_up，当值为负时表示尽量取最多，比如row_low取0，row_up取rowNum-1
	Matrix getMergeMatrix(const Matrix &second, bool is_v = true) const;				//合并矩阵，默认垂直方向合并

	Matrix operator +(const Matrix &m) const;        //两个矩阵相加，如果m只有一行或者一列，则用矩阵的每一行或者每一列加上这一行或者这一列
	Matrix operator -(const Matrix &m) const;        //两个矩阵相减，如果m只有一行或者一列，则用矩阵的每一行或者每一列减上这一行或者这一列
	Matrix operator +(const double f) const;         //矩阵相加常数
	Matrix operator -(const double f) const;         //矩阵相减常数
	Matrix operator *(const Matrix &m) const;        //两个矩阵相乘
	Matrix operator *(const double f) const;         //矩阵乘以常数
	Matrix operator /(const double f) const;         //矩阵除以常数
	Matrix operator /(const Matrix &m) const;        //矩阵除以矩阵，相应元素相除，如果m只有一行或者一列，则用矩阵的每一行或者每一列除上这一行或者这一列

	Matrix& operator=(const Matrix& m);				 //深度复制
	Matrix& operator=(const double f);				 //常数赋值
	Matrix Inverse() const;							 //得到逆矩阵
	Matrix Reciprocal() const;						 //矩阵对每个元素的倒数处理后的矩阵

	friend std::ostream& operator <<(std::ostream &os, const Matrix &m);		//输出符重载

	double vector_norm(bool is_sqrt=true) const;		//计算向量模，is_sqrt表示是否求平方根
	Matrix sum(int axis = 0) const;						//计算所有行或者列的数值和，返回一个一维数组,axis=0代表列，axis=1代表行，其他代表列。
	double all_sum() const;								//计算所有和
	Matrix product(int axis = 0) const;					//计算所有行或者列的点乘积，返回一个一维数组,axis=0代表列，axis=1代表行，其他代表列。
	double all_product() const;							//计算所有元素的积


	Matrix matpow(double p) const;					//矩阵点乘的p次方
	Matrix matpow(int p) const;						//矩阵点乘的p次方
	Matrix matpow(const Matrix &m, bool int_pow = true) const;			//矩阵相应元素的p次方（p对应m矩阵的元素），如果m只有一行或者一列，则用矩阵的每一行或者每一列乘方这一行或者这一列
	Matrix dot(const Matrix &m) const;				//矩阵点乘，相应元素相乘，如果m只有一行或者一列，则用矩阵的每一行或者每一列乘上这一行或者这一列

private:
	double *item;      //指向矩阵首元素
	int rowNum;        //矩阵行数
	int colNum;        //矩阵列数

private:
	//矩阵初等行变换
	//如果j=-1,则对i扩大multiply倍
	//如果j在取值范围内，则将第i行扩大multiply倍加到j行
	void RowSwap(int i, int j, double multiply);
	//交换两行
	void RowSwap(int i, int j);
};