#include "InsertionSort.h"

// O Insertion Sort ordena a lista construindo um array ordenado um elemento de cada vez
// Ele percorre a lista, e para cada elemento, o insere na posição correta da parte ordenada da lista
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    // Percorre cada elemento do array
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        // Move os elementos da parte ordenada para a direita
        // para criar espaço para a chave
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // Insere a chave na posição correta
        arr[j + 1] = key;
    }
}
