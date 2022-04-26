#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "Euler.cpp"
#include "Quaternion.cpp"

using namespace std;

const float PI = 3.14159;

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

vector<Quaternion> createRotQuats(vector<float> axis, int numAngles) {
    vector<Quaternion> qArr;
    float thisAngle = 0;
    Quaternion thisQ;
    Quaternion axisQ(0, axis[0], axis[1], axis[2]);
    for (int i=0; i<numAngles; i++) {
        thisQ = axisQ.get_rot(thisAngle);
        qArr.push_back(thisQ);
        thisAngle += (1/numAngles) * 2 * PI;
    }
    return qArr;
}

vector<Euler> createRotEulers(vector<Quaternion> qArr) {
    vector<Euler> eArr;
    for (int i=0; i<qArr.size(); i++) {
        eArr.push_back(quatToEuler(qArr[i]));
    }
    return eArr;
}

vector<vector<float> > quatRotsToPts(vector<float> pt, vector<Quaternion> qArr) {
    vector<vector<float> > ptsArr;
    Quaternion initPtQ(0, pt[0], pt[1], pt[2]);
    Quaternion nextPtQ;
    vector<float> nextPt;
    for (int i=0; i<qArr.size(); i++) {
        nextPtQ = initPtQ.rotate(qArr[i]);
        nextPt.push_back(nextPtQ.get_v().get_x());
        nextPt.push_back(nextPtQ.get_v().get_y());
        nextPt.push_back(nextPtQ.get_v().get_z());
        ptsArr.push_back(nextPt);
    }
    return ptsArr;
}

vector<vector<float> > eulerRotsToPts(vector<float> pt, vector<Euler> eArr) {
    vector<vector<float> > ptsArr;
    vector<float> nextPt;
    for (int i=0; i<eArr.size(); i++) {
        nextPt = eArr[i].rotate(pt);
        ptsArr.push_back(nextPt);
    }
    return ptsArr;  
}


int main() {
    return 0;
}

