#include "BubbleSort.h"
#include <chrono>

// O Bubble Sort ordena a lista repetidamente trocando os elementos adjacentes
// se eles estiverem na ordem errada. Esse processo é repetido até que a lista esteja ordenada.
Metrics bubbleSort(std::vector<int>& arr) {
    Metrics metrics = {0, 0, 0.0};
    int n = arr.size();
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    // Percorre cada elemento do array
    for (int i = 0; i < n - 1; ++i) {
        // Percorre a parte não ordenada do array
        for (int j = 0; j < n - i - 1; ++j) {
            metrics.comparisons++; // Incrementa a contagem de comparações
            // Troca os elementos adjacentes se estiverem na ordem errada
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                metrics.movements++; // Incrementa a contagem de movimentos
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}
