#include "celestialbody.h"
//#include "vec3.h"

//CelestialBody::CelestialBody(vec3 newPosition, vec3 newVelocity, double newMass, string newName)
//{
//        position = newPosition;
//        velocity = newVelocity;
//        mass = newMass;
//        name = newName;
//}

// NameOfClass::ObjetType( variables / properties ,... )
CelestialBody::CelestialBody( double m ,double x, double y, double z, double vx, double vy, double vz) {
    mass = m;
    position[0] = x;
    position[1] = y;
    position[2] = z;
    velocity[0] = vx;
    velocity[1] = vy;
    velocity[2] = vz;
}

//  DISTANCE
//  NameOfClass::MethodInClass ( TypeObject )  ---->  define distance "r"
double CelestialBody::distance( CelestialBody other ) {
    double dx = this->position[0] - other.position[0];
    double dy = this->position[1] - other.position[1];
    double dz = this->position[2] - other.position[2];
    return sqrt( dx*dx + dy*dy + dz*dz);
}

//  ACCELLERATION
//  Define accelleration method
double CelestialBody::accelleration(CelestialBody other, int axis) {
    double tol = 1e-6;
    double r = this->distance( other );
    if ( fabs(r) > tol )
    {
        return -(this->position[axis] - other.position[axis])*4*M_PI*M_PI*other.mass/(r*r*r)/* *RelativisticCorrection( other )*/ ;
    } else {
        return 0;
    }
}

//  SPECIAL ACCELERATION
double CelestialBody::accellerationRel(CelestialBody other, int axis) {
    double r = this->distance( other );
    double l = this->AngularMoment();
    double c  = 63197.8; //  AU/yr
    if ( r!=0 )    {
        return -( 1 + 3*l*l/(r*r*c*c))*(this->position[axis] - other.position[axis])*4*M_PI*M_PI*other.mass/(r*r*r);
    } else {
        return 0;
    }
}


double CelestialBody::PerihelionPrecession(){
    return this->position[1]/this->position[0];
}

double CelestialBody::AngularMoment(){
  double x  = this->position[0];
  double y  = this->position[1];
  double z  = this->position[2];
  double vx = this->velocity[0];
  double vy = this->velocity[1];
  double vz = this->velocity[2];
  //  return ||Crossproduct|| = ||( x, y, z ) X ( dx, dy, dz )||
  return sqrt(( y*vz - z*vy )*( y*vz - z*vy ) + ( x*vz - z*vx )*( x*vz - z*vx ) + ( x*vy - y*vx )*( x*vy - y*vx ));
}

//double CelestialBody::RelativisticCorrection( CelestialBody other ){
//    double c  = 63197.8; //  AU/yr
//    double cc = c*c;
//    double r = distance( other );
//    double l = AngularMoment();
//    return ( 1 + 3*l*l/(r*r*cc));

//}

//double CelestialBody::KineticEnergy(){
//  double vv = this->velocity[0]*this->velocity[0] + this->velocity[1]*this->velocity[1] + this->velocity[2]*this->velocity[2];
//  return 0.5*this->mass*vv;
//}

//double CelestialBody::PotentialEnergy( CelestialBody other ){
//  double r = this->distance(other);
//  if (r!=0){
//      return -4*M_PI*M_PI*other.mass*this->mass/r;
//  } else {
//      return 0;
//  }
//}
