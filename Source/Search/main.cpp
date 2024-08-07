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
#include "Metrics.h"
#include "FingerTree.h"

// Funções para gerar arranjos
std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr(size);
    std::iota(arr.begin(), arr.end(), 1); // Garante que o array começa de 1 a size
    return arr;
}

std::vector<int> generateReversedArray(int size) {
    std::vector<int> arr(size);
    std::iota(arr.rbegin(), arr.rend(), 1); // Garante que o array começa de size a 1
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

        auto start = std::chrono::high_resolution_clock::now();
        Metrics searchMetrics = searchFunction(arr, target);
        auto end = std::chrono::high_resolution_clock::now();
        searchMetrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        searchMetrics.algorithm = algorithmName;
        searchMetrics.arrayType = arrayType;
        searchMetrics.size = size;

        outputFile << searchMetrics.algorithm << "," << searchMetrics.arrayType << "," << searchMetrics.size << "," << searchMetrics.comparisons << "," << searchMetrics.movements << "," << searchMetrics.time_us << std::endl;

        std::cerr << "Tempo de busca (us): " << searchMetrics.time_us << std::endl;
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

// Função para testar busca em AVLTree e BinarySearchTree
template <typename TreeType>
void testSearchAlgorithmTree(Metrics (TreeType::*searchFunction)(int),
                             TreeType& tree, 
                             int target,
                             std::ofstream& outputFile, 
                             const std::string& algorithmName, 
                             const std::string& arrayType, 
                             int size) {
    try {
        std::cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << std::endl;

        if (!outputFile) {
            throw std::runtime_error("Arquivo de saída não está aberto");
        }

        auto start = std::chrono::high_resolution_clock::now();
        Metrics searchMetrics = (tree.*searchFunction)(target);
        auto end = std::chrono::high_resolution_clock::now();
        searchMetrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        searchMetrics.algorithm = algorithmName;
        searchMetrics.arrayType = arrayType;
        searchMetrics.size = size;

        outputFile << searchMetrics.algorithm << "," << searchMetrics.arrayType << "," << searchMetrics.size << "," << searchMetrics.comparisons << "," << searchMetrics.movements << "," << searchMetrics.time_us << std::endl;

        std::cerr << "Tempo de busca (us): " << searchMetrics.time_us << std::endl;
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
        auto remove_end = std::chrono::high_resolution_clock::now(); // Renomear para evitar conflito
        totalRemoveMetrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(remove_end - start).count();
        outputFile << totalRemoveMetrics.algorithm << "," << totalRemoveMetrics.arrayType << "," << totalRemoveMetrics.size << "," << totalRemoveMetrics.comparisons << "," << totalRemoveMetrics.movements << "," << totalRemoveMetrics.time_us << std::endl;

        std::cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << std::endl;
    }
}

// Função para testar busca em FingerTree
void testSearchAlgorithmFingerTree(Metrics (FingerTree::*searchFunction)(int),
                                   FingerTree& tree, 
                                   int target,
                                   std::ofstream& outputFile, 
                                   const std::string& algorithmName, 
                                   const std::string& arrayType, 
                                   int size) {
    try {
        std::cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << std::endl;

        if (!outputFile) {
            throw std::runtime_error("Arquivo de saída não está aberto");
        }

        auto start = std::chrono::high_resolution_clock::now();
        Metrics searchMetrics = (tree.*searchFunction)(target);
        auto end = std::chrono::high_resolution_clock::now();
        searchMetrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        searchMetrics.algorithm = algorithmName;
        searchMetrics.arrayType = arrayType;
        searchMetrics.size = size;

        outputFile << searchMetrics.algorithm << "," << searchMetrics.arrayType << "," << searchMetrics.size << "," << searchMetrics.comparisons << "," << searchMetrics.movements << "," << searchMetrics.time_us << std::endl;

        std::cerr << "Tempo de busca (us): " << searchMetrics.time_us << std::endl;
        std::cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << std::endl;
    }
}

int main() {
    std::ofstream outputFile("results.csv");
    outputFile << "Algorithm,ArrayType,Size,Comparisons,Movements,Time(us)" << std::endl;

    std::vector<int> sizes = {10, 100, 1000, 10000, 100000};
    int target = 50000; // Elemento que será buscado/removido (um valor que está aproximadamente no meio do array)

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

        // Testar BinarySearch (apenas arrays ordenados)
        testSearchAlgorithm(binarySearch, sortedArray, outputFile, "BinarySearch", "Sorted", size, target);

        // Testar AVLTree
        AVLTree avlTree;
        testInsertRemoveAlgorithmTree(&AVLTree::insert, &AVLTree::remove, avlTree, sortedArray, outputFile, "AVLTree", "Sorted", size, target);
        testSearchAlgorithmTree(&AVLTree::search, avlTree, target, outputFile, "AVLTreeSearch", "Sorted", size);
        avlTree = AVLTree(); // Reiniciar a árvore para o próximo teste

        testInsertRemoveAlgorithmTree(&AVLTree::insert, &AVLTree::remove, avlTree, reversedArray, outputFile, "AVLTree", "Reversed", size, target);
        testSearchAlgorithmTree(&AVLTree::search, avlTree, target, outputFile, "AVLTreeSearch", "Reversed", size);
        avlTree = AVLTree(); // Reiniciar a árvore para o próximo teste

        testInsertRemoveAlgorithmTree(&AVLTree::insert, &AVLTree::remove, avlTree, almostSortedArray, outputFile, "AVLTree", "AlmostSorted", size, target);
        testSearchAlgorithmTree(&AVLTree::search, avlTree, target, outputFile, "AVLTreeSearch", "AlmostSorted", size);
        avlTree = AVLTree(); // Reiniciar a árvore para o próximo teste

        testInsertRemoveAlgorithmTree(&AVLTree::insert, &AVLTree::remove, avlTree, randomArray, outputFile, "AVLTree", "Random", size, target);
        testSearchAlgorithmTree(&AVLTree::search, avlTree, target, outputFile, "AVLTreeSearch", "Random", size);

        // Testar FingerTree
        FingerTree fingerTree;
        testInsertRemoveAlgorithmFingerTree(&FingerTree::insert, &FingerTree::remove, fingerTree, sortedArray, outputFile, "FingerTree", "Sorted", size, target);
        testSearchAlgorithmFingerTree(&FingerTree::search, fingerTree, target, outputFile, "FingerTreeSearch", "Sorted", size);

        fingerTree = FingerTree(); // Reiniciar a árvore para o próximo teste
        for (const auto& value : reversedArray) {
            fingerTree.insert(value);
        }
        testInsertRemoveAlgorithmFingerTree(&FingerTree::insert, &FingerTree::remove, fingerTree, reversedArray, outputFile, "FingerTree", "Reversed", size, target);
        testSearchAlgorithmFingerTree(&FingerTree::search, fingerTree, target, outputFile, "FingerTreeSearch", "Reversed", size);

        fingerTree = FingerTree(); // Reiniciar a árvore para o próximo teste
        for (const auto& value : almostSortedArray) {
            fingerTree.insert(value);
        }
        testInsertRemoveAlgorithmFingerTree(&FingerTree::insert, &FingerTree::remove, fingerTree, almostSortedArray, outputFile, "FingerTree", "AlmostSorted", size, target);
        testSearchAlgorithmFingerTree(&FingerTree::search, fingerTree, target, outputFile, "FingerTreeSearch", "AlmostSorted", size);

        fingerTree = FingerTree(); // Reiniciar a árvore para o próximo teste
        for (const auto& value : randomArray) {
            fingerTree.insert(value);
        }
        testInsertRemoveAlgorithmFingerTree(&FingerTree::insert, &FingerTree::remove, fingerTree, randomArray, outputFile, "FingerTree", "Random", size, target);
        testSearchAlgorithmFingerTree(&FingerTree::search, fingerTree, target, outputFile, "FingerTreeSearch", "Random", size);

        // Testar BinarySearchTree
        BinarySearchTree bst;
        testInsertRemoveAlgorithmTree(&BinarySearchTree::insert, &BinarySearchTree::remove, bst, sortedArray, outputFile, "BinarySearchTree", "Sorted", size, target);
        testSearchAlgorithmTree(&BinarySearchTree::search, bst, target, outputFile, "BinarySearchTreeSearch", "Sorted", size);
        bst = BinarySearchTree(); // Reiniciar a árvore para o próximo teste

        testInsertRemoveAlgorithmTree(&BinarySearchTree::insert, &BinarySearchTree::remove, bst, reversedArray, outputFile, "BinarySearchTree", "Reversed", size, target);
        testSearchAlgorithmTree(&BinarySearchTree::search, bst, target, outputFile, "BinarySearchTreeSearch", "Reversed", size);
        bst = BinarySearchTree(); // Reiniciar a árvore para o próximo teste

        testInsertRemoveAlgorithmTree(&BinarySearchTree::insert, &BinarySearchTree::remove, bst, almostSortedArray, outputFile, "BinarySearchTree", "AlmostSorted", size, target);
        testSearchAlgorithmTree(&BinarySearchTree::search, bst, target, outputFile, "BinarySearchTreeSearch", "AlmostSorted", size);
        bst = BinarySearchTree(); // Reiniciar a árvore para o próximo teste

        testInsertRemoveAlgorithmTree(&BinarySearchTree::insert, &BinarySearchTree::remove, bst, randomArray, outputFile, "BinarySearchTree", "Random", size, target);
        testSearchAlgorithmTree(&BinarySearchTree::search, bst, target, outputFile, "BinarySearchTreeSearch", "Random", size);

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
