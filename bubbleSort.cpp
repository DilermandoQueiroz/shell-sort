#include "BubbleSort.h"

// O Bubble Sort ordena a lista repetidamente trocando os elementos adjacentes
// se eles estiverem na ordem errada. Esse processo é repetido até que a lista esteja ordenada
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    // Percorre cada elemento do array
    for (int i = 0; i < n - 1; ++i) {
        // Percorre a parte não ordenada do array
        for (int j = 0; j < n - i - 1; ++j) {
            // Troca os elementos adjacentes se estiverem na ordem errada
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
