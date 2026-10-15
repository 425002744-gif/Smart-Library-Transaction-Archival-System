#ifndef SEARCH_SORT_ENGINE_H
#define SEARCH_SORT_ENGINE_H

#include "EntityModel.h"

class SearchSortEngine {
public:
    static int linearSearch(const Book arr[], int n, const std::string& targetISBN, long long& comparisons);
    static int binarySearch(const Book arr[], int n, const std::string& targetISBN, long long& comparisons);

    static void bubbleSort(Book arr[], int n, long long& comparisons, long long& swaps);
    static void selectionSort(Book arr[], int n, long long& comparisons, long long& swaps);
    static void insertionSort(Book arr[], int n, long long& comparisons, long long& swaps);
};

#endif // SEARCH_SORT_ENGINE_H
