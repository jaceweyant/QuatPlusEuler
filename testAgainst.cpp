#include <iostream>
#include <vector>
#include <map>

#include "Euler.cpp"
#include "Quaternion.cpp"


using namespace std;

vector<vector<float> > createQuatRotations(vector<float> p, vector<float> axis, int numRotations) {
    Quaternion thisPt(0,p[0],p[1],p[2]);
    Quaternion thisAxis(0,axis[0],axis[1],axis[2]);
    vector<vector<float> > ptsArr;
    vector<float> thisPtVect;
    float thisAngle = 0;
    for (int i; i < numRotations; i++) {
        Quaternion thisPt2;
        thisPt2 = thisPt.rotate(thisAngle, thisAxis);

        thisPtVect[0] = thisPt2.get_direction().get_x();
        thisPtVect[1] = thisPt2.get_direction().get_y();
        thisPtVect[2] = thisPt2.get_direction().get_z();

        ptsArr[i] = thisPtVect;

        thisAngle += (2 * 3.14159)/numRotations;
    }

    return ptsArr;
}


int main() {
    return 0;
}

