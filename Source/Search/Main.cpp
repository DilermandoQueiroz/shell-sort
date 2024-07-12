#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include "linearSearch.h"
#include "binarySearch.h"
#include "binarySearchTree.h"
#include "AVLTree.h"
#include "redBlackTree.h"
#include "metrics.h"

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

// Função para testar inserção, remoção e busca em árvores
template <typename Tree>
void testTreeOperations(Tree& tree, const vector<int>& arr, int additionalValue, int target, ofstream& outputFile, const string& treeName, const string& arrayType, int size) {
    try {
        // Construir a árvore com os valores iniciais
        for (int val : arr) {
            tree.insert(val);
        }

        // Inserção de um valor adicional
        Metrics insertMetrics = tree.insert(additionalValue);
        outputFile << treeName << "_Insert," << arrayType << "," << size << "," << insertMetrics.comparisons << "," << insertMetrics.movements << "," << insertMetrics.time_us << endl;

        // Busca
        Metrics searchMetrics = tree.search(target);
        outputFile << treeName << "_Search," << arrayType << "," << size << "," << searchMetrics.comparisons << "," << searchMetrics.movements << "," << searchMetrics.time_us << endl;

        // Remoção
        Metrics removeMetrics = tree.remove(target);
        outputFile << treeName << "_Remove," << arrayType << "," << size << "," << removeMetrics.comparisons << "," << removeMetrics.movements << "," << removeMetrics.time_us << endl;

    } catch (const exception& e) {
        cerr << "Erro ao testar " << treeName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << endl;
    }
}

// Função para testar busca em arrays
void testSearchFunction(Metrics (*searchFunction)(const vector<int>&, int), const vector<int>& arr, int target, ofstream& outputFile, const string& functionName, const string& arrayType, int size) {
    try {
        cerr << "Testando " << functionName << " no array " << arrayType << " de tamanho " << size << endl;
        Metrics metrics = searchFunction(arr, target);
        outputFile << functionName << "," << arrayType << "," << size << "," << metrics.comparisons << "," << metrics.movements << "," << metrics.time_us << endl;
        cerr << functionName << " no array " << arrayType << " de tamanho " << size << " completado" << endl;
    } catch (const exception& e) {
        cerr << "Erro ao testar " << functionName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << endl;
    }
}

int main() {
    ofstream outputFile("search_results.csv");
    outputFile << "Operation,ArrayType,Size,Comparisons,Movements,Time(us)" << endl;

    vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};
    for (int size : sizes) {
        cerr << "Processando arrays de tamanho " << size << endl;

        // Gerar arrays
        vector<int> sortedArray = generateSortedArray(size);
        vector<int> reversedArray = generateReversedArray(size);
        vector<int> almostSortedArray = generateAlmostSortedArray(size);
        vector<int> randomArray = generateRandomArray(size);
        int target = sortedArray[size / 2]; // Um valor presente nos arrays
        int additionalValue = size + 1; // Um valor que será inserido adicionalmente

        // Testar LinearSearch
        testSearchFunction(linearSearch, sortedArray, target, outputFile, "LinearSearch", "Sorted", size);
        testSearchFunction(linearSearch, reversedArray, target, outputFile, "LinearSearch", "Reversed", size);
        testSearchFunction(linearSearch, almostSortedArray, target, outputFile, "LinearSearch", "AlmostSorted", size);
        testSearchFunction(linearSearch, randomArray, target, outputFile, "LinearSearch", "Random", size);

        // Testar BinarySearch
        testSearchFunction(binarySearch, sortedArray, target, outputFile, "BinarySearch", "Sorted", size);
        testSearchFunction(binarySearch, reversedArray, target, outputFile, "BinarySearch", "Reversed", size);
        testSearchFunction(binarySearch, almostSortedArray, target, outputFile, "BinarySearch", "AlmostSorted", size);
        testSearchFunction(binarySearch, randomArray, target, outputFile, "BinarySearch", "Random", size);

        // Testar BinarySearchTree
        {
            BinarySearchTree bst;
            testTreeOperations(bst, sortedArray, additionalValue, target, outputFile, "BinarySearchTree", "Sorted", size);
            testTreeOperations(bst, reversedArray, additionalValue, target, outputFile, "BinarySearchTree", "Reversed", size);
            testTreeOperations(bst, almostSortedArray, additionalValue, target, outputFile, "BinarySearchTree", "AlmostSorted", size);
            testTreeOperations(bst, randomArray, additionalValue, target, outputFile, "BinarySearchTree", "Random", size);
        }

        // Testar AVLTree
        {
            AVLTree avl;
            testTreeOperations(avl, sortedArray, additionalValue, target, outputFile, "AVLTree", "Sorted", size);
            testTreeOperations(avl, reversedArray, additionalValue, target, outputFile, "AVLTree", "Reversed", size);
            testTreeOperations(avl, almostSortedArray, additionalValue, target, outputFile, "AVLTree", "AlmostSorted", size);
            testTreeOperations(avl, randomArray, additionalValue, target, outputFile, "AVLTree", "Random", size);
        }

        // Testar RedBlackTree
        {
            RedBlackTree rbt;
            testTreeOperations(rbt, sortedArray, additionalValue, target, outputFile, "RedBlackTree", "Sorted", size);
            testTreeOperations(rbt, reversedArray, additionalValue, target, outputFile, "RedBlackTree", "Reversed", size);
            testTreeOperations(rbt, almostSortedArray, additionalValue, target, outputFile, "RedBlackTree", "AlmostSorted", size);
            testTreeOperations(rbt, randomArray, additionalValue, target, outputFile, "RedBlackTree", "Random", size);
        }

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