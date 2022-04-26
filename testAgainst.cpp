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

// NOT WORKING (quats in arr all the same)
vector<Quaternion> createRotQuats(vector<float> axis, float numAngles) {
    vector<Quaternion> qArr;
    float angleIncr = (1/ numAngles) * 2 * PI;
    Quaternion thisQ;
    Quaternion axisQ(0, axis[0], axis[1], axis[2]);
    for (int i=0; i<numAngles; i++) {
        thisQ = axisQ.get_rot(i * angleIncr);
        qArr.push_back(thisQ);
    }
    return qArr;
}

vector<Euler> createRotEulers(vector<Quaternion> qArr) {
    vector<Euler> eArr;
    for (int i=qArr.size() - 1; i>=0; i--) {
        // FOR SOME REASON THE EULER ARRAY IS EXACTLY BACKWARDS FROM THE QUAT ARRAY WHEN MAPPING FRONT LEFT TO RIGHT
        eArr.push_back(quatToEuler(qArr[i]));
    }
    return eArr;
}

vector<vector<float> > quatRotsToPts(vector<float> pt, vector<Quaternion> qArr) {
    vector<vector<float> > ptsArr;

    Quaternion initPtQ(0, pt[0], pt[1], pt[2]);
    Quaternion rotQ;
    Quaternion nextPtQ;

    vector<float> nextPt;
    for (int i=0; i<3; i++) {
        nextPt.push_back(0);
    }

    for (int i=0; i<qArr.size(); i++) {
        rotQ = qArr[i];
        nextPtQ = initPtQ.rotate(rotQ);

        // SOMETHING WEIRD HAPPENING HERE --- RESOLVED!!
        nextPt[0] = nextPtQ.get_qx();
        nextPt[1] = nextPtQ.get_qy();
        nextPt[2] = nextPtQ.get_qz();

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

void print_qArr(vector<Quaternion> qArr) {
    for (int i=0; i<qArr.size(); i++) {
        Quaternion q;
        q = qArr[i];
        // q.print_ijk();
    }
}

bool test(vector<float> initPt, vector<float> axis, int numAngles) {
    vector<Quaternion> qArr;
    qArr = createRotQuats(axis, numAngles); // NOT WORKING
    print_qArr(qArr);

    vector<Euler> eArr;
    eArr = createRotEulers(qArr);

    vector<vector<float> > qPts;
    qPts = quatRotsToPts(initPt, qArr);

    vector<vector<float> > ePts;
    ePts = eulerRotsToPts(initPt, eArr);

    bool isWorking = true;
    for (int i=0; i<numAngles; i++) {
        if (qPts[i] != ePts[i]) {
            isWorking = false;
            cout << "place = " << i << "\n";
            cout << "quat result = " << qPts[i][0] << ", " << qPts[i][1] << ", " << qPts[i][2] << "\n";
            cout << "euler result = " << ePts[i][0] << ", " << ePts[i][1] << ", " << ePts[i][2] << "\n\n";
        }
    }
    return isWorking;
}

int main() {

    vector<float> initPt1;
    initPt1.push_back(1);
    initPt1.push_back(0);
    initPt1.push_back(0);

    vector<float> axis1;
    axis1.push_back(0);
    axis1.push_back(0);
    axis1.push_back(1);
    
    int numAngles;

    // NOT WORKING (qPts is not changing for diff angles)
    bool test1 = test(initPt1, axis1, 10);






    return 0;
}

