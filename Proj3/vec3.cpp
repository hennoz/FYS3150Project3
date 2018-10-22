#include "vec3.h"
#include <cmath>
#include <iostream>
using namespace std;


vec3::vec3()
{
    components[0] = 0;
    components[1] = 0;
    components[2] = 0;
}

vec3::vec3( double x, double y, double z )
{
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

void vec3::print()
{
    cout << "[" << components[0] << ", " << components[1] << ", " << components[2] << "]" <<endl;
}

void vec3::print(string msg)
{
    cout << msg;
    print();
}

//  Calculate length v1.length()
double vec3::length()
{
    return sqrt(components[0]*components[0] + components[1]*components[1] + components[2]*components[2]);
}

//  Calculate dot product v1.dot(v2)
double vec3::dot(vec3 other)
{
    return components[0]*other.components[0] +
            components[1]*other.components[1] + components[2]*other.components[2];
}

//  Calculate cross product v1.cross(v2)
vec3 vec3::cross(vec3 other)
{
    return vec3 (components[1]*other.components[2]-components[2]*other.components[1],
            components[2]*other.components[0] - components[0]*other.components[2],
            components[0]*other.components[1] - components[1]*other.components[0]);
}

//  Normalize v1.normalize()
vec3 vec3::normalize()
{
    double length = this->length();
    if ( length != 0)
    {
        return vec3 (
        components[0] /= length,
        components[1] /= length,
        components[2] /= length);
    }
}


//  Addition componentwise v1 += v2, v1 is now changed
vec3 &vec3::operator+=(const vec3 &other)
{
    components[0] += other.components[0];
    components[1] += other.components[1];
    components[2] += other.components[2];
    return *this;
}

//  Subtraction
vec3 &vec3::operator-=(const vec3 &other)
{
    components[0] -= other.components[0];
    components[1] -= other.components[1];
    components[2] -= other.components[2];
    return *this;
}


//
vec3 &vec3::operator*=(double other)
{
    components[0] *= other;
    components[1] *= other;
    components[2] *= other;
    return *this;
}

vec3 &vec3::operator/=(double other)
{
    components[0] /= other;
    components[1] /= other;
    components[2] /= other;
    return *this;
}


