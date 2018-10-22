#ifndef SOLVER_H
#define SOLVER_H
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "celestialbody.h"
using namespace std;

class Solver {
public:
    int MeshPoints;
    double TimeFinal;
    vector<CelestialBody>m_Objects;

    int Method;

    Solver( int N, double T_F, vector<CelestialBody> objects, int m );

    void solve();

};

#endif // SOLVER_H
