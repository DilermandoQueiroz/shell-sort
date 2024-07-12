#include "BinarySearch.h"
#include <chrono>
#include <algorithm> // Para std::lower_bound e std::upper_bound

Metrics binarySearch(const std::vector<int>& arr, int target) {
    Metrics metrics = {0, 0, 0.0}; // Inicializa os valores de métricas
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        metrics.comparisons++; // Incrementa a contagem de comparações

        if (arr[mid] == target) {
            break; // Elemento encontrado
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}

Metrics binaryInsert(std::vector<int>& arr, int target) {
    Metrics metrics = {0, 0, 0.0}; // Inicializa os valores de métricas
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    auto it = std::lower_bound(arr.begin(), arr.end(), target);
    metrics.comparisons = std::distance(arr.begin(), it); // Número de comparações até encontrar a posição correta
    arr.insert(it, target);
    metrics.movements = std::distance(it, arr.end()); // Movimentos necessários para inserir

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}

Metrics binaryRemove(std::vector<int>& arr, int target) {
    Metrics metrics = {0, 0, 0.0}; // Inicializa os valores de métricas
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    auto it = std::lower_bound(arr.begin(), arr.end(), target);
    metrics.comparisons = std::distance(arr.begin(), it); // Número de comparações até encontrar a posição correta

    if (it != arr.end() && *it == target) {
        arr.erase(it);
        metrics.movements = std::distance(it, arr.end()); // Movimentos necessários para remover
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}