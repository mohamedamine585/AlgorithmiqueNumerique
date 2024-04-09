#include <iostream>
#include <vector>
#include <cmath>

// Perform Cholesky decomposition of a symmetric positive definite matrix A into L
void cholesky_decomposition(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L) {
    int n = A.size();

    // Initialize L matrix as zeros
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

    // Perform Cholesky decomposition
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;
            for (int k = 0; k < j; k++) {
                sum += L[i][k] * L[j][k];
            }

            if (i == j) {
                L[i][j] = std::sqrt(A[i][i] - sum);
            } else {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}

int main() {
    // Example symmetric positive definite matrix A
    std::vector<std::vector<double>> A = {{4, 12, -16}, {12, 37, -43}, {-16, -43, 98}};
    int n = A.size();

    // Declare matrix L for Cholesky decomposition
    std::vector<std::vector<double>> L;

    // Perform Cholesky decomposition
    cholesky_decomposition(A, L);

    // Print the original matrix A
    std::cout << "Original matrix A:" << std::endl;
    for (const auto& row : A) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    // Print the lower triangular matrix L (result of Cholesky decomposition)
    std::cout << "\nLower triangular matrix L:" << std::endl;
    for (const auto& row : L) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
