#include <iostream>
#include <sstream>
#include "os_wrapper.h"
#include "contracts.h"

typedef float (*DerivativeFunc)(float, float);
typedef int   (*GCFFunc)(int, int);

DerivativeFunc derivative = nullptr;
GCFFunc        gcf = nullptr;

LibHandle lib_deriv = nullptr;
LibHandle lib_gcf   = nullptr;

bool load_impl(bool v1) 
{
#ifdef _WIN32
    const char* d = v1 ? "./libfunc1_derivative_v1.dll" : "./libfunc1_derivative_v2.dll";
    const char* g = v1 ? "./libfunc2_gcf_v1.dll"        : "./libfunc2_gcf_v2.dll";
#else
    const char* d = v1 ? "./libfunc1_derivative_v1.so" : "./libfunc1_derivative_v2.so";
    const char* g = v1 ? "./libfunc2_gcf_v1.so"        : "./libfunc2_gcf_v2.so";
#endif

    if (lib_deriv) os_close_library(lib_deriv);
    if (lib_gcf)   os_close_library(lib_gcf);

    lib_deriv = os_load_library(d);
    lib_gcf   = os_load_library(g);

    if (!lib_deriv || !lib_gcf) 
    {
        std::cerr << "Failed to load libraries\n";
        return false;
    }

    derivative = (DerivativeFunc) os_load_symbol(lib_deriv, "Derivative");
    gcf        = (GCFFunc)        os_load_symbol(lib_gcf, "GCF");

    return derivative && gcf;
}

int main() 
{
    std::cout << "Program #2 (dynamic loading)\n";
    std::cout << "Commands:\n";
    std::cout << "  0           - switch implementation (v1 <-> v2)\n";
    std::cout << "  1 A deltaX  - compute Derivative(A, deltaX)\n";
    std::cout << "  2 A B       - compute GCF(A, B)\n";
    std::cout << "  q           - quit\n\n";

    bool v1 = true;
    if (!load_impl(v1)) return 1;

    std::string line;

    while (true) 
    {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "q") break;

        std::istringstream iss(line);
        int cmd;
        iss >> cmd;

        if (cmd == 0) {
            v1 = !v1;
            if (!load_impl(v1)) 
            {
                std::cout << "Error switching implementation\n";
                return 1;
            }
            std::cout << "Switched to implementation: " << (v1 ? "v1" : "v2") << "\n";

        } else if (cmd == 1) 
        {
            float A, dx;
            if (!(iss >> A >> dx)) 
            {
                std::cout << "Error: format is 1 A deltaX\n";
                continue;
            }
            std::cout << derivative(A, dx) << "\n";

        } else if (cmd == 2) 
        {
            int A, B;
            if (!(iss >> A >> B)) 
            {
                std::cout << "Error: format is 2 A B\n";
                continue;
            }
            std::cout << gcf(A, B) << "\n";

        } else 
        {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
