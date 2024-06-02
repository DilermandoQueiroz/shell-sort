#include "QuickSort.h"
#include <chrono>
#include <stack>

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

// Versão iterativa do Quick Sort
void quickSortIterative(std::vector<int>& arr, int low, int high, Metrics& metrics) {
    // Cria uma pilha auxiliar para armazenar os índices de sub-arrays
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(low, high));

    while (!stack.empty()) {
        low = stack.top().first;
        high = stack.top().second;
        stack.pop();

        // Particiona o array
        int pi = partition(arr, low, high, metrics);

        // Se houver elementos à esquerda do pivô, adiciona ao stack
        if (pi - 1 > low) {
            stack.push(std::make_pair(low, pi - 1));
        }

        // Se houver elementos à direita do pivô, adiciona ao stack
        if (pi + 1 < high) {
            stack.push(std::make_pair(pi + 1, high));
        }
    }
}

Metrics quickSort(std::vector<int>& arr) {
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    quickSortIterative(arr, 0, arr.size() - 1, metrics);

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}
