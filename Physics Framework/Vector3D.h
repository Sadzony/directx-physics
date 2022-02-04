#pragma once
#include <iostream>
#include <windows.h>
#include "constants.h"
//compares two real numbers. Returns true if they are equal
inline bool isEqual(float a, float b)
{
    if (fabs(a - b) < 1E-12)
        return true;

    return false;
}

inline bool isEqual(double a, double b)
{
    if (fabs(a - b) < 1E-12)
        return true;

    return false;
}

class Vector3D
{
    double x;
    double y;
    double z;

    Vector3D() :x(0.0), y(0.0), z(0.0) {}
    Vector3D(double p_x, double p_y, double p_z) :x(p_x), y(p_y), z(p_z) {}

    //sets all coordinates to 0
    void Zero() { x = 0.0; y = 0.0; z = 0.0; }

    //returns true if all coordinates are 0
    bool isZero()const { return (x * x + y * y + z*z) < MinDouble; }

    //returns the length of the vector
    double Length()const;

    //returns the squared length of the vector (thereby avoiding the sqrt)
    double LengthSq()const;

    void   Normalize();

    double Dot(const Vector3D& v2)const;

    //adjusts coordinates so that the length of the vector does not exceed max
    void Truncate(double max);

    //returns the distance between this vector and the one passed as a parameter
    double Distance(const Vector3D& v2)const;

    //squared version of above.
    double DistanceSq(const Vector3D& v2)const;

    //returns the vector that is the reverse of this vector
    Vector3D GetReverse()const;

    Vector3D Reflect(const Vector3D& surfaceNormal);

    //overloaded operators
    Vector3D& operator+=(const Vector3D& rhs);
    Vector3D& operator-=(const Vector3D& rhs);
    Vector3D& operator*(const Vector3D& rhs);
    Vector3D& operator*=(const Vector3D& rhs);
    Vector3D& operator*=(const double& rhs);
    Vector3D& operator/=(const double& rhs);
    Vector3D operator*(double rhs);
    Vector3D operator-(const Vector3D& rhs);
    Vector3D operator+(const Vector3D& rhs);
    Vector3D operator/(const double& rhs);

    Vector3D& operator=(const Vector3D& v2);

    bool operator==(const Vector3D& rhs)const;
    bool operator!=(const Vector3D& rhs)const;

};



