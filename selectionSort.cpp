#include "SelectionSort.h"
#include <chrono>

// O Selection Sort ordena a lista encontrando repetidamente o menor elemento da parte não ordenada
// e colocando-o na posição correta na parte ordenada
Metrics selectionSort(std::vector<int>& arr) {
    Metrics metrics = {0, 0, 0.0};
    int n = arr.size();
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo
    // Percorre cada posição do array
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        // Encontra o menor elemento na parte não ordenada
        for (int j = i + 1; j < n; ++j) {
            metrics.comparisons++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Troca o menor elemento encontrado com o primeiro elemento da parte não ordenada
        if (minIdx != i) {
            metrics.comparisons++;
            std::swap(arr[i], arr[minIdx]);
            metrics.movements++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}
