// Vector class header file
#ifndef VECT_H
#define VECT_H


#include <iostream>
using namespace std;

class Vect {
    // allows private Vect data members to be accessible to Quaternion class
    friend class Quaternion; 
    public:
        // CONSTRUCTORS
        //-----------------------------------------------------------------------------------
        // DEFAULT CONSTRUCTOR
        Vect();

        // xyz VALUE INPUT CONSTRUCTOR
        Vect(float xIn, float yIn, float zIn);

        // L-VALUE VECT OBJECT CONSTRUCTOR (COPIES A VECT OBJECT VARIABLE)
        Vect(const Vect & rhs);

        // R-VALUE VECT OBJECT CONSTRUCTOR
        // I think this should make it so that I can do stuff like Vect v0( v1 + v2 ) and whatnot
        // but I should read up on what exactly the double reference operation && does
        Vect(Vect && rhs);

        // OVERLOADED OPERATIONS
        //-----------------------------------------------------------------------------------
        // COPIES INTO SOME VECT OBJECT FROM AN EXISTING L-VALUE VECT OBJECT
        //      This really feels like it shouldn't work                                     !!!NOTE!!!
        //      like is it not using the operation inside the definition?
        Vect operator = (const Vect & rhs);

        // COPIES INTO SOME VECT OBJECT FROM A TEMPORARY R-VALUE VECT OBJECT
        Vect operator = (Vect && rhs);

        // PERFORMS VECTOR ADDITION
        //      unclear whether or not this is a mutator                                       !!!NOTE!!!
        //      Also this acts on l-values only                                                 !!!NOTE!!!
                // and I don't think I really need an r-value version
        Vect operator+(const Vect & rhs) const;
        Vect operator-(const Vect & rhs) const;

        // SCALAR MULTIPLICATION
        Vect operator*(const float & k) const;

        // NON-OVERLOADED OPERATIONS
        //-----------------------------------------------------------------------------------
        // VECTOR MAGNITUDE
        float mag() const;

        Vect norm() const;

        // GIVES DOT PRODUCT OF *THIS WITH L-VALUE VECT OBJECT
        //      unclear whether or not this should be a constant function                      !!!NOTE!!!
        float dot(const Vect & rhs) const;

        // CROSS PRODUCT OF *THIS WITH L-VALUE VECT OBJECT
        //      should this be a mutator or no?                                                !!!NOTE!!!
        //      unclear whether or not this should be a constant function                      !!!NOTE!!!
        Vect cross(const Vect & rhs);

        float get_x() const;
        float get_y() const;
        float get_z() const;

        void print_xyz();
        
    protected:
        float x;
        float y;
        float z;

        friend class Quaternion;
};


#endif