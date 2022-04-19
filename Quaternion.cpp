// NEW PROGRAM TO CREATE AND MANIPULATE QUATERNION OBJECTS
// IMPROVED FROM "Quat.cpp"

// test 2

#define _USE_MATH_DEFINES

#include <iostream>
#include <queue>
#include <cmath>
#include <map>
#include <string>

#include "Quaternion.h"


// COMPILER SHORTCUT
// g++ --std=c++11 Quaternion.cpp

using namespace std;


//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************

// CONSTRUCTORS
//-----------------------------------------------------------------------------------
// DEFAULT CONSTRUCTOR
Vect::Vect() {
    x = 0;
    y = 0;
    z = 0;
}

// xyz VALUE INPUT CONSTRUCTOR
Vect::Vect(float xIn, float yIn, float zIn) {
    x = xIn;
    y = yIn;
    z = zIn;
}

// L-VALUE VECT OBJECT CONSTRUCTOR (COPIES A VECT OBJECT VARIABLE)
Vect::Vect(const Vect & rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

// R-VALUE VECT OBJECT CONSTRUCTOR
// I think this should make it so that I can do stuff like Vect v0( v1 + v2 ) and whatnot
// but I should read up on what exactly the double reference operation && does
Vect::Vect(Vect && rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

// OVERLOADED OPERATIONS
//-----------------------------------------------------------------------------------
// COPIES INTO SOME VECT OBJECT FROM AN EXISTING L-VALUE VECT OBJECT
//      This really feels like it shouldn't work                                     !!!NOTE!!!
//      like is it not using the operation inside the definition?
Vect Vect::operator = (const Vect & rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

// COPIES INTO SOME VECT OBJECT FROM A TEMPORARY R-VALUE VECT OBJECT
Vect Vect::operator = (Vect && rhs) {
    Vect copy(rhs);
    swap(x, copy.x);
    swap(y, copy.y);
    swap(z, copy.z);
    return *this;
}

// PERFORMS VECTOR ADDITION
//      unclear whether or not this is a mutator                                       !!!NOTE!!!
//      Also this acts on l-values only                                                 !!!NOTE!!!
        // and I don't think I really need an r-value version
Vect Vect::operator+(const Vect & rhs) const {
    Vect summ(x+rhs.x, y+rhs.y, z+rhs.z);
    return summ;
}

Vect Vect::operator-(const Vect & rhs) const {
    Vect difference(x-rhs.x, y+rhs.y, z+rhs.z);
    return difference;
}

// SCALAR MULTIPLICATION
Vect Vect::operator*(const float & k) const {
    Vect scaled(x*k,y*k,z*k);
    return scaled;
}

// NON-OVERLOADED OPERATIONS
//-----------------------------------------------------------------------------------
// VECTOR MAGNITUDE
float Vect::mag() const {
    return sqrt(x*x + y*y + z*z);
}

Vect Vect::norm() const {
    Vect copy = *this;
    copy * (1/copy.mag());
    return copy;
}

// GIVES DOT PRODUCT OF *THIS WITH L-VALUE VECT OBJECT
//      unclear whether or not this should be a constant function                      !!!NOTE!!!
float Vect::dot(const Vect & rhs) const {
    float target = x*rhs.x + y*rhs.y + z*rhs.z;
    return target;
}

// CROSS PRODUCT OF *THIS WITH L-VALUE VECT OBJECT
//      should this be a mutator or no?                                                !!!NOTE!!!
//      unclear whether or not this should be a constant function                      !!!NOTE!!!
Vect Vect::cross(const Vect & rhs) {
    Vect target;
    target.x = y*rhs.z - z*rhs.y;
    target.y = z*rhs.x - x*rhs.z;
    target.z = x*rhs.y - y*rhs.x;
    return target;
}

float Vect::get_x() const {
    return x;
}
float Vect::get_y() const {
    return y;
}
float Vect::get_z() const {
    return z;
}

void Vect::print_xyz() {
    cout << "[" << x << ", " << y << ", " << z << "]" << endl;
}

//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************

Quaternion::Quaternion() {
    w = 0;
    v.x = 0;
    v.y = 0;
    v.z = 0;   
}

Quaternion::Quaternion(float wIn, const Vect & vIn) {
    w = wIn;
    v = vIn;
}

Quaternion::Quaternion(float wIn, float xIn, float yIn, float zIn) {
    w = wIn;
    v.x = xIn;
    v.y = yIn;
    v.z = zIn;
}

Quaternion::Quaternion(const Quaternion & q) {
    w = q.w;
    v = q.v;
}

Quaternion Quaternion::operator= (const Quaternion & rhs) {
    Quaternion copy(rhs);
    w = copy.w;
    v = copy.v;
    return *this;
}

Quaternion Quaternion::operator= (Quaternion && rhs) {
    Quaternion copy(rhs);
    w = copy.w;
    v = copy.v;
    return *this;
}

// QUATERNION MULTIPLICATION
Quaternion Quaternion::operator*(const Quaternion & rhs) {
    Quaternion product;
    product.w = w*rhs.w - v.dot(rhs.v);
    product.v = (rhs.v * w) + (v * rhs.w) + v.cross(rhs.v);
    return product;
}

// SCALAR MULTIPLICATION
Quaternion Quaternion::operator*(const float & k) {
    Quaternion scaled(w*k, v*k);
    return scaled;
}

// QUATERNION HELPER MEMBER FUNCTIONS
//-----------------------------------------------------------------------------------
// I should consider making norm() and i() mutator functions
// Maybe even rotate(), I don't really see why not

// GET METHOD FOR QUATERNION MAGNITUDE
double Quaternion::mag() const {
    return sqrt(w*w + v.mag()*v.mag()); // can be simplified with a Vect mag function
}

// IS THE QUATERNION ON THE UNIT HYPERSPHERE?
bool Quaternion::isUnit() const {
    return mag() == 1;
}

bool Quaternion::isPure() const {
    return w==0;
}

Quaternion Quaternion::norm() const {
    if (mag() != 0) {
        Quaternion normal(w/mag(), v.norm());
        return normal;
    }
    else {
        cout << "error: input has magnitude of 0" << endl;
        return *this;
    }
}

Quaternion Quaternion::inverse() const {
    double mm = mag()*mag();
    if (mm != 0) {
        Quaternion inv(w/mm, v*(-1/mm));
        return inv;
    }
    else{
        cout << "error: input has magnitude of 0" << endl;
        return *this;
    }
}

float Quaternion::get_w() const {
    return w;
}
Vect Quaternion::get_v() const {
    return v;
}

// PRINT QUATERNION IN w + xi + yj + zk FORM
// I want to make this round the values                                                   
void Quaternion::print_ijk() const {
    float newW = round(w * 10000) / 10000;
    float newX = round(v.get_x() * 10000) / 10000;
    float newY = round(v.get_y() * 10000) / 10000;
    float newZ = round(v.get_z() * 10000) / 10000;
    cout << newW << " + " << newX << "i + " << newY << "j + " << newZ << "k" << endl;
}

// ROTATION MEMBER FUNCTIONS
//-----------------------------------------------------------------------------------

// ROTATE BY SOME ANGLE AROUND SOME AXIS
// maybe make this a void mutable method... maybe not
Quaternion Quaternion::rotate(float theta, const Quaternion & d) const {
    if (!isPure()) {
        cout << "error: input not a pure quaternion" << endl;
        return *this;
    }
    else {
        float m = mag();
        Quaternion p1 = norm();
        Quaternion q1;
        q1.w = cos(theta/2);
        q1.v = d.v.norm() * (sin(theta/2));
        Quaternion q2 = q1.inverse();
        Quaternion p2 = (q1 * p1) * q2;
        return p2*m;
    }
}

float Quaternion::get_angle() {
    Quaternion q = norm();
    float theta = acos(q.w) * 2;
    return theta;
}
Vect Quaternion::get_direction() {
    Vect d = v.norm();
    return d;
}

//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************


//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************
//***********************************************************************************************************

void inputTester() {
    cout << "This is a test of the Quaternion Class.\n\n";

    float p1x;
    float p1y;
    float p1z;
    cout << "Enter an initial point: \n";
    cout << "x = ";
    cin >> p1x;
    cout << "y = ";
    cin >> p1y;
    cout << "z = ";
    cin >> p1z;

    Quaternion p1(0,p1x,p1y,p1z);

    cout << "\nWhat kind of operation are we doing?\n";
    cout << "a) Rotate by some angle around some axis -- get resultant point.\n";
    cout << "b) Rotate to another point -- get rotation quaternion.\n";
    char opKindStr;
    cin >> opKindStr;

    if (opKindStr == 'a') {
        cout << "\nEnter an axis around which to rotate:\n";
        float qxIn;
        float qyIn;
        float qzIn;
        cout << "Enter an initial point: \n";
        cout << "x = ";
        cin >> qxIn;
        cout << "y = ";
        cin >> qyIn;
        cout << "z = ";
        cin >> qzIn;
        Quaternion qIn(0, qxIn, qyIn, qzIn);
        cout << "Enter an angle to rotate by:\n";
        float theta;
        cout << "theta = ";
        cin >> theta;
        Quaternion p2Out;
        p2Out = p1.rotate(theta,qIn);
        cout << "\nThe new rotated point: ";
        p2Out.print_ijk();
    }
    else if (opKindStr == 'b') {
        cout << "\nThis is no longer a thing\n";
    }
    else {
        cout << "error: invalid input.";
    }
    
}

map<float, Quaternion> manyRotations(int numAngles, const Quaternion & p1, const Quaternion & q) {
    map<float, Quaternion> my_map;
    float theta;

    for (float i = 0; i < numAngles; i++) {
        theta = (i / numAngles) * 2 * 3.14159;

        Quaternion p2;
        p2 = p1.rotate(theta, q);
        my_map[theta] = p2;
        my_map[theta].print_ijk();
    }

    return my_map;
}



int main() {


    cout << "Testing Quaternion class...\n\n";
    cout << "Pick a tester:\n";
    cout << "a) Simple input/output tester\n" << "b) test many rotations at once\n";

    char this_test;
    cin >> this_test;

    if (this_test == 'a') {
        inputTester();
    }
    else if (this_test == 'b') {
        int numAngles;
        cout << "How many angles shall we test for? ";
        cin >> numAngles;

        map<float,Quaternion> this_map = manyRotations(numAngles, Quaternion(0,1,0,0), Quaternion(0,0,1,0));
    }
    else {
        cout << "INVALID INPUT\n";
    }


    return 0;
}
// BE
// LONGER
