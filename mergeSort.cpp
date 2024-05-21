#include "MergeSort.h"

// Função auxiliar para mesclar duas metades
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Cria arrays temporários
    std::vector<int> L(n1), R(n2);

    // Copia os dados para os arrays temporários
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[mid + 1 + i];

    // Mescla os arrays temporários de volta ao array original
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// O Merge Sort divide o array em duas metades, ordena cada metade recursivamente
// e depois mescla as duas metades ordenadas
void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(std::vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}
