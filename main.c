#include <stdio.h>
#include <stdlib.h>
#include "videoteka.h"

int main() {
  resetujBazu();
  dodavanjeZanra();
  dodavanjeFilma();
  dodavanjeFilma();
  dodavanjeRacuna(5, 0);
  dodavanjeRacuna(5, 1);
  ispisRacuna();
  return 0;
}