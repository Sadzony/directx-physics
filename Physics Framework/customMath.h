#pragma once
#include <limits>
const double  MinDouble = (std::numeric_limits<double>::min)();
//compares two real numbers. Returns true if they are equal
inline bool isEqual(float a, float b)
{
    if (fabs((double)a - (double)b) < 1E-12)
        return true;

    return false;
}

inline bool isEqual(double a, double b)
{
    if (fabs(a - b) < 1E-12)
        return true;

    return false;
}