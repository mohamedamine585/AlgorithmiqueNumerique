#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

void lu_decomposition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
    int n = A.size();

    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    U = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
    }

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
    vector<int> sizes = {100, 400, 500, 700, 1000, 1500, 2000};
    vector<double> avgTimes;

    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int n : sizes) {
        vector<vector<double>> A(n, vector<double>(n));
        vector<double> b(n, 1.0);

        double totalElapsedTime = 0.0;
        int numTrials = 5;

        for (int trial = 0; trial < numTrials; ++trial) {
            std::vector<std::vector<double>> L, U;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    A[i][j] = distribution(generator);
                }
                b[i] = distribution(generator);
            }
            auto start = high_resolution_clock::now();

            lu_decomposition(A, L, U);

            auto end = high_resolution_clock::now();
            duration<double> elapsedTime = duration_cast<duration<double>>(end - start);
            totalElapsedTime += elapsedTime.count();
        }

        double avgTime = totalElapsedTime / numTrials;
        avgTimes.push_back(avgTime);
    }

    for (int i = 0; i < sizes.size(); ++i) {
        cout << "Size: " << sizes[i] << ", Avg Time: " << avgTimes[i] << " seconds" << endl;
    }

    return 0;
}
