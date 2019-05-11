#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#define OVERFLOWED 1E-12
#define IS_DOUBLE_ZERO(d)  (abs(d) < OVERFLOWED)

class Matrix
{
public:
	Matrix(int m, int n);						//����һ��m*n��ȫ�����
	Matrix(int n);								//����һ��n*n�ĵ�λ����
	Matrix(const Matrix &M);					//�������캯�������
	Matrix(double* items, int m, int n);		//�������鿽��һ������
	~Matrix();
	static Matrix FromFile(std::string file);	//��һ���ļ��й������
	int getRowNum() const;						//���ؾ��������
	int getColNum() const;						//���ؾ��������

	Matrix Trans() const;						//�õ�����ת��

	double get(int i, int j) const;             //���ؾ����i��j��Ԫ��
	void set(int i, int j, double val);         //���þ����i��j��Ԫ��

	Matrix getSubMatrix(int row_low, int row_up, int col_low, int col_up) const;    //�����Ӿ����дӵ�row_low����row_up���д�col_low��col_up����ֵΪ��ʱ��ʾ����ȡ��࣬����row_lowȡ0��row_upȡrowNum-1
	Matrix getMergeMatrix(const Matrix &second, bool is_v = true) const;		    //�ϲ�����Ĭ�ϴ�ֱ����ϲ�

	Matrix operator +(const Matrix &m) const;        //�����������
	Matrix operator -(const Matrix &m) const;        //�����������
	Matrix operator +(const double f) const;         //������ӳ���
	Matrix operator -(const double f) const;         //�����������
	Matrix operator *(const Matrix &m) const;        //�����������
	Matrix operator *(const double f) const;         //������Գ���

	Matrix& operator=(const Matrix& m);				 //��ȸ���
	Matrix& operator=(const double f);				 //������ֵ
	Matrix Inverse() const;							 //�õ������

	friend std::ostream& operator <<(std::ostream &os, const Matrix &m);		//���������

	double vector_norm(bool is_sqrt=true) const;		//��������ģ
	Matrix sum(int axis = 0) const;					//���������л����е���ֵ�ͣ�����һ��һά����,axis=0�����У�axis=1�����У����������С�
	double all_sum() const;							//�������к�


	Matrix matpow(double p) const;					//�����˵�p�η�
	Matrix matpow(int p) const;						//�����˵�p�η�
	Matrix matpow(const Matrix &m) const;				//������

private:
	double *item;      //ָ�������Ԫ��
	int rowNum;        //��������
	int colNum;        //��������

private:
	//��������б任
	//���j=-1,���i����multiply��
	//���j��ȡֵ��Χ�ڣ��򽫵�i������multiply���ӵ�j��
	void RowSwap(int i, int j, double multiply);
	//��������
	void RowSwap(int i, int j);
};