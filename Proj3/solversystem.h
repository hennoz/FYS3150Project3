#ifndef SOLVERSYSTEM_H
#define SOLVERSYSTEM_H
#include <vector>
#include "celestialbody.h"


class SolverSystem
{
private:
    std::vector<CelestialBody>m_objects;
    std::vector<vector<double>> positions;
public:
    double GMo;
    SolverSystem();
    void addObject(CelestialBody object);

    void solve(int N, int T);

    void printObjects();
};

#endif // SOLVERSYSTEM_H
