#include <iostream>
#include <vector>

// Perform LU decomposition (FLU) of a matrix A into L and U matrices
void lu_decomposition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
    int n = A.size();

    // Initialize L matrix as identity and U matrix as zeros
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    U = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
    }

    // Perform LU decomposition
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }

        for (int j = i + 1; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum += L[j][k] * U[k][i];
            }
            L[j][i] = (A[j][i] - sum) / U[i][i]; // Division by U[i][i]
        }
    }
}

int main() {
    // Example matrix A
    std::vector<std::vector<double>> A = {{2, 1, -1}, {1, 3, 2}, {1, 1, 1}};
    int n = A.size();

    // Declare matrices L and U for LU decomposition
    std::vector<std::vector<double>> L, U;

    // Perform LU decomposition (FLU)
    lu_decomposition(A, L, U);

    // Print the original matrix A
    std::cout << "Original matrix A:" << std::endl;
    for (const auto& row : A) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    // Print the L and U matrices
    std::cout << "\nLower triangular matrix L:" << std::endl;
    for (const auto& row : L) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nUpper triangular matrix U:" << std::endl;
    for (const auto& row : U) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
