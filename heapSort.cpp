#include "HeapSort.h"
#include <chrono>

// Função auxiliar para ajustar o heap
void heapify(std::vector<int>& arr, int n, int i, Metrics& metrics) {
    int largest = i; // Inicializa o maior como raiz
    int left = 2 * i + 1; // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    metrics.comparisons++; // Comparação entre filho esquerdo e raiz
    // Se o filho esquerdo é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    metrics.comparisons++; // Comparação entre filho direito e o maior até agora
    // Se o filho direito é maior que o maior até agora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se o maior não é a raiz
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        metrics.movements++; // Incrementa a contagem de movimentos
        // Recursivamente ajusta o heap afetado
        heapify(arr, n, largest, metrics);
    }
}

// O Heap Sort primeiro constrói um heap max e depois troca o elemento raiz (o maior)
// com o último elemento do heap. Este processo é repetido para o restante do heap.
Metrics heapSort(std::vector<int>& arr) {
    Metrics metrics = {0, 0, 0.0};
    int n = arr.size();
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    // Constrói o heap max
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, metrics);

    // Extrai os elementos do heap um por um
    for (int i = n - 1; i >= 0; i--) {
        // Move a raiz atual para o fim
        std::swap(arr[0], arr[i]);
        metrics.movements++; // Incrementa a contagem de movimentos
        // Chama heapify no heap reduzido
        heapify(arr, i, 0, metrics);
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}
