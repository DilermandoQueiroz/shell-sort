#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std;
using namespace chrono;

// Funções para gerar arranjos
vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 0);
    return arr;
}

vector<int> generateReversedArray(int size) {
    vector<int> arr(size);
    iota(arr.rbegin(), arr.rend(), 0);
    return arr;
}

vector<int> generateAlmostSortedArray(int size) {
    vector<int> arr = generateSortedArray(size);
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < size / 10; ++i) {
        swap(arr[gen() % size], arr[gen() % size]);
    }
    return arr;
}

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, size);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Função para testar um algoritmo de ordenação
void testSortingAlgorithm(void (*sortFunction)(vector<int>&), vector<int>& arr, ofstream& outputFile, const string& algorithmName, const string& arrayType, int size) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    double duration = duration_cast<microseconds>(end - start).count();

    outputFile << algorithmName << "," << arrayType << "," << size << "," << duration << endl;
}

int main() {
    ofstream outputFile("sorting_results.csv");
    outputFile << "Algorithm,ArrayType,Size,Time(us)" << endl;

    vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};
    for (int size : sizes) {
        vector<int> sortedArray = generateSortedArray(size);
        vector<int> reversedArray = generateReversedArray(size);
        vector<int> almostSortedArray = generateAlmostSortedArray(size);
        vector<int> randomArray = generateRandomArray(size);

        // Test InsertionSort
        testSortingAlgorithm(insertionSort, sortedArray, outputFile, "InsertionSort", "Sorted", size);
        testSortingAlgorithm(insertionSort, reversedArray, outputFile, "InsertionSort", "Reversed", size);
        testSortingAlgorithm(insertionSort, almostSortedArray, outputFile, "InsertionSort", "AlmostSorted", size);
        testSortingAlgorithm(insertionSort, randomArray, outputFile, "InsertionSort", "Random", size);

        // Test SelectionSort
        testSortingAlgorithm(selectionSort, sortedArray, outputFile, "SelectionSort", "Sorted", size);
        testSortingAlgorithm(selectionSort, reversedArray, outputFile, "SelectionSort", "Reversed", size);
        testSortingAlgorithm(selectionSort, almostSortedArray, outputFile, "SelectionSort", "AlmostSorted", size);
        testSortingAlgorithm(selectionSort, randomArray, outputFile, "SelectionSort", "Random", size);

        // Test BubbleSort
        testSortingAlgorithm(bubbleSort, sortedArray, outputFile, "BubbleSort", "Sorted", size);
        testSortingAlgorithm(bubbleSort, reversedArray, outputFile, "BubbleSort", "Reversed", size);
        testSortingAlgorithm(bubbleSort, almostSortedArray, outputFile, "BubbleSort", "AlmostSorted", size);
        testSortingAlgorithm(bubbleSort, randomArray, outputFile, "BubbleSort", "Random", size);

        // Test HeapSort
        testSortingAlgorithm(heapSort, sortedArray, outputFile, "HeapSort", "Sorted", size);
        testSortingAlgorithm(heapSort, reversedArray, outputFile, "HeapSort", "Reversed", size);
        testSortingAlgorithm(heapSort, almostSortedArray, outputFile, "HeapSort", "AlmostSorted", size);
        testSortingAlgorithm(heapSort, randomArray, outputFile, "HeapSort", "Random", size);

        // Test MergeSort
        testSortingAlgorithm(mergeSort, sortedArray, outputFile, "MergeSort", "Sorted", size);
        testSortingAlgorithm(mergeSort, reversedArray, outputFile, "MergeSort", "Reversed", size);
        testSortingAlgorithm(mergeSort, almostSortedArray, outputFile, "MergeSort", "AlmostSorted", size);
        testSortingAlgorithm(mergeSort, randomArray, outputFile, "MergeSort", "Random", size);

        // Test QuickSort
        testSortingAlgorithm(quickSort, sortedArray, outputFile, "QuickSort", "Sorted", size);
        testSortingAlgorithm(quickSort, reversedArray, outputFile, "QuickSort", "Reversed", size);
        testSortingAlgorithm(quickSort, almostSortedArray, outputFile, "QuickSort", "AlmostSorted", size);
        testSortingAlgorithm(quickSort, randomArray, outputFile, "QuickSort", "Random", size);
    }

    outputFile.close();
    return 0;
}
