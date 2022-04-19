#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "Euler.cpp"
#include "Quaternion.cpp"


using namespace std;



vector<vector<float> > quatsToPts(vector<float> p, vector<float> axis, int numRotations) {
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


Euler quatToEuler(Quaternion q) {
    float phi, theta, psi;
    float w, x, y, z;

    w = q.get_w();
    x = q.get_v().get_x();
    y = q.get_v().get_y();
    z = q.get_v().get_z();

    phi = atan2(2 * (w*x + y*z), 1 - 2 * (x*x + y*y));
    theta = asin(2 * (w*y - z*x));
    psi = atan2(2 * (w*z + x*y), 1 - 2 * (y*y + z*z));

    Euler e(phi,theta,psi);
    return e;
}

vector<vector<float> > createEulerRotations() {

}

vector<vector<float> > createEulerRotations(vector<float> p, vector<float> eAngles, int numAngles) {
    /*
    Euler thisEuler(eAngles[0], eAngles[1], eAngles[2]);

    float thisAngle = 0;
    vector<float> thisPtVect;
    for (int i; i < numAngles; i++) {
        thisPtVect = thisEuler.rotate(p);
    }
    */
    
}


int main() {
    return 0;
}

