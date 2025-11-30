#pragma once
#include "matrix.h"
#include "os_wrapper.h"
#include <vector>

struct ConvTask {
    int row;
    Matrix* in;
    Matrix* out;
    const std::vector<double>* kernel;
    int W;
    os_semaphore* sem;
};

void* worker_conv(void* arg);

void apply_convolution(Matrix& m, const std::vector<double>& kernel, int W, int K, int max_threads);
