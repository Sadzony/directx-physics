#pragma once
#include <iostream>
#include <windows.h>
#include "customMath.h"


class Vector3D
{
public:
    double x;
    double y;
    double z;

    Vector3D() :x(0.0), y(0.0), z(0.0) {}
    Vector3D(double p_x, double p_y, double p_z) :x(p_x), y(p_y), z(p_z) {}
    Vector3D(const Vector3D& vec) :x(vec.x), y(vec.y), z(vec.z) {}

    //sets all coordinates to 0
    void Zero() { x = 0.0; y = 0.0; z = 0.0; }

    //returns true if all coordinates are 0
    bool isZero()const { return (x * x + y * y + z*z) < MinDouble; }

    //returns the length of the vector
    double Length()const;

    //returns the squared length of the vector (thereby avoiding the sqrt)
    double LengthSq()const;


    //sets the vector as the magnitude 1
    void Normalize();
    //returns the vector as magnitude 1
    Vector3D Normalized()const;

    double Dot(const Vector3D& v2)const;

    //adjusts coordinates so that the length of the vector does not exceed max
    void Truncate(double max);

    //returns the distance between this vector and the one passed as a parameter
    double Distance(const Vector3D& v2)const;

    //squared version of above.
    double DistanceSq(const Vector3D& v2)const;

    //returns the vector that is the reverse of this vector
    Vector3D GetReverse()const;

    //returns a reflected vector based on a normal
    Vector3D Reflect(const Vector3D& surfaceNormal);

    //overloaded operators
    
    //addition
    Vector3D operator+(const Vector3D& rhs)const;
    Vector3D& operator+=(const Vector3D& rhs);

    //subtraction
    Vector3D operator-(const Vector3D& rhs)const;
    Vector3D& operator-=(const Vector3D& rhs);

    //cross product
    Vector3D& operator*(const Vector3D& rhs)const;
    Vector3D& operator*=(const Vector3D& rhs);

    //boolean operators
    bool operator==(const Vector3D& rhs)const;
    bool operator!=(const Vector3D& rhs)const;

    //scalars
    Vector3D operator/(const double& rhs)const;
    Vector3D& operator/=(const double& scalar);
    Vector3D& operator*=(const double& scalar);
};

//scalar operations, non member to allow both sides


Vector3D operator*(const double& lhs, const Vector3D& rhs);
Vector3D operator*(const Vector3D& lhs, const double& rhs);