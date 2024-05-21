#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>  // Adicionar este cabeçalho para std::iota
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "Metrics.h"

using namespace std;
using namespace chrono;

// Funções para gerar arranjos
vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 0);  // std::iota preenche o array com valores sequenciais
    return arr;
}

vector<int> generateReversedArray(int size) {
    vector<int> arr(size);
    iota(arr.rbegin(), arr.rend(), 0);  // std::iota preenche o array com valores sequenciais em ordem reversa
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
void testSortingAlgorithm(Metrics (*sortFunction)(vector<int>&), vector<int>& arr, ofstream& outputFile, const string& algorithmName, const string& arrayType, int size) {
    Metrics metrics = sortFunction(arr);
    outputFile << algorithmName << "," << arrayType << "," << size << "," << metrics.comparisons << "," << metrics.movements << "," << metrics.time_us << endl;
}

int main() {
    ofstream outputFile("sorting_results.csv");
    outputFile << "Algorithm,ArrayType,Size,Comparisons,Movements,Time(us)" << endl;

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

        // Outros testes de algoritmos serão adicionados aqui posteriormente
    }

    outputFile.close();
    return 0;
}
