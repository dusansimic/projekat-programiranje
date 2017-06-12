#include <stdio.h>
#include <stdlib.h>

int main() {
  int provera = 0;
  while (provera != 'q') {
    printf("\nDa li zelite sledeci racun ili da prekinete pregled? (enter/q) ");
    provera = fgetc(stdin);
    fflush(stdin);
    if (provera == '\n')
      continue;
  }
}