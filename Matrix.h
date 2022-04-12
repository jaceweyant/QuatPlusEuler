// 3x3 Matrix class header file


/*
The class should be initialized with a nested array, 
representing the rows and columns of the matrix,
of float values which represent the elements of the matrix.

It should include the following libraries
- iostream
- cmath
- vector
- tuple

It should include the following operations:
- scalar multiplication
- matrix multiplication

It should include the following methods:
- get row, get column
- set row, set column
- get element
- set element
*/

#ifndef MATRIX_H
#define MATRIX_H

using namespace std;


#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>

struct MIL {
	vector<vector<int> > indices;
	vector<float> values;
	MIL() {}
	MIL(vector<vector<int> > i, vector<float> v) {
		indices = i;
		values = v;
	}
};


class Matrix {

public:
	// INITIALIZERS
	Matrix();
	Matrix(const MIL& inMIL); // NOT OBSOLETE
	Matrix(const Matrix& inMatrix);

	// OPERATIONS
	void operator=(Matrix& mx);
	void operator=(Matrix&& mx);
	Matrix operator*(float& k);
	Matrix operator*(Matrix& m2);

	// METHODS
	float get_val(int r, int c);
	void set_val(int r, int c, float val);

	vector<float> get_row(int r);
	void set_row(int r, vector<float> row);
	vector<float> get_col(int c);
	void set_col(int c, vector<float> col);

	void printMatrix();

private:
	// DATA MEMBERS
	vector<vector<float> > m;
};

#endif
