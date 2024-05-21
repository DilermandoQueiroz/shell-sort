#include "QuickSort.h"

// Função auxiliar para particionar o array
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Pivô
    int i = low - 1; // Índice do menor elemento
    for (int j = low; j < high; ++j) {
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// O Quick Sort escolhe um pivô e particiona o array em dois sub-arrays,
// onde os elementos à esquerda do pivô são menores e à direita são maiores
// Em seguida, ordena recursivamente os sub-arrays
void quickSortHelper(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Índice de particionamento
        quickSortHelper(arr, low, pi - 1);  // Ordena a parte esquerda do pivô
        quickSortHelper(arr, pi + 1, high); // Ordena a parte direita do pivô
    }
}

void quickSort(std::vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}
