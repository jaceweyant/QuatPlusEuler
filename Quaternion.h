#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>

#include "Vect.h"

class Quaternion {

    public:
        // QUATERNION CONSTRUCTORS
        //-----------------------------------------------------------------------------------

        // DEFAULT CONSTRUCTOR
        Quaternion();

        // CONSTRUCTOR GIVEN float and Vect& Object, "wIn" and "vIn"
        Quaternion(float wIn, const Vect & vIn);


        // CONSTRUCTOR FOR GIVEN floats "wIn", "xIn", "yIn", "zIn"
        // Do I need this?
        Quaternion(float wIn, float xIn, float yIn, float zIn);

        // COPY CONSTRUCTOR
        Quaternion(const Quaternion & q);


        // OVERLOADED OPERATIONS
        //-----------------------------------------------------------------------------------

        // COPIES ONE L-VALUE QUATERNION INTO *THIS
        Quaternion operator= (const Quaternion & rhs);

        // COPIES AN TEMPORARY (R-VALUE) QUATERNION INTO *THIS
        Quaternion operator= (Quaternion && rhs);

        // QUATERNION MULTIPLICATION
        Quaternion operator*(const Quaternion & rhs);

        // SCALAR MULTIPLICATION
        Quaternion operator*(const float & k);


        // QUATERNION HELPER MEMBER FUNCTIONS
        //-----------------------------------------------------------------------------------
        // I should consider making norm() and i() mutator functions
        // Maybe even rotate(), I don't really see why not

        // GET METHOD FOR QUATERNION MAGNITUDE
        double mag() const;

        // IS THE QUATERNION ON THE UNIT HYPERSPHERE?
        bool isUnit() const;

        bool isPure() const;

        Quaternion norm() const;

        Quaternion inverse() const;

        // PRINT QUATERNION IN w + xi + yj + zk FORM
        // I want to make this round the values                                                     !!!NOTE!!!
        void print_ijk() const;

        // ROTATION MEMBER FUNCTIONS
        //-----------------------------------------------------------------------------------

        // ROTATE BY SOME ANGLE AROUND SOME AXIS
        // maybe make this a void mutable method... maybe not
        Quaternion rotate(float theta, const Quaternion & d) const;

        float get_angle();

        Vect get_direction();

    
    private:

        // PRIVATE QUATERNION DATA MEMBERS
        //-----------------------------------------------------------------------------------
        float w;
        Vect v;
};

#endif