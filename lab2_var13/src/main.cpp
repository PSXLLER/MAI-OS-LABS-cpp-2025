#include "matrix.h"
#include "convolution.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 6) {
        std::cout << "Usage: conv <input_matrix> <output_matrix> <kernel_file> <K> <max_threads>\n";
        return 1;
    }

    std::string input_file  = argv[1];
    std::string output_file = argv[2];
    std::string kernel_file = argv[3];

    int K        = std::atoi(argv[4]);
    int max_thr  = std::atoi(argv[5]);

    Matrix m = Matrix::readFromFile(input_file);

    std::ifstream kin(kernel_file);
    int W;
    kin >> W;

    std::vector<double> kernel(W * W);
    for (int i = 0; i < W * W; ++i)
        kin >> kernel[i];

    apply_convolution(m, kernel, W, K, max_thr);

    m.writeToFile(output_file);

    return 0;
}
