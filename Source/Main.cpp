#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "Metrics.h"

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
void testSortingAlgorithm(Metrics (*sortFunction)(vector<int>&), vector<int>& arr, ofstream& outputFile, const string& algorithmName, const string& arrayType, int size) {
    try {
        cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << endl;
        Metrics metrics = sortFunction(arr);
        outputFile << algorithmName << "," << arrayType << "," << size << "," << metrics.comparisons << "," << metrics.movements << "," << metrics.time_us << endl;
        cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << endl;
    } catch (const exception& e) {
        cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << endl;
    }
}

int main() {
    ofstream outputFile("sorting_results.csv");
    outputFile << "Algorithm,ArrayType,Size,Comparisons,Movements,Time(us)" << endl;

    vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};
    for (int size : sizes) {
        cerr << "Processando arrays de tamanho " << size << endl;

        // Gerar arrays
        vector<int> sortedArray = generateSortedArray(size);
        vector<int> reversedArray = generateReversedArray(size);
        vector<int> almostSortedArray = generateAlmostSortedArray(size);
        vector<int> randomArray = generateRandomArray(size);

        // Testar InsertionSort
        testSortingAlgorithm(insertionSort, sortedArray, outputFile, "InsertionSort", "Sorted", size);
        testSortingAlgorithm(insertionSort, reversedArray, outputFile, "InsertionSort", "Reversed", size);
        testSortingAlgorithm(insertionSort, almostSortedArray, outputFile, "InsertionSort", "AlmostSorted", size);
        testSortingAlgorithm(insertionSort, randomArray, outputFile, "InsertionSort", "Random", size);

        // Testar BubbleSort
        testSortingAlgorithm(bubbleSort, sortedArray, outputFile, "BubbleSort", "Sorted", size);
        testSortingAlgorithm(bubbleSort, reversedArray, outputFile, "BubbleSort", "Reversed", size);
        testSortingAlgorithm(bubbleSort, almostSortedArray, outputFile, "BubbleSort", "AlmostSorted", size);
        testSortingAlgorithm(bubbleSort, randomArray, outputFile, "BubbleSort", "Random", size);

        // Testar HeapSort
        testSortingAlgorithm(heapSort, sortedArray, outputFile, "HeapSort", "Sorted", size);
        testSortingAlgorithm(heapSort, reversedArray, outputFile, "HeapSort", "Reversed", size);
        testSortingAlgorithm(heapSort, almostSortedArray, outputFile, "HeapSort", "AlmostSorted", size);
        testSortingAlgorithm(heapSort, randomArray, outputFile, "HeapSort", "Random", size);

        // Testar MergeSort
        testSortingAlgorithm(mergeSort, sortedArray, outputFile, "MergeSort", "Sorted", size);
        testSortingAlgorithm(mergeSort, reversedArray, outputFile, "MergeSort", "Reversed", size);
        testSortingAlgorithm(mergeSort, almostSortedArray, outputFile, "MergeSort", "AlmostSorted", size);
        testSortingAlgorithm(mergeSort, randomArray, outputFile, "MergeSort", "Random", size);

        // Testar QuickSort
        testSortingAlgorithm(quickSort, sortedArray, outputFile, "QuickSort", "Sorted", size);
        testSortingAlgorithm(quickSort, reversedArray, outputFile, "QuickSort", "Reversed", size);
        testSortingAlgorithm(quickSort, almostSortedArray, outputFile, "QuickSort", "AlmostSorted", size);
        testSortingAlgorithm(quickSort, randomArray, outputFile, "QuickSort", "Random", size);

        // Testar ShellSort
        testSortingAlgorithm(shellSort, sortedArray, outputFile, "ShellSort", "Sorted", size);
        testSortingAlgorithm(shellSort, reversedArray, outputFile, "ShellSort", "Reversed", size);
        testSortingAlgorithm(shellSort, almostSortedArray, outputFile, "ShellSort", "AlmostSorted", size);
        testSortingAlgorithm(shellSort, randomArray, outputFile, "ShellSort", "Random", size);

        // Liberação de memória
        sortedArray.clear();
        reversedArray.clear();
        almostSortedArray.clear();
        randomArray.clear();
        sortedArray.shrink_to_fit();
        reversedArray.shrink_to_fit();
        almostSortedArray.shrink_to_fit();
        randomArray.shrink_to_fit();

        cerr << "Processamento de arrays de tamanho " << size << " finalizado" << endl;
    }

    outputFile.close();
    cerr << "Programa finalizado" << endl;
    return 0;
}
