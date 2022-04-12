// Matrix Class Implementation

// COMPILER SHORTCUT
// g++ --std=c++14 Matrix.cpp

#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <string>

#include "Matrix.h"

using namespace std;


// INITIALIZERS --------------------------------------------------------------
Matrix::Matrix() {
	vector<float> thisRow(3, 0);
	for (int i = 0; i < 3; i++) {
		m.push_back(thisRow);
	}
}

// NOT OBSOLETE
Matrix::Matrix(const MIL& inMIL) {
	vector<float> r(3, 0);
	for (int i = 0; i < 3; i++) {
		m.push_back(r);
	}

	vector<vector<int> > m_indices = inMIL.indices;
	vector<float> m_vals = inMIL.values;

	for (int i = 0; m_vals.size(); i++) {
		// use set_val method to set the element at the index to the corresponding value
		vector<int> index = m_indices[i];
		float val = m_vals[i];
		set_val(index[0], index[1], val);
	}
}

Matrix::Matrix(const Matrix& inMx) {
	m = inMx.m;
}

// OPERATORS ------------------------------------------------------------------
void Matrix::operator=(Matrix& mx) {
	m = mx.m;
}

void Matrix::operator=(Matrix&& mx) {
	m = mx.m;
}

Matrix Matrix::operator*(float& k) {
	Matrix newMx;
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			newMx.m[i][j] *= k;
		}
	}
	return newMx;
}

Matrix Matrix::operator*(Matrix& mx) {
	Matrix newMx;
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			vector<float> row = get_row(i);
			vector<float> col = mx.get_col(j);
			float val = row[0]*col[0] + row[1]*col[1] +row[2]*col[2];
			newMx.set_val(i, j, val);
		}
	}
	return newMx;
}



// METHODS --------------------------------------------------------------------
float Matrix::get_val(int r, int c) {
	float val = m[r][c];
	return val;
}

void Matrix::set_val(int r, int c, float val) {
	m[r][c] = val;
	return;
}

vector<float> Matrix::get_row(int r) {
	vector<float> row = m[r];
	return row;
}

void Matrix::set_row(int r, vector<float> row) {
	m[r] = row;
	return;
}

vector<float> Matrix::get_col(int c) {
	vector<float> col;
	for (int i=0; i<3; i++) {
		col.push_back(m[i][c]);
	}
	return col;
}

void Matrix::set_col(int c, vector<float> col) {
	for (int i=0; i<3; i++) {
		m[i][c] = col[i];
	}
	return;
}


void Matrix::printMatrix() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int main() {

	Matrix A;
	A.set_val(0,0,2);
	A.set_val(0,1,3);
	A.set_val(1,1,2);
	A.printMatrix();

	Matrix B;
	B.set_val(0,0,2);
	B.set_val(0,2,3);
	B.set_val(1,0,2);
	B.printMatrix();

	Matrix C;
	C = A*B;
	C.printMatrix();

	return 0;
}
