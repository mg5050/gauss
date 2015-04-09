#ifndef __MATRIX_INCLUDED__
#define __MATRIX_INCLUDED__

#include <string>

class node
{
public:
    double value; // a	real	number
    int row;	//	an	integer > 0	storing which row	this node belongs	to
    int col;  // an integer >	0 storing which column this node	belongs to
    node * rowLink; // link	to	the next	node in the	row linked list
    node * colLink; // link	to	the next	node in the	col linked list
    
    node(void): rowLink(NULL), colLink(NULL) {}
};

void ClearMatrix(int matrix);
void ParseTerm(std::string s, int row);
void InsertNodeAtRow(node * head, node * newnode, int col, int pos, int matrix);
void InsertNodeAtCol(node * head, node * newnode, int row, int pos, int matrix);
void Insert(int i, int j, node c, int matrix);
void Initialize(int n, std::string s[], int matrix);
void Output(int matrix);
void copyNode(node source, node * &dest);
void PrintNode(node * tp);
node * FetchMatrixRow(int matrix, int pos);
node * FetchMatrixCol(int matrix, int pos);
node * SetMatrixRow(int matrix, int pos, node * p);
node * SetMatrixCol(int matrix, int pos, node * p);
node * GetNode(int row, int col, int matrix);
void DelNodeAtRow(node * head, int row, int col, int matrix);
void DelNodeAtCol(node * head, int row, int col, int matrix);
void SwapRows(int i, int j, int matrix);
void Delete(int i, int j, int matrix);
void AddRow(int i, double c, int j, int matrix);
void SubtractRow(int i, double c, int j, int matrix);
void PrintLL(node * hp);

enum MATRIX
{
	m1,
	m2,
	m3
};

extern std::string s1[4];
extern std::string s2[6];
extern std::string s3[8];

extern int MATRIX_SIZE[3];

#endif