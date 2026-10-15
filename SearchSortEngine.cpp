#include "SearchSortEngine.h"

using namespace std;

int SearchSortEngine::linearSearch(const Book arr[], int n, const string& targetISBN, long long& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i].isbn == targetISBN) {
            return i;
        }
    }
    return -1;
}

int SearchSortEngine::binarySearch(const Book arr[], int n, const string& targetISBN, long long& comparisons) {
    comparisons = 0;
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid].isbn == targetISBN) {
            return mid;
        }
        if (arr[mid].isbn < targetISBN) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void SearchSortEngine::bubbleSort(Book arr[], int n, long long& comparisons, long long& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j].isbn > arr[j + 1].isbn) {
                Book temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void SearchSortEngine::selectionSort(Book arr[], int n, long long& comparisons, long long& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j].isbn < arr[minIdx].isbn) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Book temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            swaps++;
        }
    }
}

void SearchSortEngine::insertionSort(Book arr[], int n, long long& comparisons, long long& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 1; i < n; i++) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j].isbn > key.isbn) {
                arr[j + 1] = arr[j];
                swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}
