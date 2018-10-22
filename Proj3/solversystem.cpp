#include <iostream>
#include "solversystem.h"
#include <cmath>
#include "vec3.h"

SolverSystem::SolverSystem()
{
    GMo = 4*M_PI*M_PI;
}


void SolverSystem::addObject(CelestialBody newObject)
{
    m_objects.push_back(newObject);
}

void SolverSystem::printObjects()
{

    for ( unsigned int i = 0; i < m_objects.size(); i++)
    {
//        m_objects[i].print();
    }
}
