#pragma once

#ifdef _WIN32
  #ifdef BUILD_DLL
    #define API __declspec(dllexport)
  #else
    #define API __declspec(dllimport)
  #endif
#else
  #define API
#endif

extern "C" 
{
    API float Derivative(float A, float deltaX);
    API int   GCF(int A, int B);
}
