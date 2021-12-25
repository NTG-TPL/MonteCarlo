
#include <vector>
#include <iostream>
#include "Functions.h"

double SumH(std::vector<double>& x, std::vector<double>& y, std::vector<double>& index, int n) {
    double expected_val = 0;
    for (int i = 0; i < n; i++) {
        if (index[i] == 1) {
            expected_val += (sin(x[i] + y[i]) + cos(x[i] - y[i])) / (x[i] + y[i]);
        }
    }
    return expected_val;
}
void SelectPoints(std::vector<double>& x, std::vector<double>& y, std::vector<double>& index, int n) {
    for (int i = 0; i < n; i++) {
        double g_x = sqrt(x[i] - 1);
        if (y[i] <= g_x) {
            index[i] = 1;
        }
    }
}
void InitPoints(std::vector<double>& x, std::vector<double>& y, int n)
{
    double sq = sqrt(3.0);
    for (int i = 0; i < n; i++)
    {
        x.emplace_back(((double)rand() / (double)RAND_MAX) * 2.0 + 2.0);
        y.emplace_back(((double)rand() / (double)RAND_MAX) * sq);
    }
}