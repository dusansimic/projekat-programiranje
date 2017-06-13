#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *videotekaFajl = "videoteka.dat";
const char *zanrFajl = "zanrovi.dat";
const char *racuniFajl = "racuni.dat";

typedef struct Film {
  int id;
  char ime[50];
  float cena;
  int brIzdavan;
  int stanje;
  int status;
  int idZanr;
} Film_t;

typedef struct Zanr {
  int id;
  char ime[10];
  int status;
} Zanr_t;

typedef struct Racun {
  int id;
  int idFilma;
  struct tm *vremeIzdavanja;
  int idIzdavaca; // id radnika
} Racun_t;


int odabirFilma(Film_t *filmovi, int brFilmova) {
  while (1) {
    system("cls");
    int i;
    for (i = 0; i < brZanrova, i++) {
      printf("%i. %s", filmovi[i]->id, filmovi[i]->ime);
    }
    printf("> ");
    scanf("%i", &o);
    if ((o > 1 || o <= brFilmova) && filmovi[o]->stanje) {
      filmovi[o]->stanje = 0;
      filmovi[o]->brIzdavan++;
      break;
    }
  }
  return o;
}

int dodavanjeFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  int brFilmova;
  Film_t *filmovi;
  if (f != NULL) {
    fread(&brFilmova, sizeof(int), 1, f);
    filmovi = malloc(sizeof(Film_t) * brFilmova);
    fread(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  brFilmova++;
  realloc(filmovi, sizeof(Film_t) * brFilmova);
  printf("Unesite id filma: ");
  scanf("%i", &(filmovi[brFilmova-1]->id));
  printf("Unesite ime filma: ");
  fgets(filmovi[brFilmova-1]->ime, 50, stdin);
  printf("Unesite cenu filma: ");
  scanf("%f", &(filmovi[brFilmova-1]->brIzdavan));
  filmovi[brFilmova-1]->status = 0;

  Zanr_t *zanrovi;
  int brZanrova;
  f = fopen(zanrFajl, "rb");
  if (f != NULL) {
    fread(&brZanrova, sizeof(int), 1, f);
    zanrovi = malloc(sizeof(Zanr_t) * brZanrova);
    fread(zanrovi, sizeof(Zanr_t), brZanrova, f);
  }
  fclose(f);
  int o = 0;
  while (1) {
    int i;
    for (i = 0; i < brZanrova, i++) {
      printf("%i. %s", zanrovi[i]->id, zanrovi[i]->ime);
    }
    printf("> ");
    scanf("%i", &o);
    if (o > 1 || o <= brZanrova)
      break;
  }
  free(zanrovi);
  filmovi[brFilmova-1]->idZanr = o;
  f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(brFilmova, sizeof(int), 1, f);
    fwrite(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  free(filmovi);
  return 0;
}



int brisanjeFilma() {
  Film_t filmovi;
  int brFilmova;
  FILE *f = fopen(videotekaFajl, "rb");
  if (f != NULL) {
    fread(&brFilmova, sizeof(int), 1, f);
    filmovi = malloc(sizeof(Film_t) * brFilmova);
    fread(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  int o = odabirFilma(filmovi, brFilmova);
  filmovi[o]->status = 1;
  f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(&brFilmova, sizeof(int), 1, f);
    fwrite(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  free(filmovi);
  return 0;
}




int azuriranjeFilma() {
  Film_t filmovi;
  int brFilmova;
  FILE *f = fopen(videotekaFajl, "rb");
  if (f != NULL) {
    fread(&brFilmova, sizeof(int), 1, f);
    filmovi = malloc(sizeof(Film_t) * brFilmova);
    fread(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  int o = odabirFilma(filmovi, brFilmova);

  printf("Unesite ime filma (%s): ", filmovi[o]->ime);
  fgets(filmovi[o]->ime, 50, stdin);
  fflush(stdin);

  filmovi[o]->status = 1;
  f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(&brFilmova, sizeof(int), 1, f);
    fwrite(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  free(filmovi);
  return 0;
}

int dodavanjeZanra() { // srki
  Zanr_t zanrovi;
  int brZanrova;
  FILE *f = fopen(zanroviFajl, "rb");
  if (f != NULL) {
    fread(&brZanrova, sizeof(int), 1, f);
    zanrovi = malloc(sizeof(Zanr_t) * brZanrova);
    fread(zanrovi, sizeof(Zanr_t), brZanrova, f);
  }
  fclose(f);
  brZanrova++;
  realloc(zanrovi, sizeof(Zanr_t) * brZanrova);
  zanrovi[brZanrova-1]->id = brZanrova - 1;
  printf("Uneiste ime zanra: ");
  scanf("%s", zanrovi[brZanrova-1]->ime);
  zanrovi[brZanrova-1]->status = 0;
  f = fopen(zanroviFajl, "wb");
  if (f != NULL) {
    fwrite(&brZanrova, sizeof(int), 1, f);
    fwrite(zanrovi, sizeof(Zanr_t), brZanrova, f);
  }
  fclose(f);
  free(zanrovi);
  return 0;
}

int azuriranjeZanra(){ // srki
  Zanr_t zanrovi;
  int brZanrova;
  FILE *f = fopen(zanroviFajl, "rb");
  if (f != NULL) {
    fread(&brZanrova, sizeof(int), 1, f);
    zanrovi = malloc(sizeof(Zanr_t) * brZanrova);
    fread(zanrovi, sizeof(Zanr_t), brZanrova, f);
  }
  fclose(f);
  int o;
  while (1) {
    int i;
    for (i = 0; i < brZanrova, i++) {
      printf("%i. %s", zanrovi[i]->id, zanrovi[i]->ime);
    }
    printf("> ");
    scanf("%i", &o);
    if (o > 1 || o <= brZanrova)
      break;
  }
  printf("Unesite izmenu imena zanra (%s): ", zanrovi[o]->ime);
  scanf("%s", zanrovi[o]->ime);
  f = fopen(zanroviFajl, "wb");
  if (f != NULL) {
    fwrite(&brZanrova, sizeof(int), 1, f);
    fwrite(zanrovi, sizeof(Zanr_t), brZanrova, f);
  }
  fclose(f);
  free(zanrovi);
  return 0;
}
int brisanjeZanra() { // srki
  Zanr_t zanrovi;
  int brZanrova;
  FILE *f = fopen(zanroviFajl, "rb");
  if (f != NULL) {
    fread(&brZanrova, sizeof(int), 1, f);
    zanrovi = malloc(sizeof(Zanr_t) * brZanrova);
    fread(zanrovi, sizeof(Zanr_t), brZanrova, f);
  }
  fclose(f);
  int o;
  while (1) {
    int i;
    for (i = 0; i < brZanrova, i++) {
      printf("%i. %s", zanrovi[i]->id, zanrovi[i]->ime);
    }
    printf("> ");
    scanf("%i", &o);
    if (o > 1 || o <= brZanrova)
      break;
  }
  zanrovi[o]->status = 1;
  f = fopen(zanroviFajl, "wb");
  if (f != NULL) {
    fwrite(&brZanrova, sizeof(int), 1, f);
    fwrite(zanrovi, sizeof(Zanr_t), brZanrova, f);
  }
  fclose(f);
  free(zanrovi);
  return 0;
}

// kubini ispisi

int izdavanjeFilma(int idIzdavaca) {
  FILE *f = fopen(videotekaFajl, "rb");
  int brFilmova;
  Film_t *filmovi;
  if (f != NULL) {
    fread(&brFilmova, sizeof(int), 1, f);
    filmovi = malloc(sizeof(Film_t) * brFilmova);
    fread(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  int o;
  while (1) {
    system("cls");
    int i;
    for (i = 0; i < brZanrova, i++) {
      printf("%i. %s", zanrovi[i]->id, zanrovi[i]->ime);
    }
    printf("> ");
    scanf("%i", &o);
    if ((o > 1 || o <= brZanrova) && filmovi[o]->stanje) {
      filmovi[o]->stanje = 0;
      filmovi[o]->brIzdavan++;
      break;
    }
  }
  dodavanjeRacuna(idIzdavaca, filmovi[o]->id);
  f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(brFilmova, sizeof(int), 1, f);
    fwrite(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  free(filmovi);
  return 0;
}

struct tm* trenutnoVreme(){
  time_t mytime;
  mytime = time(NULL);
  printf(ctime(&mytime));
  struct tm *timeInfo;
  timeInfo = localtime(&mytime);
  timeInfo->tm_year+=1900;
  return timeInfo;
};

int dodavanjeRacuna(int idRad, int idFilm) {
  FILE *f = fopen(racuniFajl, "rb");
  int brRacuna;
  Racun_t *racuni;
  if (f != NULL) {
    fread(&brRacuna, sizeof(int), 1, f);
    racuni = malloc(sizeof(Racun_t) * brRacuna);
    fread(racuni, sizeof(Racun_t), brRacuna, f);
  }
  fclose(f);
  brRacuna++;
  realloc(racuni, sizeof(Racun_t) * brRacuna);
  racuni[brRacuna-1]->id = brRacuna - 1;
  racuni[brRacuna-1]->idIzdavaca = idRad;
  racun[brRacuna-1]->idFilma = idFilm;
  racun[brRacuna-1]->vremeIzdavanja = trenutnoVreme();
  f = fopen(racuniFajl, "wb");
  if (f != NULL) {
    fwrite(&brRacuna, sizeof(int), 1, f);
    fwrite(racuni, sizeof(Racuni_t), brRacuna, f);
  }
  fclose(f);
  free(racuni);
  return 0;
}

int vracanjeFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  int brFilmova;
  Film_t *filmovi;
  if (f != NULL) {
    fread(&brFilmova, sizeof(int), 1, f);
    filmovi = malloc(sizeof(Film_t) * brFilmova);
    fread(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  int o;
  while (1) {
    system("cls");
    int i;
    for (i = 0; i < brZanrova, i++) {
      printf("%i. %s", zanrovi[i]->id, zanrovi[i]->ime);
    }
    printf("> ");
    scanf("%i", &o);
    if ((o > 1 || o <= brZanrova) && !filmovi[o]->stanje) {
      filmovi[o]->stanje = 1;
      break;
    }
  }
  f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(brFilmova, sizeof(int), 1, f);
    fwrite(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  free(filmovi);
  return 0;
}

int ispisRacuna() {
  FILE *f = fopen(racuniFajl, "rb");
  int brRacuna;
  Racun_t *racuni;
  if (f != NULL) {
    fread(&brRacuna, sizeof(int), 1, f);
    racuni = malloc(sizeof(Racun_t) * brRacuna);
    fread(racuni, sizeof(Racun_t), brRacuna, f);
  }
  fclose(f);
  int i;
  for (i = 0; i < brRacuna; i++) {
    system("cls");
    printf("ID racuna: %i\n", racuni[i]->id);
    printf("ID izdatog filma: %i\n", racuni[i]->idFilma);
    f = fopen(videotekaFajl, "rb");
    int brFilmova;
    Film_t *filmovi;
    if (f != NULL) {
      fread(&brFilmova, sizeof(int), 1, f);
      filmovi = malloc(sizeof(Film_t) * brFilmova);
      fread(filmovi, sizeof(Film_t), brFilmova, f);
    }
    fclose(f);
    int j;
    for (j = 0; j < brFilmova; j++) {
      if (filmovi[j]->id == racuni[i]->idFilma) {
        printf("Ime izdatog filma: %s\n", filmovi[j]->ime);
      }
    }
    free(filmovi);
    printf("Vreme izdavanja filma: %i:%i", racuni[i]->vremeIzdavanja->tm_hour, racuni[i]->vremeIzdavanja->tm_min);
    printf("\nDa li zelite sledeci racun ili da prekinete pregled? (enter/q) ");
    int provera = 0;
    while (provera != 'q' && provera != '\n') {
      provera = fgetc(stdin);
      fflush(stdin);
    }
    if (provera == 'q')
      break;
  }
}