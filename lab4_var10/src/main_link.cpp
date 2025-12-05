#include <iostream>
#include <sstream>
#include "contracts.h"

int main() 
{
    std::cout << "Program #1 (compile-time linking)\n";
    std::cout << "Commands:\n";
    std::cout << "  1 A deltaX  - compute Derivative(A, deltaX)\n";
    std::cout << "  2 A B       - compute GCF(A, B)\n";
    std::cout << "  q           - quit\n\n";

    std::string line;
    while (true) 
    {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "q") break;

        std::istringstream iss(line);
        int cmd;
        iss >> cmd;

        if (cmd == 1) 
        {
            float A, dx;
            if (!(iss >> A >> dx)) 
            {
                std::cout << "Error: format is 1 A deltaX\n";
                continue;
            }
            std::cout << Derivative(A, dx) << "\n";

        } else if (cmd == 2) {
            int A, B;
            if (!(iss >> A >> B)) 
            {
                std::cout << "Error: format is 2 A B\n";
                continue;
            }
            std::cout << GCF(A, B) << "\n";

        } else 
        {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
