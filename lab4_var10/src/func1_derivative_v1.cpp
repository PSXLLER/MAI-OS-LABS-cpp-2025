#define BUILD_DLL
#include "contracts.h"
#include <cmath>

extern "C" API float Derivative(float A, float deltaX) 
{
    return (cos(A + deltaX) - cos(A)) / deltaX;
}
