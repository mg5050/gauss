#include <iostream>
#include "matrix.h"

#define INVALID_NODE_VALUE -9999.99

int MaxRow(int pastrows, int column, int matrix);
void DivideRow(int row, double divisor, int matrix);
void Triangulate(int matrix);

using namespace std;

void Triangulate(int matrix)
{
	int maxrow = 0;
	for(int i = 0; i < MATRIX_SIZE[matrix]; i++) // for every row
	{
		maxrow = MaxRow(i, i, matrix); // col = row
		if(i != maxrow) SwapRows(i, maxrow, matrix);
		//Output(m1);
		
		node * p = GetNode(i, i + 1, matrix);
		double nodeval = 0.0;
		
		if(p != NULL) nodeval = p->value;

		DivideRow(i, nodeval, matrix);
		//cout << "divide:\n\n";
		//Output(m1);
		
		nodeval = 0.0;
		if(p != NULL) nodeval = p->value;
		
		for(int j = i + 1; j < MATRIX_SIZE[matrix]; j++)
		{
			p = GetNode(j, i + 1, matrix);
			double coeff = 0.0;
			if(p != NULL) coeff = p->value / nodeval;
			
			SubtractRow(i, coeff, j, matrix);
			//cout << "subtract:\n\n";
			//Output(m1);
		}
	}
}

void BackSub(int matrix)
{
	for(int i = MATRIX_SIZE[matrix] - 1; i > 0; i--) // for every row
	{	
		node * p = GetNode(i, i + 1, matrix);
		double nodeval = 0.0;
		
		if(p != NULL) nodeval = p->value;
		
		for(int j = i - 1; j >= 0; j--) // for rhs columns
		{
			p = GetNode(j, i + 1, matrix);
			double coeff = 0.0;
			if(p != NULL) coeff = p->value / nodeval;
			
			SubtractRow(i, coeff, j, matrix);
			//cout << "subtract:\n\n";
			//Output(m1);
		}
	}
}

double * Solve(int matrix)
{
	//int * soln = new int[MATRIX_SIZE[matrix]];
	node * tp = NULL;
	double * soln = new double[MATRIX_SIZE[matrix]];
	//soln.reserve(MATRIX_SIZE[matrix]); 
	for(int i = 0; i < MATRIX_SIZE[matrix]; i++)
	{
		tp = FetchMatrixRow(matrix, i);
		while(tp != NULL && tp->col != -1) tp = tp->colLink;
		//PrintNode(tp);
		soln[i] = tp->value;
		//cout << soln[i] << endl;
	}
	return soln;
}

bool IsSolution(double * x, int matrix)
{
	bool soln = true;
	node * tp = NULL;
	node * prev = NULL;
	double sum = 0;
	for(int i = 0; i < MATRIX_SIZE[matrix]; i++)
	{
		tp = FetchMatrixRow(matrix, i);
		while(tp != NULL && tp->col != -1) 
		{
			sum += tp->value * x[tp->col - 1]; // sum row multiplied by constant
			//cout << "sum is " << x[tp->col - 1] << " x " << tp->value << " = " << sum << endl;
			prev = tp;
			tp = tp->colLink;
		}
		cout << "Row " << i << " x " << x[tp->col - 1] << " = " << sum << endl;
		//cout << "sum is: " << sum << endl;
		if(sum != prev->value && prev->col == -1) soln = false;
		sum = 0;
	}
	cout << endl;
	return soln;
}

int MaxRow(int pastrows, int column, int matrix) // return row with maximum value at col, where row is greater than pastrows
{
	node * ptr = FetchMatrixCol(matrix, column);
	if(ptr == NULL) return 0;
	int maxrow = pastrows;
	double max = INVALID_NODE_VALUE;
	while(ptr != NULL)
	{
		if(ptr->value > max && ptr->row >= pastrows) 
		{
			max = ptr->value;
			maxrow = ptr->row;
		}
		ptr = ptr->rowLink;
	}
	return maxrow;
}

void DivideRow(int row, double divisor, int matrix)
{
	node * ptr = FetchMatrixRow(matrix, row);
	node * del = NULL;
	while(ptr != NULL)
	{
		ptr->value = ptr->value / divisor;
		if(ptr->value == 0.0) 
		{
			del = ptr;
			ptr = ptr->colLink;
			Delete(del->row, del->col, matrix);
		}
		else ptr = ptr->colLink;
	}
}

void Step3Operations(string str[], int matrix)
{
	ClearMatrix(matrix);
	Initialize(MATRIX_SIZE[matrix], str, matrix);
	cout << "original:\n\n";
	Output(matrix);
	
	Triangulate(matrix);
	cout << "triangulation:\n\n";
	Output(matrix);
	
	cout << "solved:\n\n";
	BackSub(matrix);
	Output(matrix);
	
	double * soln = Solve(matrix);

	ClearMatrix(matrix);
	Initialize(MATRIX_SIZE[matrix], str, matrix);

	if(IsSolution(soln, matrix) == true)
	cout << "Solution to matrix is correct.\n" << endl;
	
	delete[] soln;
}

int main()
{
	s1[0] = "3x1+5x4=8";
	s1[1] = "2x2-7x3=9";
	s1[2] = "5x1-3x2-10x4=-8";
	s1[3] = "6x2-5x4=1";
	
	Step3Operations(s1, m1);
	
	s2[0] = "-3x1+16x3=6";
	s2[1] = "3x1+2x2=-3";
	s2[2] = "-x1-x2-x3=10";
	s2[3] = "x2+2x3+10x4=7";
	s2[4] = "2x5+x6=0";
	s2[5] = "8x4+3x6=-1";
	
	Step3Operations(s2, m2);

	s3[0] = "2x1-4x4+5x6=32";
	s3[1] = "3x1+4x3+2x5+x7+8x8=31";
	s3[2] = "x2+2x4+3x7=-7";
	s3[3] = "x1+x4+2x5+2x8=10";
	s3[4] = "-x1-2x2+5x8=8";
	s3[5] = "x2+2x4+3x6=8";
	s3[6] = "x3+2x5+x7+x8=8";
	s3[7] = "x1-3x5+x8=-5";
	
	Step3Operations(s3, m3);
}