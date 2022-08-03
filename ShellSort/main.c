#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#include "modulo.h"

int main(void){
  int i, vet[MAX];

  printf("A seguir informe os valores da sequencia:\n");
  for (i = 0; i < MAX; i++){
    printf("Informe um valor: ");
    scanf("%d", &vet[i]);
  }
  shell_sort(vet, MAX);

  printf("Valores ordenados\n");
  for (i = 0; i < MAX; i++){
    printf("%d\n", vet[i]);
  }
  getchar();
  return 0;
}

//gcc main.c modulo.c m.h -o main 
//./main