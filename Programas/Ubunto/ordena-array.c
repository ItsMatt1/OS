#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Algoritmo do BubbleSort

void BubbleSort(int vetor[], int n)
{
    int k, j, aux;

    for (k = 1; k < n; k++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

// Algoritmo do QuickSort

void QuickSort(int values[], int began, int end)
{
    int i, j, pivo, aux;
    i = began;
    j = end - 1;
    pivo = values[(began + end) / 2];
    while (i <= j)
    {
        while (values[i] < pivo && i < end)
        {
            i++;
        }
        while (values[j] > pivo && j > began)
        {
            j--;
        }
        if (i <= j)
        {
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;
            i++;
            j--;
        }
    }
    if (j > began)
        QuickSort(values, began, j + 1);
    if (i < end)
        QuickSort(values, i, end);
}

int main()
{
    // Criação do array com 10 números desordenados

    int array[10] = {5, 1, 20, 7, 3, 8, 32, 2, 9, 24};

    // Criação de um processo filho

    // Se o filho for criado corretamente
    if (fork() == 0)
    {
        // Chamando o quicksort se o processo for filho
        QuickSort(array, 0, 10);

        // Imprimir o Quicksort ordenando o vetor
        for (int i = 0; i < 10; i++)
        {
            printf("quicksort: %d\n", array[i]);
        }
    }

    //Se o processo for o pai
    else
    {
        // Chamando o bubblesort se o processo for pai
        BubbleSort(array, 10);

        // Imprimir o bubblesort ordenando o vetor
        for (int i = 0; i < 10; i++)
        {
            printf("bubble sort: %d\n", array[i]);
        }
    }
}