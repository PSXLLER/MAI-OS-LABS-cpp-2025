#include "matrix.h"
#include <fstream>
#include <stdexcept>

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r * c) {}

double& Matrix::at(int r, int c) {
    return data[r * cols + c];
}

const double& Matrix::at(int r, int c) const {
    return data[r * cols + c];
}

Matrix Matrix::readFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in)
        throw std::runtime_error("Cannot open input file");

    int r, c;
    in >> r >> c;

    Matrix m(r, c);
    for (int i = 0; i < r * c; ++i)
        in >> m.data[i];

    return m;
}

void Matrix::writeToFile(const std::string& path) const {
    std::ofstream out(path);
    out << rows << " " << cols << "\n";

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            out << at(i, j) << " ";
        out << "\n";
    }
}
