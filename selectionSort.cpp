#include "SelectionSort.h"

// O Selection Sort ordena a lista encontrando repetidamente o menor elemento da parte não ordenada
// e colocando-o na posição correta na parte ordenada
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    // Percorre cada posição do array
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        // Encontra o menor elemento na parte não ordenada
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Troca o menor elemento encontrado com o primeiro elemento da parte não ordenada
        std::swap(arr[i], arr[minIdx]);
    }
}
