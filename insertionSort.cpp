#include "InsertionSort.h"
#include <chrono>

// O Insertion Sort ordena a lista construindo um array ordenado um elemento de cada vez
// Ele percorre a lista, e para cada elemento, o insere na posição correta da parte ordenada da lista
Metrics insertionSort(std::vector<int>& arr) {
    Metrics metrics = {0, 0, 0.0};
    int n = arr.size();
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    // Percorre cada elemento do array
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move os elementos da parte ordenada para a direita
        // para criar espaço para a chave
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            metrics.movements++; // Incrementa a contagem de movimentos
            j = j - 1;
            metrics.comparisons++; // Incrementa a contagem de comparações
        }
        arr[j + 1] = key;
        metrics.movements++; // Incrementa a contagem de movimentos
        if (j >= 0) {
            metrics.comparisons++; // Incrementa a contagem de comparações para o caso onde a condição falhou
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}
