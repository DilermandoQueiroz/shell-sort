#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include "LinearSearch.h"
#include "BinarySearch.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "Metrics.h"
#include "FingerTree.h"

// Funções para gerar arranjos
std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr(size);
    std::iota(arr.begin(), arr.end(), 1);
    return arr;
}

std::vector<int> generateReversedArray(int size) {
    std::vector<int> arr(size);
    std::iota(arr.rbegin(), arr.rend(), 1);
    return arr;
}

std::vector<int> generateAlmostSortedArray(int size) {
    std::vector<int> arr = generateSortedArray(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < size / 10; ++i) {
        std::swap(arr[gen() % size], arr[gen() % size]);
    }
    return arr;
}

std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, size);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Função para testar um algoritmo de busca
void testSearchAlgorithm(Metrics (*searchFunction)(const std::vector<int>&, int),
                         std::vector<int>& arr, 
                         std::ofstream& outputFile, 
                         const std::string& algorithmName, 
                         const std::string& arrayType, 
                         int size, 
                         int target) {
    try {
        std::cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << std::endl;
        
        if (!outputFile) {
            throw std::runtime_error("Arquivo de saída não está aberto");
        }

        Metrics searchMetrics = searchFunction(arr, target);
        searchMetrics.algorithm = algorithmName;
        searchMetrics.arrayType = arrayType;
        searchMetrics.size = size;

        if (searchMetrics.algorithm.empty() || searchMetrics.arrayType.empty()) {
            throw std::runtime_error("Strings não foram inicializadas corretamente");
        }

        outputFile << searchMetrics.algorithm << "," << searchMetrics.arrayType << "," << searchMetrics.size << "," << searchMetrics.comparisons << "," << searchMetrics.movements << "," << searchMetrics.time_us << std::endl;

        std::cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << std::endl;
    }
}

// Função para testar um algoritmo de inserção e remoção
void testInsertRemoveAlgorithm(Metrics (*insertFunction)(std::vector<int>&, int),
                               Metrics (*removeFunction)(std::vector<int>&, int),
                               std::vector<int>& arr, 
                               std::ofstream& outputFile, 
                               const std::string& algorithmName, 
                               const std::string& arrayType, 
                               int size, 
                               int target) {
    try {
        std::cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << std::endl;

        if (!outputFile) {
            throw std::runtime_error("Arquivo de saída não está aberto");
        }

        // Testar inserção
        Metrics insertMetrics = insertFunction(arr, target);
        insertMetrics.algorithm = algorithmName + "Insert";
        insertMetrics.arrayType = arrayType;
        insertMetrics.size = size;

        // Testar remoção
        Metrics removeMetrics = removeFunction(arr, target);
        removeMetrics.algorithm = algorithmName + "Remove";
        removeMetrics.arrayType = arrayType;
        removeMetrics.size = size;

        // Registrar métricas no arquivo
        outputFile << insertMetrics.algorithm << "," << insertMetrics.arrayType << "," << insertMetrics.size << "," << insertMetrics.comparisons << "," << insertMetrics.movements << "," << insertMetrics.time_us << std::endl;
        outputFile << removeMetrics.algorithm << "," << removeMetrics.arrayType << "," << removeMetrics.size << "," << removeMetrics.comparisons << "," << removeMetrics.movements << "," << removeMetrics.time_us << std::endl;

        std::cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << std::endl;
    }
}

// Função para testar um algoritmo de inserção e remoção (para AVLTree e BinarySearchTree)
template <typename TreeType>
void testInsertRemoveAlgorithmTree(Metrics (TreeType::*insertFunction)(int),
                                   Metrics (TreeType::*removeFunction)(int),
                                   TreeType& tree, 
                                   std::vector<int>& arr, 
                                   std::ofstream& outputFile, 
                                   const std::string& algorithmName, 
                                   const std::string& arrayType, 
                                   int size, 
                                   int target) {
    try {
        std::cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << std::endl;
        
        if (!outputFile) {
            throw std::runtime_error("Arquivo de saída não está aberto");
        }

        // Métricas de inserção
        Metrics totalInsertMetrics = {algorithmName + "Insert", arrayType, size, 0, 0, 0.0};
        auto start = std::chrono::high_resolution_clock::now();
        for (const auto& value : arr) {
            Metrics insertMetrics = (tree.*insertFunction)(value);
            totalInsertMetrics.comparisons += insertMetrics.comparisons;
            totalInsertMetrics.movements += insertMetrics.movements;
        }
        auto end = std::chrono::high_resolution_clock::now();
        totalInsertMetrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        outputFile << totalInsertMetrics.algorithm << "," << totalInsertMetrics.arrayType << "," << totalInsertMetrics.size << "," << totalInsertMetrics.comparisons << "," << totalInsertMetrics.movements << "," << totalInsertMetrics.time_us << std::endl;

        // Métricas de remoção
        Metrics totalRemoveMetrics = {algorithmName + "Remove", arrayType, size, 0, 0, 0.0};
        start = std::chrono::high_resolution_clock::now();
        for (const auto& value : arr) {
            Metrics removeMetrics = (tree.*removeFunction)(value);
            totalRemoveMetrics.comparisons += removeMetrics.comparisons;
            totalRemoveMetrics.movements += removeMetrics.movements;
        }
        end = std::chrono::high_resolution_clock::now();
        totalRemoveMetrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        outputFile << totalRemoveMetrics.algorithm << "," << totalRemoveMetrics.arrayType << "," << totalRemoveMetrics.size << "," << totalRemoveMetrics.comparisons << "," << totalRemoveMetrics.movements << "," << totalRemoveMetrics.time_us << std::endl;

        std::cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << std::endl;
    }
}

// Função para testar um algoritmo de inserção e remoção (para FingerTree)
void testInsertRemoveAlgorithmFingerTree(Metrics (FingerTree::*insertFunction)(int),
                                   Metrics (FingerTree::*removeFunction)(int),
                                   FingerTree& tree, 
                                   std::vector<int>& arr, 
                                   std::ofstream& outputFile, 
                                   const std::string& algorithmName, 
                                   const std::string& arrayType, 
                                   int size, 
                                   int target) {
    try {
        std::cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << std::endl;
        
        if (!outputFile) {
            throw std::runtime_error("Arquivo de saída não está aberto");
        }

        // Métricas de inserção
        Metrics totalInsertMetrics = {algorithmName + "Insert", arrayType, size, 0, 0, 0.0};
        auto start = std::chrono::high_resolution_clock::now();
        for (const auto& value : arr) {
            Metrics insertMetrics = (tree.*insertFunction)(value);
            totalInsertMetrics.comparisons += insertMetrics.comparisons;
            totalInsertMetrics.movements += insertMetrics.movements;
        }
        auto end = std::chrono::high_resolution_clock::now();
        totalInsertMetrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        outputFile << totalInsertMetrics.algorithm << "," << totalInsertMetrics.arrayType << "," << totalInsertMetrics.size << "," << totalInsertMetrics.comparisons << "," << totalInsertMetrics.movements << "," << totalInsertMetrics.time_us << std::endl;

        // Métricas de remoção
        Metrics totalRemoveMetrics = {algorithmName + "Remove", arrayType, size, 0, 0, 0.0};
        start = std::chrono::high_resolution_clock::now();
        for (const auto& value : arr) {
            Metrics removeMetrics = (tree.*removeFunction)(value);
            totalRemoveMetrics.comparisons += removeMetrics.comparisons;
            totalRemoveMetrics.movements += removeMetrics.movements;
        }
        end = std::chrono::high_resolution_clock::now();
        totalRemoveMetrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        outputFile << totalRemoveMetrics.algorithm << "," << totalRemoveMetrics.arrayType << "," << totalRemoveMetrics.size << "," << totalRemoveMetrics.comparisons << "," << totalRemoveMetrics.movements << "," << totalRemoveMetrics.time_us << std::endl;

        std::cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << std::endl;
    }
}

int main() {
    std::ofstream outputFile("search_results.csv");
    outputFile << "Algorithm,ArrayType,Size,Comparisons,Movements,Time(us)" << std::endl;

    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};
    int target = 1; // Elemento que será buscado/removido

    for (int size : sizes) {
        std::cerr << "Processando arrays de tamanho " << size << std::endl;

        // Gerar arrays
        std::vector<int> sortedArray = generateSortedArray(size);
        std::vector<int> reversedArray = generateReversedArray(size);
        std::vector<int> almostSortedArray = generateAlmostSortedArray(size);
        std::vector<int> randomArray = generateRandomArray(size);

        // Testar LinearSearch
        testSearchAlgorithm(linearSearch, sortedArray, outputFile, "LinearSearch", "Sorted", size, target);
        testSearchAlgorithm(linearSearch, reversedArray, outputFile, "LinearSearch", "Reversed", size, target);
        testSearchAlgorithm(linearSearch, almostSortedArray, outputFile, "LinearSearch", "AlmostSorted", size, target);
        testSearchAlgorithm(linearSearch, randomArray, outputFile, "LinearSearch", "Random", size, target);

        testInsertRemoveAlgorithm(linearInsert, linearRemove, sortedArray, outputFile, "LinearSearch", "Sorted", size, target);
        testInsertRemoveAlgorithm(linearInsert, linearRemove, reversedArray, outputFile, "LinearSearch", "Reversed", size, target);
        testInsertRemoveAlgorithm(linearInsert, linearRemove, almostSortedArray, outputFile, "LinearSearch", "AlmostSorted", size, target);
        testInsertRemoveAlgorithm(linearInsert, linearRemove, randomArray, outputFile, "LinearSearch", "Random", size, target);

        // Testar BinarySearch
        testSearchAlgorithm(binarySearch, sortedArray, outputFile, "BinarySearch", "Sorted", size, target);
        testSearchAlgorithm(binarySearch, reversedArray, outputFile, "BinarySearch", "Reversed", size, target);
        testSearchAlgorithm(binarySearch, almostSortedArray, outputFile, "BinarySearch", "AlmostSorted", size, target);
        testSearchAlgorithm(binarySearch, randomArray, outputFile, "BinarySearch", "Random", size, target);

        // Testar AVLTree
        AVLTree avlTree;
        testInsertRemoveAlgorithmTree(&AVLTree::insert, &AVLTree::remove, avlTree, sortedArray, outputFile, "AVLTree", "Sorted", size, target);
        avlTree = AVLTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmTree(&AVLTree::insert, &AVLTree::remove, avlTree, reversedArray, outputFile, "AVLTree", "Reversed", size, target);
        avlTree = AVLTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmTree(&AVLTree::insert, &AVLTree::remove, avlTree, almostSortedArray, outputFile, "AVLTree", "AlmostSorted", size, target);
        avlTree = AVLTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmTree(&AVLTree::insert, &AVLTree::remove, avlTree, randomArray, outputFile, "AVLTree", "Random", size, target);

        // Testar FingerTree
        FingerTree fingerTree;
        testInsertRemoveAlgorithmFingerTree(&FingerTree::insert, &FingerTree::remove, fingerTree, sortedArray, outputFile, "FingerTree", "Sorted", size, target);
        fingerTree = FingerTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmFingerTree(&FingerTree::insert, &FingerTree::remove, fingerTree, reversedArray, outputFile, "FingerTree", "Reversed", size, target);
        fingerTree = FingerTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmFingerTree(&FingerTree::insert, &FingerTree::remove, fingerTree, almostSortedArray, outputFile, "FingerTree", "AlmostSorted", size, target);
        fingerTree = FingerTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmFingerTree(&FingerTree::insert, &FingerTree::remove, fingerTree, randomArray, outputFile, "FingerTree", "Random", size, target);

        // Testar BinarySearchTree
        BinarySearchTree bst;
        testInsertRemoveAlgorithmTree(&BinarySearchTree::insert, &BinarySearchTree::remove, bst, sortedArray, outputFile, "BinarySearchTree", "Sorted", size, target);
        bst = BinarySearchTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmTree(&BinarySearchTree::insert, &BinarySearchTree::remove, bst, reversedArray, outputFile, "BinarySearchTree", "Reversed", size, target);
        bst = BinarySearchTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmTree(&BinarySearchTree::insert, &BinarySearchTree::remove, bst, almostSortedArray, outputFile, "BinarySearchTree", "AlmostSorted", size, target);
        bst = BinarySearchTree(); // Reiniciar a árvore para o próximo teste
        testInsertRemoveAlgorithmTree(&BinarySearchTree::insert, &BinarySearchTree::remove, bst, randomArray, outputFile, "BinarySearchTree", "Random", size, target);

        // Liberação de memória
        sortedArray.clear();
        reversedArray.clear();
        almostSortedArray.clear();
        randomArray.clear();
        sortedArray.shrink_to_fit();
        reversedArray.shrink_to_fit();
        almostSortedArray.shrink_to_fit();
        randomArray.shrink_to_fit();

        std::cerr << "Processamento de arrays de tamanho " << size << " finalizado" << std::endl;
    }

    outputFile.close();
    std::cerr << "Programa finalizado" << std::endl;
    return 0;
}
