#include <stdio.h>
#include <stdlib.h>
#include "modulo.h"

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
