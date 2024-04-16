#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;
using namespace std::chrono;

void cholesky_decomposition(const std::vector<std::vector<double>> &A, std::vector<std::vector<double>> &L)
{
    int n = A.size();

    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

    // Perform Cholesky decomposition
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < j; k++)
            {
                sum += L[i][k] * L[j][k];
            }

            if (i == j)
            {
                L[i][j] = std::sqrt(A[i][i] - sum);
            }
            else
            {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}
void solve_linear_system(const std::vector<std::vector<double>>& L, const std::vector<double>& b, std::vector<double>& x)
{
    int n = L.size();
    x.resize(n);

    // Forward substitution: Solve Ly = b
    std::vector<double> y(n);
    for (int i = 0; i < n; ++i)
    {
        double sum = 0.0;
        for (int j = 0; j < i; ++j)
        {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }

    // Backward substitution: Solve L^T x = y
    for (int i = n - 1; i >= 0; --i)
    {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j)
        {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
}
int main()
{
    vector<int> sizes = {100, 400, 500, 700, 1000, 1500, 2000};
    vector<double> avgTimes;

    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int n : sizes)
    {
        vector<vector<double>> A(n, vector<double>(n));
        vector<double> b(n, 1.0);

        double totalElapsedTime = 0.0;
        int numTrials = 5;

        for (int trial = 0; trial < numTrials; ++trial)
        {
            std::vector<std::vector<double>> L;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    A[i][j] = distribution(generator);
                }
                b[i] = distribution(generator);
            }
            auto start = high_resolution_clock::now();

            cholesky_decomposition(A, L);

            auto end = high_resolution_clock::now();
            duration<double> elapsedTime = duration_cast<duration<double>>(end - start);
            totalElapsedTime += elapsedTime.count();
        }

        double avgTime = totalElapsedTime / numTrials;
        avgTimes.push_back(avgTime);
    }

    for (int i = 0; i < sizes.size(); ++i)
    {
        cout << "Size: " << sizes[i] << ", Avg Time: " << avgTimes[i] << " seconds" << endl;
    }

    return 0;
}
