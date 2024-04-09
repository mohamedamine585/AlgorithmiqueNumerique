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
int main() {
    // Example system of equations
    std::vector<std::vector<double>> A = {{2, 1, -1}, {1, 3, 2}, {1, 1, 1}};
    std::vector<double> b = {2, 12, 4};

    // Perform Gaussian elimination
    gaussian_elimination(A, b);

    // Perform back substitution to find the solution vector x
    std::vector<double> x = back_substitution(A, b);

    // Print the upper triangular matrix A and the modified vector b
    std::cout << "Upper triangular matrix A after Gaussian elimination:" << std::endl;
    for (const auto& row : A) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Modified vector b after Gaussian elimination:" << std::endl;
    for (const auto& elem : b) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Print the solution vector x
    std::cout << "Solution vector x:" << std::endl;
    for (const auto& elem : x) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}