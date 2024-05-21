#include "HeapSort.h"

// Função auxiliar para ajustar o heap
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i; // Inicializa o maior como raiz
    int left = 2 * i + 1; // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    // Se o filho esquerdo é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Se o filho direito é maior que o maior até agora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se o maior não é a raiz
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        // Recursivamente ajusta o heap afetado
        heapify(arr, n, largest);
    }
}

// O Heap Sort primeiro constrói um heap max e depois troca o elemento raiz (o maior)
// com o último elemento do heap. Este processo é repetido para o restante do heap
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    // Constrói o heap max
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrai os elementos do heap um por um
    for (int i = n - 1; i >= 0; i--) {
        // Move a raiz atual para o fim
        std::swap(arr[0], arr[i]);
        // Chama heapify no heap reduzido
        heapify(arr, i, 0);
    }
}
