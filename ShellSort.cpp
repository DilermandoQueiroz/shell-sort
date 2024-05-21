#include "ShellSort.h"

// O Shell Sort é uma generalização do Insertion Sort que permite a troca de elementos distantes.
// A ideia principal é inicializar o intervalo entre os elementos a serem comparados com um valor grande (gap)
// e depois reduzir gradualmente esse valor até 1. Isso ajuda a reduzir drasticamente o número total de movimentações necessárias.

// O algoritmo Shell Sort funciona em várias fases:
// 1. Escolha uma sequência de gaps.
// 2. Para cada gap, faça uma ordenação por inserção nos elementos que estão a essa distância.
// 3. Reduza o gap até que ele seja 1, momento em que o algoritmo se comporta como um Insertion Sort.

void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    
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
            }
            // Insere temp na posição correta
            arr[j] = temp;
        }
    }
}
