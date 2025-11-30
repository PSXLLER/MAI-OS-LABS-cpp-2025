#pragma once
#include <vector>
#include <string>

class Matrix {
public:
    int rows, cols;
    std::vector<double> data;

    Matrix(int r = 0, int c = 0);
    double&       at(int r, int c);
    const double& at(int r, int c) const;

    static Matrix readFromFile(const std::string& path);
    void writeToFile(const std::string& path) const;
};
