#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <string>
#include "vec3.h"
#include <math.h>

using namespace std;

class CelestialBody
{
public:
//    vec3 position;
//    vec3 velocity;
    double position[3];
    double velocity[3];
    double mass;
    string name;

    double kinetic;
    double potential;

//    CelestialBody(vec3 newPosition, vec3 newVelocity, double newMass, string newName );

    CelestialBody( double m ,double x, double y, double z, double vx, double vy, double vz);

    double distance( CelestialBody other);
    double accelleration ( CelestialBody other, int axis);
    double KineticEnergy();
    double PotentialEnergy( CelestialBody other );
    double AngularMoment();
    double RelativisticCorrection( CelestialBody other );
    double accellerationRel( CelestialBody other, int axis );
    double PerihelionPrecession();
};

#endif // CELESTIALBODY_H
