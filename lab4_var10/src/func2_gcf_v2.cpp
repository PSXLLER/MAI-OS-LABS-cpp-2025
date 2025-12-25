#define BUILD_DLL
#include "contracts.h"

extern "C" API int GCF(int A, int B) 
{
    int minv = (A < B ? A : B);
    int g = 1;
    for (int i = 1; i <= minv; i++) {
        if (A % i == 0 && B % i == 0)
            g = i;
    }
    return g;
}
