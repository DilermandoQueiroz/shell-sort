#include "LinearSearch.h"
#include <chrono>

Metrics linearSearch(const std::vector<int>& arr, int target) {
    Metrics metrics = {0, 0, 0.0}; // Inicializa os valores de métricas
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    for (size_t i = 0; i < arr.size(); ++i) {
        metrics.comparisons++; // Incrementa a contagem de comparações
        if (arr[i] == target) {
            metrics.movements = 1;
            break; // Sai do loop quando o elemento é encontrado
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}

Metrics linearInsert(std::vector<int>& arr, int target) {
    Metrics metrics = {0, 0, 0.0}; // Inicializa os valores de métricas
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    arr.push_back(target);
    metrics.movements = 1; // Um movimento para inserir o elemento

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}

Metrics linearRemove(std::vector<int>& arr, int target) {
    Metrics metrics = {0, 0, 0.0}; // Inicializa os valores de métricas
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    for (auto it = arr.begin(); it != arr.end(); ++it) {
        metrics.comparisons++; // Incrementa a contagem de comparações
        if (*it == target) {
            arr.erase(it);
            metrics.movements = 1; // Um movimento para remover o elemento
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}