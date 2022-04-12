// Euler Angle Rotation Class Header

#ifndef EULER_H
#define EULER_H

#include <iostream>
#include <vector>

#include "Matrix.h"

using namespace std;

class Euler {
public:
    // PUBLIC DATA MEMBERS
    
    // INITIALIZERS
    Euler();
    Euler(float phi, float theta, float psi);
    Euler(const Euler& e);

    Matrix get_A();

    vector<float> rotate(vector<float>& pt);




private:
    // PRIVATE DATA MEMBERS
    Matrix A;
};

#endif