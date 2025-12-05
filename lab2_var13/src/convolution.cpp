#include "convolution.h"

void* worker_conv(void* arg) {
    ConvTask* t = (ConvTask*)arg;

    int r    = t->row;
    int rows = t->in->rows;
    int cols = t->in->cols;
    int W    = t->W;
    int half = W / 2;

    for (int c = 0; c < cols; ++c) {
        double sum = 0.0;

        for (int i = 0; i < W; ++i) {
            int rr = r + i - half;

            for (int j = 0; j < W; ++j) {
                int cc = c + j - half;

                double pixel = 0.0;

                if (rr >= 0 && rr < rows && cc >= 0 && cc < cols) {
                    pixel = t->in->at(rr, cc);
                }

                sum += pixel * (*t->kernel)[i * W + j];
            }
        }

        t->out->at(r, c) = sum;
    }

    os_semaphore_signal(t->sem);
    delete t;
    return nullptr;
}

void apply_convolution(Matrix& m,
                       const std::vector<double>& kernel,
                       int W,
                       int K,
                       int max_threads)
{
    Matrix temp(m.rows, m.cols);
    Matrix* in  = &m;
    Matrix* out = &temp;

    os_semaphore* sem = os_semaphore_create(max_threads);

    for (int iter = 0; iter < K; ++iter) {
        std::vector<os_thread*> threads;
        threads.reserve(m.rows);

        for (int r = 0; r < m.rows; ++r) {
            os_semaphore_wait(sem);

            ConvTask* t = new ConvTask{
                r, in, out, &kernel, W, sem
            };

            os_thread* th = os_thread_create(worker_conv, t);
            threads.push_back(th);
        }

        for (auto t : threads) {
            os_thread_join(t);
            os_thread_destroy(t);
        }

        Matrix* tmp = in;
        in  = out;
        out = tmp;
    }

    if (in != &m)
        m = *in;

    os_semaphore_destroy(sem);
}
