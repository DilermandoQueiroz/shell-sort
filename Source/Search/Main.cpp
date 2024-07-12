#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include <linearSearch.h>
#include <binarySearch.h>
#include <binarySearchTree.h>
#include <AVLTree.h>
#include <redBlackTree.h>
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

// Função para testar um algoritmo de busca
void testSearchAlgorithm(Metrics (*searchFunction)(const vector<int>&, int), vector<int>& arr, int target, ofstream& outputFile, const string& algorithmName, const string& arrayType, int size) {
    try {
        cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << endl;
        Metrics metrics = searchFunction(arr, target);
        outputFile << algorithmName << "," << arrayType << "," << size << "," << metrics.comparisons << "," << metrics.movements << "," << metrics.time_us << endl;
        cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << endl;
    } catch (const exception& e) {
        cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << endl;
    }
}

int main() {
    ofstream outputFile("search_results.csv");
    outputFile << "Algorithm,ArrayType,Size,Comparisons,Movements,Time(us)" << endl;

    vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};
    for (int size : sizes) {
        cerr << "Processando arrays de tamanho " << size << endl;

        // Gerar arrays
        vector<int> sortedArray = generateSortedArray(size);
        vector<int> reversedArray = generateReversedArray(size);
        vector<int> almostSortedArray = generateAlmostSortedArray(size);
        vector<int> randomArray = generateRandomArray(size);
        int target = randomArray[size / 2];

        // Testar LinearSearch
        testSearchAlgorithm(linearSearch, sortedArray, target, outputFile, "LinearSearch", "Sorted", size);
        testSearchAlgorithm(linearSearch, reversedArray, target, outputFile, "LinearSearch", "Reversed", size);
        testSearchAlgorithm(linearSearch, almostSortedArray, target, outputFile, "LinearSearch", "AlmostSorted", size);
        testSearchAlgorithm(linearSearch, randomArray, target, outputFile, "LinearSearch", "Random", size);

        // Testar BinarySearch
        testSearchAlgorithm(binarySearch, sortedArray, target, outputFile, "BinarySearch", "Sorted", size);
        testSearchAlgorithm(binarySearch, reversedArray, target, outputFile, "BinarySearch", "Reversed", size);
        testSearchAlgorithm(binarySearch, almostSortedArray, target, outputFile, "BinarySearch", "AlmostSorted", size);
        testSearchAlgorithm(binarySearch, randomArray, target, outputFile, "BinarySearch", "Random", size);

        // Testar BinarySearchTree
        BinarySearchTree bst;
        for (int val : sortedArray) bst.insert(val);
        Metrics bstMetrics = bst.search(target);
        outputFile << "BinarySearchTree,Sorted," << size << "," << bstMetrics.comparisons << "," << bstMetrics.movements << "," << bstMetrics.time_us << endl;

        for (int val : reversedArray) bst.insert(val);
        bstMetrics = bst.search(target);
        outputFile << "BinarySearchTree,Reversed," << size << "," << bstMetrics.comparisons << "," << bstMetrics.movements << "," << bstMetrics.time_us << endl;

        for (int val : almostSortedArray) bst.insert(val);
        bstMetrics = bst.search(target);
        outputFile << "BinarySearchTree,AlmostSorted," << size << "," << bstMetrics.comparisons << "," << bstMetrics.movements << "," << bstMetrics.time_us << endl;

        for (int val : randomArray) bst.insert(val);
        bstMetrics = bst.search(target);
        outputFile << "BinarySearchTree,Random," << size << "," << bstMetrics.comparisons << "," << bstMetrics.movements << "," << bstMetrics.time_us << endl;

        // Testar AVLTree
        AVLTree avl;
        for (int val : sortedArray) avl.insert(val);
        Metrics avlMetrics = avl.search(target);
        outputFile << "AVLTree,Sorted," << size << "," << avlMetrics.comparisons << "," << avlMetrics.movements << "," << avlMetrics.time_us << endl;

        for (int val : reversedArray) avl.insert(val);
        avlMetrics = avl.search(target);
        outputFile << "AVLTree,Reversed," << size << "," << avlMetrics.comparisons << "," << avlMetrics.movements << "," << avlMetrics.time_us << endl;

        for (int val : almostSortedArray) avl.insert(val);
        avlMetrics = avl.search(target);
        outputFile << "AVLTree,AlmostSorted," << size << "," << avlMetrics.comparisons << "," << avlMetrics.movements << "," << avlMetrics.time_us << endl;

        for (int val : randomArray) avl.insert(val);
        avlMetrics = avl.search(target);
        outputFile << "AVLTree,Random," << size << "," << avlMetrics.comparisons << "," << avlMetrics.movements << "," << avlMetrics.time_us << endl;

        // Testar RedBlackTree
        RedBlackTree rbt;
        for (int val : sortedArray) rbt.insert(val);
        Metrics rbtMetrics = rbt.search(target);
        outputFile << "RedBlackTree,Sorted," << size << "," << rbtMetrics.comparisons << "," << rbtMetrics.movements << "," << rbtMetrics.time_us << endl;

        for (int val : reversedArray) rbt.insert(val);
        rbtMetrics = rbt.search(target);
        outputFile << "RedBlackTree,Reversed," << size << "," << rbtMetrics.comparisons << "," << rbtMetrics.movements << "," << rbtMetrics.time_us << endl;

        for (int val : almostSortedArray) rbt.insert(val);
        rbtMetrics = rbt.search(target);
        outputFile << "RedBlackTree,AlmostSorted," << size << "," << rbtMetrics.comparisons << "," << rbtMetrics.movements << "," << rbtMetrics.time_us << endl;

        for (int val : randomArray) rbt.insert(val);
        rbtMetrics = rbt.search(target);
        outputFile << "RedBlackTree,Random," << size << "," << rbtMetrics.comparisons << "," << rbtMetrics.movements << "," << rbtMetrics.time_us << endl;

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