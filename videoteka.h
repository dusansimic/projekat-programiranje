#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char *videotekaFajl = "videoteka.dat";
const char *zanroviFajl = "zanrovi.dat";
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
  char vreme[100];
  int idIzdavaca; // id radnika
} Racun_t;

char vreme[100];

/*Vreme_t TrnVreme()
{
  time_t t;
  time(&t);
  struct tm *timeinfo;
  timeinfo = localtime(&t);

  Vreme_t vr;
  
  strftime(vr.vreme, 20, "%X", timeinfo);
  strftime(vr.datum, 20, "%x", timeinfo);

  return vr;
}*/

int trenutnoVreme() {
  time_t t;
  time(&t);
  struct tm *timeinfo;
  timeinfo = localtime(&t);
  
  return 0;
}

int iscitajFilmove(Film_t *filmovi) {
  FILE *f = fopen(videotekaFajl, "rb");
  int brFilmova = 1;
  filmovi = realloc(filmovi, sizeof(Film_t) * brFilmova);
  if (f != NULL) {
    while (fread(&filmovi[brFilmova-1], sizeof(Film_t), 1, f)) {
      brFilmova++;
      filmovi = realloc(filmovi, sizeof(Film_t) * brFilmova);
    }
    fclose(f);
  }
  brFilmova--;
  filmovi = realloc(filmovi, sizeof(Film_t) * brFilmova);
  return brFilmova;
}

int iscitajZanrove(Zanr_t *zanrovi) {
  FILE *f = fopen(zanroviFajl, "rb");
  int brZanrova = 1;
  zanrovi = realloc(zanrovi, sizeof(Zanr_t) * brZanrova);
  if (f != NULL) {
    while (fread(&zanrovi[brZanrova-1], sizeof(Zanr_t), 1, f)) {
      brZanrova++;
      zanrovi = realloc(zanrovi, sizeof(Zanr_t) * brZanrova);
    }
    fclose(f);
  }
  brZanrova--;
  zanrovi = realloc(zanrovi, sizeof(Zanr_t) * brZanrova);
  return brZanrova;
}

int iscitajRacune(Racun_t *racuni) {
  FILE *f = fopen(racuniFajl, "rb");
  int brRacuna = 1;
  racuni = realloc(racuni, sizeof(Racun_t) * brRacuna);
  if (f != NULL) {
    while (fread(&racuni[brRacuna-1], sizeof(Racun_t), 1, f)) {
      brRacuna++;
      racuni = realloc(racuni, sizeof(Racun_t) * brRacuna);
    }
    fclose(f);
    printf("Uspesno iscitano!\n");
  }
  brRacuna--;
  racuni = realloc(racuni, sizeof(Racun_t) * brRacuna);
  return brRacuna;
}

int upisiFilmove(Film_t *filmovi, int brFilmova) {
  FILE *f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    int i;
    for (i = 0; i < brFilmova; i++) {
      fwrite(&filmovi[i], sizeof(Film_t), 1, f);
    }
    fclose(f);
  }
  return 0;
}

int upisiZanrove(Zanr_t *zanrovi, int brZanrova) {
  FILE *f = fopen(zanroviFajl, "wb");
  if (f != NULL) {
    int i;
    for (i = 0; i < brZanrova; i++) {
      int upisano = fwrite(&zanrovi[i], sizeof(Zanr_t), 1, f);
      printf("Upisano je %i zanrova.\n", upisano);
    }
    fclose(f);
  } else
    printf("Greska u upisu zanrova u fajl.\n");
  return 0;
}

int upisiRacune(Racun_t *racuni, int brRacuna){
  FILE *f = fopen(racuniFajl, "wb");
  if(f != NULL){
    int i;
    for(i = 0; i < brRacuna; i++){
      fwrite(&racuni[i], sizeof(Racun_t), 1, f);
    }
    fclose(f);
    printf("Uspesno upisano!\n");
  }
  return 0;
}

int odabirFilma(Film_t *filmovi, int brFilmova) {
  int o;
  while (1) {
    system("cls");
    int i;
    for (i = 0; i < brFilmova; i++) {
      printf("%i. %s", filmovi[i].id, filmovi[i].ime);
    }
    printf("> ");
    scanf("%i", &o);
    if ((o > 1 || o <= brFilmova) && filmovi[o].stanje) {
      filmovi[o].stanje = 0;
      filmovi[o].brIzdavan++;
      break;
    }
  }
  return o;
}

int dodavanjeFilma() {
  Film_t *filmovi = malloc(0);
  int brFilmova = iscitajFilmove(filmovi);
  brFilmova++;
  filmovi = realloc(filmovi, sizeof(Film_t) * brFilmova);
  filmovi[brFilmova-1].id = brFilmova - 1;
  printf("Unesite ime filma: ");
  //fgets(filmovi[brFilmova-1].ime, 50, stdin);
  scanf("%s", filmovi[brFilmova-1].ime);
  fflush(stdin);
  printf("Unesite cenu filma: ");
  scanf("%f", &(filmovi[brFilmova-1].cena));
  fflush(stdin);
  filmovi[brFilmova-1].status = 0;

  Zanr_t *zanrovi = malloc(0);
  int brZanrova = iscitajZanrove(zanrovi);
  
  int o = 0;
  while (1) {
    int i;
    for (i = 0; i < brZanrova; i++) {
      printf("%i. %s\n", zanrovi[i].id, zanrovi[i].ime);
    }
    printf("> ");
    scanf("%i", &o);
    fflush(stdin);
    if (o >= 0 && o < brZanrova)
      break;
  }
  
  filmovi[brFilmova-1].idZanr = o;
  upisiFilmove(filmovi, brFilmova);
  free(filmovi);
  free(zanrovi);
  
  return 0;
}

int brisanjeFilma() {
  Film_t *filmovi;
  int brFilmova;
  FILE *f = fopen(videotekaFajl, "rb");
  if (f != NULL) {
    fread(&brFilmova, sizeof(int), 1, f);
    filmovi = malloc(sizeof(Film_t) * brFilmova);
    fread(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  int o = odabirFilma(filmovi, brFilmova);
  filmovi[o].status = 1;
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
  Film_t *filmovi;
  int brFilmova;
  FILE *f = fopen(videotekaFajl, "rb");
  if (f != NULL) {
    fread(&brFilmova, sizeof(int), 1, f);
    filmovi = malloc(sizeof(Film_t) * brFilmova);
    fread(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  int o = odabirFilma(filmovi, brFilmova);

  printf("Unesite ime filma (%s): ", filmovi[o].ime);
  fgets(filmovi[o].ime, 50, stdin);
  fflush(stdin);

  filmovi[o].status = 1;
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
  Zanr_t *zanrovi = malloc(0);
  int brZanrova = iscitajZanrove(zanrovi);
  brZanrova++;
  zanrovi = realloc(zanrovi, sizeof(Zanr_t) * brZanrova);
  zanrovi[brZanrova-1].id = brZanrova - 1;
  printf("Uneiste ime zanra: ");
  scanf("%s", zanrovi[brZanrova-1].ime);
  fflush(stdin);
  zanrovi[brZanrova-1].status = 0;
  upisiZanrove(zanrovi, brZanrova);
  free(zanrovi);
  return 0;
}


int azuriranjeZanra(){ // srki
  Zanr_t *zanrovi;
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
    for (i = 0; i < brZanrova; i++) {
      printf("%i. %s", zanrovi[i].id, zanrovi[i].ime);
    }
    printf("> ");
    scanf("%i", &o);
    if (o > 1 || o <= brZanrova)
      break;
  }
  printf("Unesite izmenu imena zanra (%s): ", zanrovi[o].ime);
  scanf("%s", zanrovi[o].ime);
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
  Zanr_t *zanrovi;
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
    for (i = 0; i < brZanrova; i++) {
      printf("%i. %s", zanrovi[i].id, zanrovi[i].ime);
    }
    printf("> ");
    scanf("%i", &o);
    if (o > 1 || o <= brZanrova)
      break;
  }
  zanrovi[o].status = 1;
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
    for (i = 0; i < brFilmova; i++) {
      printf("%i. %s", filmovi[i].id, filmovi[i].ime);
    }
    printf("> ");
    scanf("%i", &o);
    if ((o > 1 || o <= brFilmova) && filmovi[o].stanje) {
      filmovi[o].stanje = 0;
      filmovi[o].brIzdavan++;
      break;
    }
  }
  dodavanjeRacuna(idIzdavaca, filmovi[o].id);
  f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(&brFilmova, sizeof(int), 1, f);
    fwrite(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  free(filmovi);
  return 0;
}

/*struct tm* trenutnoVreme(){
  time_t mytime;
  mytime = time(NULL);
  struct tm *timeInfo;
  timeInfo = localtime(&mytime);
  timeInfo->tm_year+=1900;
  return timeInfo;
}*/

int dodavanjeRacuna(int idRad, int idFilm) {
  Racun_t *racuni = malloc(0);
  int brRacuna = iscitajRacune(racuni);
  
  brRacuna++;
  racuni = realloc(racuni, sizeof(Racun_t) * brRacuna);
  racuni[brRacuna-1].id = brRacuna - 1;
  racuni[brRacuna-1].idIzdavaca = idRad;
  racuni[brRacuna-1].idFilma = idFilm;
  printf("Pre vremena\n");
  //racuni[brRacuna-1].vreme = TrnVreme();
  trenutnoVreme();
  strcpy(racuni[brRacuna-1].vreme, vreme);
  printf("Posle vremena\n");
  upisiRacune(racuni, brRacuna);
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
    for (i = 0; i < brFilmova; i++) {
      printf("%i. %s", filmovi[i].id, filmovi[i].ime);
    }
    printf("> ");
    scanf("%i", &o);
    if ((o > 1 || o <= brFilmova) && !filmovi[o].stanje) {
      filmovi[o].stanje = 1;
      break;
    }
  }
  f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(&brFilmova, sizeof(int), 1, f);
    fwrite(filmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  free(filmovi);
  return 0;
}

int ispisRacuna() {
  Racun_t *racuni = malloc(0);
  int brRacuna = iscitajRacune(racuni);
  
  int i;
  for (i = 0; i < brRacuna; i++) {
    system("cls");
    printf("ID racuna: %i\n", racuni[i].id);
    printf("ID izdatog filma: %i\n", racuni[i].idFilma);
    Film_t *filmovi = malloc(0);
    int brFilmova = iscitajFilmove(filmovi);
    
    int j;
    for (j = 0; j < brFilmova; j++) {
      if (filmovi[j].id == racuni[i].idFilma) {
        printf("Ime izdatog filma: %s\n", filmovi[j].ime);
      }
    }
    free(filmovi);
    printf("Vreme izdavanja filma: %s", racuni[i].vreme);
    printf("\nDa li zelite sledeci racun ili da prekinete pregled? (enter/q) ");
    int provera = 0;
    while (provera != 'q' && provera != '\n') {
      provera = fgetc(stdin);
      fflush(stdin);
    }
    if (provera == 'q')
      break;
  }
  return 0;
}

int ciscenjePodataka() { // za posle, treba odraditi za sve datoteke
  FILE *f = fopen(videotekaFajl, "rb");
  int brFilmova;
  Film_t *filmovi;
  if (f != NULL) {
    fread(&brFilmova, sizeof(int), 1, f);
    filmovi = malloc(sizeof(Film_t) * brFilmova);
    fread(filmovi, sizeof(Film_t), 1, f);
  }
  fclose(f);
  Film_t *cistiFilmovi = malloc(0);
  int brojac = 0;
  int i;
  for (i = 0; i < brFilmova; i++) {
    if (filmovi[i].status) {
      brojac++;
      realloc(cistiFilmovi, sizeof(Film_t) * brojac);
      cistiFilmovi[brojac-1] = filmovi[i];
    }
  }
  free(filmovi);
  f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(&brFilmova, sizeof(int), 1, f);
    fwrite(cistiFilmovi, sizeof(Film_t), brFilmova, f);
  }
  fclose(f);
  free(cistiFilmovi);

  f = fopen(zanroviFajl, "rb");
  int brZanrova;
  Zanr_t *zanrovi;
  if (f != NULL) {
    fread(&brZanrova, sizeof(int), 1, f);
    zanrovi = malloc(sizeof(Zanr_t) * brZanrova);
    fread(zanrovi, sizeof(Zanr_t), 1, f);
  }
  fclose(f);
  Zanr_t *cistiZanrovi = malloc(0);
  brojac = 0;
  for (i = 0; i < brZanrova; i++) {
    if (zanrovi[i].status) {
      brojac++;
      realloc(cistiZanrovi, sizeof(Zanr_t) * brojac);
      cistiZanrovi[brojac-1] = zanrovi[i];
    }
  }
  free(zanrovi);
  f = fopen(zanroviFajl, "wb");
  if (f != NULL) {
    fwrite(&brZanrova, sizeof(int), 1, f);
    fwrite(cistiZanrovi, sizeof(Zanr_t), brZanrova, f);
  }
  fclose(f);
  free(cistiZanrovi);
  return 0;
}

// srediti da se koriste nove funkcije za citanje i pisanje
int resetujBazu() {
  int br = 0;
  Film_t *filmovi = malloc(0);
  FILE *f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(filmovi, sizeof(Film_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n");
  free(filmovi);

  Zanr_t *zanrovi = malloc(0);
  f = fopen(zanroviFajl, "wb");
  if (f != NULL) {
    fwrite(zanrovi, sizeof(Zanr_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n");
  free(zanrovi);

  Racun_t *racuni = malloc(0);
  f = fopen(racuniFajl, "wb");
  if (f != NULL) {
    fwrite(racuni, sizeof(Racun_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n");
  free(racuni);

  printf("Baza podataka je uspesno resetovana!\n");
  return 0;
}