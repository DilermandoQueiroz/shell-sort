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

// Função para testar um algoritmo de busca e inserção/remocão
void testSearchAlgorithm(Metrics (*searchFunction)(const std::vector<int>&, int),
                         Metrics (*insertFunction)(std::vector<int>&, int),
                         Metrics (*removeFunction)(std::vector<int>&, int),
                         std::vector<int>& arr, 
                         std::ofstream& outputFile, 
                         const std::string& algorithmName, 
                         const std::string& arrayType, 
                         int size, 
                         int target) {
    try {
        std::cerr << "Testando " << algorithmName << " no array " << arrayType << " de tamanho " << size << std::endl;
        
        Metrics searchMetrics = searchFunction(arr, target);
        Metrics insertMetrics = insertFunction(arr, target);
        Metrics removeMetrics = removeFunction(arr, target);
        
        outputFile << algorithmName << "Search," << arrayType << "," << size << "," << searchMetrics.comparisons << "," << searchMetrics.movements << "," << searchMetrics.time_us << std::endl;
        outputFile << algorithmName << "Insert," << arrayType << "," << size << "," << insertMetrics.comparisons << "," << insertMetrics.movements << "," << insertMetrics.time_us << std::endl;
        outputFile << algorithmName << "Remove," << arrayType << "," << size << "," << removeMetrics.comparisons << "," << removeMetrics.movements << "," << removeMetrics.time_us << std::endl;

        std::cerr << algorithmName << " no array " << arrayType << " de tamanho " << size << " completado" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao testar " << algorithmName << " no array " << arrayType << " de tamanho " << size << ": " << e.what() << std::endl;
    }
}

int main() {
    std::ofstream outputFile("search_results.csv");
    outputFile << "Algorithm,ArrayType,Size,Comparisons,Movements,Time(us)" << std::endl;

    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};
    int target = -1; // Elemento que será buscado/removido

    for (int size : sizes) {
        std::cerr << "Processando arrays de tamanho " << size << std::endl;

        // Gerar arrays
        std::vector<int> sortedArray = generateSortedArray(size);
        std::vector<int> reversedArray = generateReversedArray(size);
        std::vector<int> almostSortedArray = generateAlmostSortedArray(size);
        std::vector<int> randomArray = generateRandomArray(size);

        // Testar LinearSearch
        testSearchAlgorithm(linearSearch, linearInsert, linearRemove, sortedArray, outputFile, "LinearSearch", "Sorted", size, target);
        testSearchAlgorithm(linearSearch, linearInsert, linearRemove, reversedArray, outputFile, "LinearSearch", "Reversed", size, target);
        testSearchAlgorithm(linearSearch, linearInsert, linearRemove, almostSortedArray, outputFile, "LinearSearch", "AlmostSorted", size, target);
        testSearchAlgorithm(linearSearch, linearInsert, linearRemove, randomArray, outputFile, "LinearSearch", "Random", size, target);

        // // Testar BinarySearch
        // testSearchAlgorithm(binarySearch, binaryInsert, binaryRemove, sortedArray, outputFile, "BinarySearch", "Sorted", size, target);
        // testSearchAlgorithm(binarySearch, binaryInsert, binaryRemove, reversedArray, outputFile, "BinarySearch", "Reversed", size, target);
        // testSearchAlgorithm(binarySearch, binaryInsert, binaryRemove, almostSortedArray, outputFile, "BinarySearch", "AlmostSorted", size, target);
        // testSearchAlgorithm(binarySearch, binaryInsert, binaryRemove, randomArray, outputFile, "BinarySearch", "Random", size, target);

        // // Testar BinarySearchTree
        // BinarySearchTree bst;
        // Metrics bstInsertMetrics = bst.insert(target);
        // Metrics bstSearchMetrics = bst.search(target);
        // Metrics bstRemoveMetrics = bst.remove(target);
        // outputFile << "BinarySearchTreeInsert,Random," << size << "," << bstInsertMetrics.comparisons << "," << bstInsertMetrics.movements << "," << bstInsertMetrics.time_us << std::endl;
        // outputFile << "BinarySearchTreeSearch,Random," << size << "," << bstSearchMetrics.comparisons << "," << bstSearchMetrics.movements << "," << bstSearchMetrics.time_us << std::endl;
        // outputFile << "BinarySearchTreeRemove,Random," << size << "," << bstRemoveMetrics.comparisons << "," << bstRemoveMetrics.movements << "," << bstRemoveMetrics.time_us << std::endl;

        // // Testar AVLTree
        // AVLTree avl;
        // Metrics avlInsertMetrics = avl.insert(target);
        // Metrics avlSearchMetrics = avl.search(target);
        // Metrics avlRemoveMetrics = avl.remove(target);
        // outputFile << "AVLTreeInsert,Random," << size << "," << avlInsertMetrics.comparisons << "," << avlInsertMetrics.movements << "," << avlInsertMetrics.time_us << std::endl;
        // outputFile << "AVLTreeSearch,Random," << size << "," << avlSearchMetrics.comparisons << "," << avlSearchMetrics.movements << "," << avlSearchMetrics.time_us << std::endl;
        // outputFile << "AVLTreeRemove,Random," << size << "," << avlRemoveMetrics.comparisons << "," << avlRemoveMetrics.movements << "," << avlRemoveMetrics.time_us << std::endl;

        // // Testar RedBlackTree
        // RedBlackTree rbt;
        // Metrics rbtInsertMetrics = rbt.insert(target);
        // Metrics rbtSearchMetrics = rbt.search(target);
        // Metrics rbtRemoveMetrics = rbt.remove(target);
        // outputFile << "RedBlackTreeInsert,Random," << size << "," << rbtInsertMetrics.comparisons << "," << rbtInsertMetrics.movements << "," << rbtInsertMetrics.time_us << std::endl;
        // outputFile << "RedBlackTreeSearch,Random," << size << "," << rbtSearchMetrics.comparisons << "," << rbtSearchMetrics.movements << "," << rbtSearchMetrics.time_us << std::endl;
        // outputFile << "RedBlackTreeRemove,Random," << size << "," << rbtRemoveMetrics.comparisons << "," << rbtRemoveMetrics.movements << "," << rbtRemoveMetrics.time_us << std::endl;

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
