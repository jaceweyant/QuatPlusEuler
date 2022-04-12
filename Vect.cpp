// Vect class

#include <iostream>
#include "Vect.h"

using namespace std;

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

int main() {
    return 0;
}
