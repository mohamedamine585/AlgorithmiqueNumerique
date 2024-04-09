#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

void gaussElimination(vector<vector<double>> &A, vector<double> &b)
{
    int n = A.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int maxRow = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (abs(A[j][i]) > abs(A[maxRow][i]))
            {
                maxRow = j;
            }
        }
        if (maxRow != i)
        {

            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);
        }

        for (int k = i + 1; k < n; ++k)
        {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; ++j)
            {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }
}

// Phase 2 de l'élimination de Gauss : remontée
vector<double> backSubstitution(const vector<vector<double>> &A, const vector<double> &b)
{
    int n = A.size();
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j)
        {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    return x;
}

int main()
{
    vector<int> sizes = {100, 400, 500, 700, 1000, 1500, 2000};
    vector<double> avgTimes;

    default_random_engine generator;
    // Distribution uniforme entre 0 et 1
    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int n : sizes)
    {
        vector<vector<double>> A(n, vector<double>(n));
        vector<double> b(n, 1.0);

        double totalElapsedTime = 0.0;
        int numTrials = 5;

        for (int trial = 0; trial < numTrials; ++trial)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    A[i][j] = distribution(generator);
                }
                b[i] = distribution(generator);
            }
            auto start = high_resolution_clock::now();

            gaussElimination(A, b);

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
