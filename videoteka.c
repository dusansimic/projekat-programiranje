
int dodavanjeFilma() {
  Film_t filmovi = malloc(sizeof(Film_t) * 0);
  FILE *f = fopen(videotekaFajl, "rb");
  if (f != NULL) {
    while( feof(f) ) {

    }
  }
}

int stanje() {
  int o = 0;
  while (o > 1 || o < 3) {
    printf("1. Po imenu\n");
    printf("2. Po zanru\n");
    printf("3. Po popularnosti\n");
    printf("> ");
    scanf("%i", &o);
  }
  if (o == 1) {
    pretraziPoImenu();
  } else if (o == 2) {
    int zanr = ispisZanrova();
    ispisPoZanru(zanr);
  } else if (o == 3) {
    ispisPoPopularnosti();
  }
}

int ispisZanrova() {
  int o = 0;
  FILE *f = fopen(zanrFajl, "rb");
  Zanr_t *zanrovi = malloc(sizeof(Zanr_t) * 0);
  int brZanrova = 0;
  if (f != NULL) {
    while ( feof(f) ) {
      brZanrova++;
      realloc(zanrovi, sizeof(Zanr_t) * brZanrova);
      fread(zanrovi[brZanrova-1], sizeof(Zanr_t), 1, f);
    }
  }
  fclose(f);
  while (o > 1 || o < brZanrova) {
    int i;
    for (i = 0; i < brZanrova; i++) {
      printf("%i. %s\n", (zanrovi[i]->id) + 1, zanrovi[i]->ime);
    }
    printf("> ");
    scanf("%i", &o);
  }
  return o;
}

int ispisPoZanru(int zanr) {
  zanr--;
  FILE *f = fopen(videotekaFajl, "rb");
  Film_t *filmovi = malloc(sizeof(Film_t) * 0);
  int brFilmova = 0;
  if ( f != NULL ) {
    while ( feof(f) ) {
      brFilmova++;
      realloc(filmovi, sizeof(Film_t) * brFilmova);
      fread(filmovi[brFilmova-1], sizeof(Film_t), 1, f);
    }
  }
  fclose(f);
  int i = 0;
  for (i = 0; i < brFilmova; i++) {
    if (filmovi[i]->idZanr == zanr)
    printf("%i. %s %f %i ", filmovi[i]->id, filmovi[i]->ime, filmovi[i]->cena, filmovi[i]->brIzdavan);
    if (filmovi[i]->stanje == 0) {
      printf("NA STANJU");
    } else {
      printf("NIJE NA STANJU");
    }
  }
  return 0;
}