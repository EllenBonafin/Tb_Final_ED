// Faça um programa em C que implemente o método de ordenação SHELL SORT
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void shell_sort(int *a, int size){
  int i, j, value;
  int x = 1;

  do{
    x = 3 * x + 1;
  } while (x < size);

  do{
    x /= 3;
    for (i = x; i < size; i++){
      value = a[i];
      j = i - x;

      while (j >= 0 && value < a[j]){
        a[j + x] = a[j];
        j -= x;
      }
      a[j + x] = value;
    }
  } while (x > 1);
}

int main(int argc, char **argv){
  int i, vet[MAX];

  printf("A seguir informe os valores da sequencia:\n");
  for (i = 0; i < MAX; i++){
    printf("Informe um valor: ");
    scanf("%d", &vet[i]);
  }

  shell_sort(vet, MAX);

  printf("Valores ordenados\n");
  for (i = 0; i < MAX; i++){
    printf("%dn\n", vet[i]);
  }
  system("pause");
  return 0;
}
