#include "MergeSort.h"
#include <chrono>

// Função auxiliar para mesclar duas metades
void merge(std::vector<int>& arr, int left, int mid, int right, Metrics& metrics) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Cria arrays temporários
    std::vector<int> L(n1), R(n2);

    // Copia os dados para os arrays temporários
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    // Mescla os arrays temporários de volta ao array original
    while (i < n1 && j < n2) {
        metrics.comparisons++; // Incrementa a contagem de comparações
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        metrics.movements++; // Incrementa a contagem de movimentos
        ++k;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        metrics.movements++; // Incrementa a contagem de movimentos
        ++i;
        ++k;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        metrics.movements++; // Incrementa a contagem de movimentos
        ++j;
        ++k;
    }
}

// O Merge Sort divide o array em duas metades, ordena cada metade recursivamente
// e depois mescla as duas metades ordenadas
void mergeSortHelper(std::vector<int>& arr, int left, int right, Metrics& metrics) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid, metrics);
    mergeSortHelper(arr, mid + 1, right, metrics);
    merge(arr, left, mid, right, metrics);
}

Metrics mergeSort(std::vector<int>& arr) {
    Metrics metrics = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    mergeSortHelper(arr, 0, arr.size() - 1, metrics);

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}
