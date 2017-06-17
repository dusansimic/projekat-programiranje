#include <stdio.h>
#include <stdlib.h>
#include "videoteka.h"

int main() {
  resetujBazu();
  dodavanjeZanra();
  dodavanjeFilma();
  dodavanjeRacuna(5, 0);
  ispisRacuna();
  return 0;
}