#include "anari/math.hpp"

float MathUtils::maxFloat(float first, float second, float third)
{
    float max = 0.0;
    if (isgreaterequal(first,second) && isgreaterequal(first,third)){
        max = first;
    }
    else if (isgreaterequal(third,second) && isgreaterequal(third,first)){
        max = third;
    }
    else{
        max = second;
    }
    return max;
}

float MathUtils::minFloat(float first, float second, float third)
{
    float min = 0.0;
    if (islessequal(first,second) && islessequal(first,third)){
        min = first;
    }
    else if (islessequal(third,second) && islessequal(third,first)){
        min = third;
    }
    else{
        min = second;
    }
    return min;
}

int MathUtils::cmpFloat(float A, float B)
{
    // Check if equal, accounting for epsilon.
    if (eqFloat(A, B)) { return 0; }

    // If not equal, get the difference between the values.
    float diff = A - B;

    // If A is larger, return 1; if B is larger, return -1
    return (diff < 0 ? 1 : -1);
}

// FIXME: Not quite there! See https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
bool MathUtils::eqFloat(float A, float B)
{
    /* If the absolute difference between A and B is less than the system
     * epsilon, the two values are considered equal. */
    return (fabs(A - B) < std::numeric_limits<float>
    ::epsilon());
}

float MathUtils::roundtothree(float A)
{
    float value = (int)(A * 1000 + .5);
    return (float)value / 1000;
}

double MathUtils::roundtothree(double A)
{
    double value = (int)(A * 1000 + .5);
    return (double)value / 1000;
}

float MathUtils::roundtoone(float A)
{
    float value = (int)(A * 10 + .5);
    return (float)value / 10;
}

double MathUtils::roundtoone(double A)
{
    double value = (int)(A * 10 + .5);
    return (double)value / 10;
}