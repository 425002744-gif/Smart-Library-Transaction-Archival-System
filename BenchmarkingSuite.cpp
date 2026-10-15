#include "BenchmarkingSuite.h"
#include "SearchSortEngine.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

void BenchmarkingSuite::runBenchmarkSuite() {
    int testSizes[] = {100, 1000, 10000, 50000};
    int numSizes = 4;

    cout << "\n=========================================================================================================\n";
    cout << "                                  AUTOMATED BENCHMARKING SUITE REPORT                                    \n";
    cout << "=========================================================================================================\n";
    cout << left << setw(18) << "Algorithm"
              << setw(12) << "Size (N)"
              << setw(16) << "Comparisons"
              << setw(14) << "Swaps"
              << setw(18) << "Time Elapsed (ms)"
              << setw(12) << "Big-O" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";

    for (int s = 0; s < numSizes; s++) {
        int n = testSizes[s];
        Book* originalData = new Book[n];

        for (int i = 0; i < n; i++) {
            string id = "ISBN" + to_string(n - i);
            originalData[i] = Book(id, "Title" + to_string(i), "Author", "Gen");
        }

        // 1. Bubble Sort Benchmark
        {
            Book* workArr = new Book[n];
            for (int i = 0; i < n; i++) workArr[i] = originalData[i];

            long long comps = 0, swaps = 0;
            auto start = chrono::high_resolution_clock::now();
            SearchSortEngine::bubbleSort(workArr, n, comps, swaps);
            auto end = chrono::high_resolution_clock::now();
            double elapsed = chrono::duration<double, milli>(end - start).count();

            cout << left << setw(18) << "Bubble Sort"
                      << setw(12) << n
                      << setw(16) << comps
                      << setw(14) << swaps
                      << setw(18) << fixed << setprecision(3) << elapsed
                      << setw(12) << "O(n^2)" << "\n";
            delete[] workArr;
        }

        // 2. Selection Sort Benchmark
        {
            Book* workArr = new Book[n];
            for (int i = 0; i < n; i++) workArr[i] = originalData[i];

            long long comps = 0, swaps = 0;
            auto start = chrono::high_resolution_clock::now();
            SearchSortEngine::selectionSort(workArr, n, comps, swaps);
            auto end = chrono::high_resolution_clock::now();
            double elapsed = chrono::duration<double, milli>(end - start).count();

            cout << left << setw(18) << "Selection Sort"
                      << setw(12) << n
                      << setw(16) << comps
                      << setw(14) << swaps
                      << setw(18) << fixed << setprecision(3) << elapsed
                      << setw(12) << "O(n^2)" << "\n";
            delete[] workArr;
        }

        // 3. Insertion Sort Benchmark
        {
            Book* workArr = new Book[n];
            for (int i = 0; i < n; i++) workArr[i] = originalData[i];

            long long comps = 0, swaps = 0;
            auto start = chrono::high_resolution_clock::now();
            SearchSortEngine::insertionSort(workArr, n, comps, swaps);
            auto end = chrono::high_resolution_clock::now();
            double elapsed = chrono::duration<double, milli>(end - start).count();

            cout << left << setw(18) << "Insertion Sort"
                      << setw(12) << n
                      << setw(16) << comps
                      << setw(14) << swaps
                      << setw(18) << fixed << setprecision(3) << elapsed
                      << setw(12) << "O(n^2)" << "\n";
            delete[] workArr;
        }

        delete[] originalData;
        cout << "---------------------------------------------------------------------------------------------------------\n";
    }
    cout << "=========================================================================================================\n";
}
