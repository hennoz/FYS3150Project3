#ifndef VEC3_H
#define VEC3_H
#include <string>
#include <vector>

class vec3

{
public:
    vec3();                                 //  Default constructor

    vec3(double x, double y, double z);     //  Parametized constructor

    void print();                           //  Declaring print
    void print(std::string msg);
    double length();                        //  Declare for length function
    double dot(vec3 other);                 //  Declare for dot product
    vec3 cross(vec3 other);                 //  Declare for cross product
    vec3 normalize();                       //  Declare for normalize

    //  Operators
    vec3 &operator+=(const vec3 &other);    //  Declare +operator
    vec3 &operator-=(const vec3 &other);    //  Declare -operator
    vec3 &operator*=(double other);         //  Declare operator for multiplication with scalar
    vec3 &operator/=(double other);         //  Declare operator for division with scalar


private:
    double components[3];                   //  Declare vector of 3 components


};

inline vec3 operator+(vec3 lhs, vec3 rhs)
{
    lhs += rhs;
    return lhs;
}

inline vec3 operator-(vec3 lhs, vec3 rhs)
{
    lhs -= rhs;
    return lhs;
}


inline vec3 operator*(vec3 lhs, double rhs)
{
    lhs *= rhs;
    return lhs;
}

inline vec3 operator/(vec3 lhs, double rhs)
{
    lhs /= rhs;
    return lhs;
}



#endif // VEC3_H
