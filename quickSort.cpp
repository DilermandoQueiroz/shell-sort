#include "QuickSort.h"
#include <chrono>

// Função auxiliar para particionar o array
int partition(std::vector<int>& arr, int low, int high, Metrics& metrics) {
    int pivot = arr[high]; // Pivô
    int i = low - 1; // Índice do menor elemento
    for (int j = low; j < high; ++j) {
        metrics.comparisons++; // Incrementa a contagem de comparações
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
            metrics.movements++; // Incrementa a contagem de movimentos
        }
    }
    std::swap(arr[i + 1], arr[high]);
    metrics.movements++; // Incrementa a contagem de movimentos
    return i + 1;
}

// O Quick Sort escolhe um pivô e particiona o array em dois sub-arrays,
// onde os elementos à esquerda do pivô são menores e à direita são maiores
// Em seguida, ordena recursivamente os sub-arrays
void quickSortHelper(std::vector<int>& arr, int low, int high, Metrics& metrics) {
    if (low < high) {
        int pi = partition(arr, low, high, metrics); // Índice de particionamento
        quickSortHelper(arr, low, pi - 1, metrics);  // Ordena a parte esquerda do pivô
        quickSortHelper(arr, pi + 1, high, metrics); // Ordena a parte direita do pivô
    }
}

Metrics quickSort(std::vector<int>& arr) {
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    quickSortHelper(arr, 0, arr.size() - 1, metrics);

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}
