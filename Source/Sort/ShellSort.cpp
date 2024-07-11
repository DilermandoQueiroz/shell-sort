#include "ShellSort.h"
#include <chrono>

// O Shell Sort é uma generalização do Insertion Sort que permite a troca de elementos distantes.
// A ideia principal é inicializar o intervalo entre os elementos a serem comparados com um valor grande (gap)
// e depois reduzir gradualmente esse valor até 1. Isso ajuda a reduzir drasticamente o número total de movimentações necessárias.
Metrics shellSort(std::vector<int>& arr) {
    Metrics metrics = {0, 0, 0.0};
    int n = arr.size();
    auto start = std::chrono::high_resolution_clock::now(); // Inicia a contagem do tempo

    // Inicializa o gap. Aqui estamos usando a sequência de gaps de Shell, onde o gap inicial é n/2
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Para cada gap, fazemos uma ordenação por inserção nos elementos que estão a essa distância
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            // Move os elementos de arr[0..i-gap] que são maiores que temp
            // para a posição à frente de sua posição atual
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                metrics.movements++; // Incrementa a contagem de movimentos
                metrics.comparisons++; // Incrementa a contagem de comparações
            }
            arr[j] = temp;
            metrics.movements++; // Incrementa a contagem de movimentos
            if (j >= gap) {
                metrics.comparisons++; // Incrementa a contagem de comparações
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Finaliza a contagem do tempo
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Calcula o tempo de execução
    return metrics;
}
