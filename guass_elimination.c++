#include <iostream>
#include <vector>

// Define the Gaussian elimination function
void gaussian_elimination(std::vector<std::vector<double>>& A, std::vector<double>& b) {
    int n = b.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }
}

std::vector<double> back_substitution(const std::vector<std::vector<double>>& U, const std::vector<double>& y) {
    int n = y.size();
    std::vector<double> x(n, 0.0);

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    return x;
}