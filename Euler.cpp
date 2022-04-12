// Euler and Matrix Class Implementation

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "Euler.h"

using namespace std;


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------


// FROM EULER CLASS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

Euler::Euler() {}

Euler::Euler(float phi, float theta, float psi) {

    Matrix B;
    B.set_val(0,0,cos(psi/2));
    B.set_val(0,1,sin(psi/2));
    B.set_val(1,0,-1*sin(psi/2));
    B.set_val(1,1,cos(psi/2));
    B.set_val(2,2,1);

    Matrix C;
    C.set_val(0,0,1);
    C.set_val(1,1,cos(theta/2));
    C.set_val(1,2,sin(theta/2));
    C.set_val(2,1,-1*sin(theta/2));
    C.set_val(2,2,cos(theta/2));

    Matrix D;
    D.set_val(0,0,cos(phi/2));
    D.set_val(0,1,sin(phi/2));
    D.set_val(1,0,-1*sin(phi/2));
    D.set_val(1,1,cos(phi/2));
    D.set_val(2,2,1);

    A = (B*C)*D;
}

Matrix Euler::get_A() {
    return A;
}

vector<float> Euler::rotate(vector<float>& initPt) {
    vector<float> finalPt;
    for (int i=0; i<3; i++) {
        vector<float> row = A.get_row(i);
        float val = row[0]*initPt[0] + row[1]*initPt[1] + row[2]*initPt[2];
        finalPt.push_back(val);
    }
    return finalPt;
}

void printPt(const vector<float>& pt) {
    for (int i=0; i<3; i++) {
        cout << pt[i] << ' ';
    }
    cout << endl;
}


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------


// FROM Matrix CLASS
//-------------------------------------------------------------------------------

// INITIALIZERS --------------------------------------------------------------
Matrix::Matrix() {
	vector<float> thisRow(3, 0);
	for (int i = 0; i < 3; i++) {
		m.push_back(thisRow);
	}
}

    // OBSOLETE
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
    vector<float> row;
    for (int i=0; i<3; i++) {
        row.push_back(m[r][i]);
    }
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


    // Don't really need this for anything other than testing
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

    Euler T(1,1,1);
    T.get_A().printMatrix();

    vector<float> initPt{0,0,1};
    vector<float> finalPt = T.rotate(initPt);
    printPt(finalPt);

    return 0;
}