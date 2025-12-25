#define BUILD_DLL
#include "contracts.h"

extern "C" API int GCF(int A, int B) 
{
    while (B != 0) {
        int t = A % B;
        A = B;
        B = t;
    }
    return A;
}
