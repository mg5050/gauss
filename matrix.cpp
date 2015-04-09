#include <string> // string
#include <stdlib.h> // atoi
#include <iostream>
#include <string.h>
#include "matrix.h"

using namespace std;

class node;

void ClearMatrix(int matrix);
void ParseTerm(string s, int row);
void InsertNodeAtRow(node * head, node * newnode, int col, int pos, int matrix);
void InsertNodeAtCol(node * head, node * newnode, int row, int pos, int matrix);
void Insert(int i, int j, node c, int matrix);
void Initialize(int n, string s[], int matrix);
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
void SwapNodesInCol(node * p1, node * p2, int col, int matrix);

node * M1Rows[4];
node * M1Cols[5];

node * M2Rows[6];
node * M2Cols[7];

node * M3Rows[8];
node * M3Cols[9];

string s1[4];
string s2[6];
string s3[8];

int MATRIX_SIZE[3] = {4, 6, 8};

void SwapRows(int i, int j, int matrix) // i must be less than j
{
	if(i == j) return;
	if(i > j)
	{
		int tmp = i;
		i = j;
		j = tmp;
	}
	
	node * row1 = FetchMatrixRow(matrix, i);
	node * row2 = FetchMatrixRow(matrix, j);

	node * tp = row1;
	while(tp != NULL)
	{
		tp->row = j;
		tp = tp->colLink;
	}
	tp = row2;
	while(tp != NULL)
	{
		tp->row = i;
		tp = tp->colLink;
	}
	
	SetMatrixRow(matrix, i, row2); // Set HP of row1 to row2
	SetMatrixRow(matrix, j, row1); // Set HP of row2 to row1
	
	/*
	for(int k = 0; k <= MATRIX_SIZE[matrix]; k++) // for every col
	{
		node * p1 = GetNode(i, k + 1, matrix);
		node * p2 = GetNode(j, k + 1, matrix);
		if(p1 == NULL && p2 == NULL) continue;
		if(p1 == NULL) Insert(j, 
		if(p1 != NULL && p2 != NULL) SwapNodesInCol(p1, p2, k, matrix); // p1 comes before p2
		if(p1 == NULL 
	}
	*/

}

void Delete(int i, int j, int matrix)
{
	node * ptr = FetchMatrixRow(matrix, i);
	DelNodeAtCol(ptr, i, j, matrix);
	
	ptr = FetchMatrixCol(matrix, j);
	DelNodeAtRow(ptr, i, j, matrix);
}

// three cases, remove head node, middle node, last node
void DelNodeAtCol(node * head, int row, int col, int matrix)
{
	node * tp =	head;
	node * prev	= tp;
	
	/* Shouldn't need to be deleted, dont delete y vals
	if(col == MATRIX_SIZE[matrix]) // yval col
	{
		
	}
	*/

	while(tp != NULL && tp->col < col)
	{
		prev = tp;
		tp = tp->colLink;
	}
	if(tp != NULL && tp->col == col) 
	{
		if(tp == head) // deleting head
		{
			SetMatrixRow(matrix, row, tp->colLink);
		}
		else 
		{
			prev->colLink = tp->colLink;
		}
	}
}

void DelNodeAtRow(node * head, int row, int col, int matrix)
{
	node * tp =	head;
	node * prev	= tp;

	while(tp != NULL && tp->row < row)
	{
		prev = tp;
		tp = tp->rowLink;
	}
	if(tp != NULL && tp->row == row)
	{
		if(tp == head) // deleting head
		{
			SetMatrixCol(matrix, col - 1, tp->rowLink);
		}
		else 
		{
			prev->rowLink = tp->rowLink; // deleting node
		}
	}
}

void AddRow(int i, double c, int j, int matrix)
{
	node * op = FetchMatrixRow(matrix, i); // row i HP
	//PrintLL(FetchMatrixRow(matrix, j));
	for(int x = 1; x <= MATRIX_SIZE[matrix]; x++) // for every col, do we also add y values???
	{
		if(op->col == x) // existing value in i
		{
			node * ptr = GetNode(j, x, matrix);
			if(ptr == NULL) // no match
			{
				node newnode;
				newnode.value = op->value * c;
				if(newnode.value != 0) // if val is 0 we don't need to add it
				{
					newnode.row = j;
					newnode.col = x;
					//PrintNode(&newnode);
					Insert(j, x, newnode, matrix); // insert our node
				}
			}
			else 
			{
				//PrintNode(ptr);
				//PrintNode(op);
				ptr->value += op->value * c;
				if(ptr->value == 0) Delete(j, x, matrix);
			}
			if(op != NULL) op = op->colLink;
		}
		else if(op == NULL) break;
	}
	op = GetNode(j, -1, matrix);
	node * add = GetNode(i, -1, matrix);
	op->value += add->value * c;
	//PrintLL(FetchMatrixRow(matrix, j));
}

void SubtractRow(int i, double c, int j, int matrix)
{
	node * op = FetchMatrixRow(matrix, i); // row i HP
	//PrintLL(FetchMatrixRow(matrix, j));
	for(int x = 1; x <= MATRIX_SIZE[matrix]; x++) // for every col, do we also add y values???
	{
		if(op->col == x) // existing value in i
		{
			node * ptr = GetNode(j, x, matrix);
			if(ptr == NULL) // no match
			{
				node newnode;
				newnode.value = 0 - op->value * c;
				if(newnode.value != 0) // if val is 0 we don't need to add it
				{
					newnode.row = j;
					newnode.col = x;
					//PrintNode(&newnode);
					Insert(j, x, newnode, matrix); // insert our node
				}
			}
			else 
			{
				ptr->value -= op->value * c;
				if(ptr->value == 0) Delete(j, x, matrix);
			}
			if(op != NULL) op = op->colLink;
		}
		else if(op == NULL) break;
	}
	op = GetNode(j, -1, matrix);
	node * add = GetNode(i, -1, matrix);
	op->value -= add->value * c;
	//PrintLL(FetchMatrixRow(matrix, j));
}

void PrintLL(node * hp)
{
	cout << "Printing LL:\n\n";
	while(hp != NULL) 
	{
		PrintNode(hp);
		hp = hp->colLink;
	}
	cout << "\nDone\n\n";
}

//Revise delete function
node * GetNode(int row, int col, int matrix)
{
	node * ptr = FetchMatrixRow(matrix, row);
	while(ptr != NULL && ptr->col != col) 
	{
		ptr = ptr->colLink;
	}
	if(ptr != NULL && ptr->col != col) ptr = NULL;
	return ptr;
}

// Following 4 functions work off of index
node * FetchMatrixRow(int matrix, int pos)
{
	switch(matrix)
	{
		case m1: return M1Rows[pos];
		case m2: return M2Rows[pos];
		case m3: return M3Rows[pos];
	}
}

node * FetchMatrixCol(int matrix, int pos)
{
	switch(matrix)
	{
		case m1: return M1Cols[pos];
		case m2: return M2Cols[pos];
		case m3: return M3Cols[pos];
	}
}

node * SetMatrixRow(int matrix, int pos, node * p)
{
	switch(matrix)
	{
		case m1: return M1Rows[pos] = p;
		case m2: return M2Rows[pos] = p;
		case m3: return M3Rows[pos] = p;
	}
}

node * SetMatrixCol(int matrix, int pos, node * p)
{
	switch(matrix)
	{
		case m1: return M1Cols[pos] = p;
		case m2: return M2Cols[pos] = p;
		case m3: return M3Cols[pos] = p;
	}
}

void ClearMatrix(int matrix) // set first pointers to null
{	
	switch(matrix)
	{
		case m1:
		{
			M1Rows[0] = NULL;
			M1Cols[0] = NULL;
			break;
		}
		case m2:
		{
			M2Rows[0] = NULL;
			M2Cols[0] = NULL;
			break;
		}
		case m3:
		{
			M3Rows[0] = NULL;
			M3Cols[0] = NULL;
			break;
		}
	}
}

void ParseTerm(string s, int row, node * val) // in form of	CxN
{
	int len = s.length();
	bool xfound	= false;
	for(int i =	0;	i < len; i++) // for	every	character in term
	{
		if(s.at(i) == 'x')
		{
			xfound = true;
			val->col = atoi(s.substr(i + 1, len - i).c_str()); // everything	after	x is column
			//if no constant value is 1
			if(i == 0) val->value = 1; // no constant before x, assumed to be 1
			else if(i == 1 && (s[0] == '+' || s[0] == '-'))
			{
				if(s[0] == '+' ) val->value = 1;
				else if(s[0] == '-') val->value = -1;
			}
			else 
			{
				val->value = atoi(s.substr(0, i).c_str()); // everything before x is constant
				//cout << s.substr(0, i).c_str() << endl;
			}
			break;
		}
	}

	if(xfound == false) // constant only, must be value to right of equal sign
	{
		val->value =	atoi(s.c_str());
		val->col = -1; // last column
	}

	val->row = row;
}

void PrintNode(node * tp)
{
	if(tp == NULL)
	{
		cout << "INVALID NODE\n";
		return;
	}
	cout << "addr: " << tp << " | row: " << tp->row << " | col: " << tp->col << " | val: " << tp->value;
	if(tp->rowLink == NULL) cout << " | rowLink: NULL";
	else cout << " | rowLink: LIVE";
	if(tp->colLink == NULL) cout << " | colLink: NULL" << endl;
	else cout << " | colLink: LIVE" << endl;
}

void copyNode(node source, node * &dest)
{
	dest = new node();
	dest->value = source.value;
	dest->row = source.row;
	dest->col = source.col;
}

void Insert(int i, int j, node c, int matrix)
{
	if(j == -1) j = MATRIX_SIZE[matrix] + 1; // y col

	node * row_ptr = FetchMatrixRow(matrix, i);
	node * col_ptr = FetchMatrixCol(matrix, j - 1);
	node * newnode = NULL;
	
	copyNode(c, newnode);
	
	if(row_ptr == NULL) SetMatrixRow(matrix, i, newnode);
	else InsertNodeAtCol(row_ptr, newnode, i, j, matrix);
	if(col_ptr == NULL) SetMatrixCol(matrix, j - 1, newnode);
	else InsertNodeAtRow(col_ptr, newnode, j, i, matrix);
}

void InsertNodeAtCol(node * head, node * newnode, int row, int pos, int matrix) // insert a node	at	a certain position in a	list
{
	if(head->col == -1)
	{
		if(newnode->col != -1)
		{
			newnode->colLink = head;
			SetMatrixRow(matrix, row, newnode);
		}
		return;
	}
	
	node * tp =	head;
	node * prev	= tp;

	while(tp != NULL && tp->col < pos)
	{
		if(tp->col != -1)
		{
			prev = tp;
			tp = tp->colLink;
		}
		else
		{
			if(pos <= MATRIX_SIZE[matrix]) break;
			else if(pos >= MATRIX_SIZE[matrix]) return; // cant overwrite y val
		}
	}
	if(tp != NULL && tp->col == pos) return; // non-zero element exists,	cannot be overwritten
	if(tp == NULL) newnode->colLink = NULL; // EOL
	else newnode->colLink = tp; // CONTINUITY
	if(tp == head && tp->col > pos) // our node comes before head
	{
		SetMatrixRow(matrix, row, newnode);
	}
	else 
	{
		prev->colLink = newnode;	//	insert c
	}
	return;
}

void InsertNodeAtRow(node * head, node * newnode, int col, int pos, int matrix) // insert a node	at	a certain position in a	list
{
	node * tp =	head;
	node * prev	= tp;
	while(tp != NULL && tp->row < pos)
	{
		prev = tp;
		tp = tp->rowLink;
	}
	if(tp != NULL && tp->row == pos) return; // non-zero element exists,	cannot be overwritten
	if(tp == NULL) newnode->rowLink = NULL; // EOL
	else newnode->rowLink = tp;
	if(tp == head && tp->row > pos) // our node comes before head
	{
		SetMatrixCol(matrix, col - 1, newnode);
	}
	else prev->rowLink = newnode; //	insert c
	return;
}

void Initialize(int n, string s[], int matrix)
{
	for(int i = 0; i < n; i++) // for every row
	{
		int sz = s[i].size();
		int prev = 0, len = s[i].length();
		for(int j = 0; j < len; j++) // for	every	character in that	row
		{
			char c = s[i].at(j);
			if(c == '-' || c == '+' || c == '=')	//	delimiters
			{
				 
				if(j > 0 && j > prev + 1)
				{
					node val;
					char * term = new char[sz+1];
					string scpy = s[i];
					memcpy(term, scpy.c_str(), sz); // program crash
					term[j] = '\0';
					term+=prev;
					prev = j;
					
					ParseTerm(term, i, &val);
					//PrintNode(&val);
					Insert(i, val.col, val, matrix);
					//cout << "term: " << term << " | " << "val: " << val.value << " row: " << val.row << " col: " << val.col << endl;
				}
				if(c == '=') 
				{
					node val;
					char * term = new char[sz+1];
					term = &s[i][j+1];
					ParseTerm(term, i, &val);
					//PrintNode(&val);
					Insert(i, val.col, val, matrix);
					//cout << "term: " << term << " | " << "val: " << val.value << " row: " << val.row << " col: " << val.col << endl;
				}
				
			}
			
		}
	}
}

// account for col = -1 behavior
void Output(int matrix)
{
	for(int i = 0; i < MATRIX_SIZE[matrix]; i++) // for every possible row
	{
		node * tp = FetchMatrixRow(matrix, i);
		node * yval = NULL;
		cout << '[';
		for(int j = 1; j <= MATRIX_SIZE[matrix] + 1; j++)
		{
			if(tp != NULL && tp->col == -1) 
			{
				yval = tp; // yval, must be done last
				tp = NULL;
				continue;
			}
			if(tp == NULL || tp->col > j) // 0, empty col
			{
				//cout << "col: " << j << " val: ";
				cout << " 0";
			}
			else if(tp->col == j) // existing value for column
			{
				//cout << "col: " << j << " val: ";
				cout << ' ' << tp->value;
				tp = tp->colLink;
			}
		}
		cout << "]" << '[' << "X" << i + 1 << ']'<< '[';
		if(yval != NULL) cout << yval->value;
		cout << ']';
		cout << endl;	
	}
	cout << endl;
}