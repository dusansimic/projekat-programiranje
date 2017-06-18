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
  struct tm *vremeIzdavanja;
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

int clearScreen() {
  system("@cls||clear");
  return 0;
}

int odabirFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return -1;
  Film_t film;
  int brFilmova = 0;
  int o;
  while (1) {
    clearScreen();
    int lastId;
    while (fread(&film, sizeof(Film_t), 1, f)) {
      printf("\b%i. %s\n", film.id, film.ime);
      lastId = film.id;
    }
    printf("Unesite id odabranog filma: ");
    scanf("%i", &o);
    if (o >= 0 && o <= lastId)
      break;
  }
  return o;
}

int odabirZanra() {
  FILE *f = fopen(zanroviFajl, "rb");
  if (f == NULL)
    return -1;
  Zanr_t tempZanr;
  int o;
  while (1) {
    int lastId;
    fseek(f, 0, SEEK_SET);
    clearScreen();
    while (fread(&tempZanr, sizeof(Zanr_t), 1, f)) {
      printf("\b%i. %s\n", tempZanr.id, tempZanr.ime);
      lastId = tempZanr.id;
    }
    printf("Unesite id odabranog zanra: ");
    scanf("%i", &o);
    if (o >= 0 && o <= lastId)
      break;
  }
  return o;
}

int dodavanjeFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  int brFilmova = 0;
  Film_t tempFilm;
  while (fread(&tempFilm, sizeof(Film_t), 1, f))
    brFilmova++;
  fclose(f);
  f = fopen(videotekaFajl, "ab");
  if (f == NULL)
    return 1;
  Film_t film;
  film.id = brFilmova;
  printf("Unesite ime filma: ");
  //fgets(filmovi[brFilmova-1].ime, 50, stdin);
  scanf("%s", film.ime);
  fflush(stdin);
  printf("Unesite cenu filma: ");
  scanf("%f", &(film.cena));
  fflush(stdin);
  film.status = 0;

  int odabranZanr = odabirZanra();
  
  film.idZanr = odabranZanr;
  
  fwrite(&film, sizeof(Film_t), 1, f);

  fclose(f);
  
  return 0;
}

int brisanjeFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  int o = odabirFilma();
  int rBr = 0;
  Film_t film;
  while (fread(&film, sizeof(Film_t), 1, f)) {
    rBr++;
    if (film.id == o) {
      film.status = 1;
    }
  }
  fclose(f);
  f = fopen(videotekaFajl, "wb");
  if (f == NULL)
    return 1;
  fseek(f, sizeof(Film_t) * rBr, SEEK_SET);
  fwrite(&film, sizeof(Film_t), 1, f);
  fclose(f);
  return 0;
}

int azuriranjeFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  int o = odabirFilma();
  int rBr;
  Film_t film;
  while (fread(&film, sizeof(Film_t), 1, f)) {
    rBr++;
    if (film.id == o) {
      printf("Unesite ime filma (%s): ", film.ime);
      fgets(film.ime, 50, stdin);
      fflush(stdin);
      printf("Unseite cenu filma (%f): ", film.cena);
      scanf("%f", &(film.cena));
      fflush(stdin);
    }
  }
  fclose(f);
  f = fopen(videotekaFajl, "wb");
  if (f == NULL)
    return 1;
  fseek(f, sizeof(Film_t) * rBr, SEEK_SET);
  fwrite(&film, sizeof(Film_t), 1, f);
  fclose(f);
  return 0;
}

int dodavanjeZanra() { // srki
  FILE *f = fopen(zanroviFajl, "rb");
  if (f == NULL)
    return 1;
  int brZanrova = 0;
  Zanr_t tempZanr;
  while (fread(&tempZanr, sizeof(Zanr_t), 1, f))
    brZanrova++;
  fclose(f);
  f = fopen(zanroviFajl, "ab");
  if (f == NULL)
    return 1;
  Zanr_t zanr;
  zanr.id = brZanrova;
  printf("Unesite ime zanra: ");
  scanf("%s", zanr.ime);
  fflush(stdin);
  zanr.status = 0;
  fwrite(&zanr, sizeof(Zanr_t), 1, f);
  fclose(f);
  return 0;
}

int azuriranjeZanra(){ // srki
  FILE *f = fopen(zanroviFajl, "rb");
  if (f == NULL)
    return 1;
  int o = odabirZanra();
  int rBr;
  Zanr_t zanr;
  while (fread(&zanr, sizeof(Zanr_t), 1, f)) {
    rBr++;
    if (zanr.id == o) {
      printf("Unesite ime zanra (%s): ", zanr.ime);
      fgets(zanr.ime, 50, stdin);
      fflush(stdin);
    }
  }
  fclose(f);
  f = fopen(zanroviFajl, "wb");
  if (f == NULL)
    return 1;
  fseek(f, sizeof(Zanr_t) * rBr, SEEK_SET);
  fwrite(&zanr, sizeof(Zanr_t), 1, f);
  fclose(f);
  return 0;
}

int brisanjeZanra() { // srki
  FILE *f = fopen(zanroviFajl, "rb");
  if (f == NULL)
    return 1;
  int o = odabirZanra();
  int rBr = 0;
  Zanr_t zanr;
  while (fread(&zanr, sizeof(Zanr_t), 1, f)) {
    rBr++;
    if (zanr.id == o) {
      zanr.status = 1;
    }
  }
  fclose(f);
  f = fopen(zanroviFajl, "wb");
  if (f == NULL)
    return 1;
  fseek(f, sizeof(Zanr_t) * rBr, SEEK_SET);
  fwrite(&zanr, sizeof(Zanr_t), 1, f);
  fclose(f);
  return 0;
}

// kubini ispisi

int izdavanjeFilma(int idIzdavaca) {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  int rBr;
  Film_t film;
  int o = odabirFilma();
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id == o) {
      film.stanje = 0;
      film.brIzdavan++;
    }
  }
  fclose(f);
  dodavanjeRacuna(idIzdavaca, film.id);
  f = fopen(videotekaFajl, "wb");
  if (f == NULL)
    return 1;
  fseek(f, sizeof(Film_t) * rBr, SEEK_SET);
  fwrite(&film, sizeof(Film_t), 1, f);
  fclose(f);
  return 0;
}

struct tm* trenutnoVreme(){
  time_t mytime;
  mytime = time(NULL);
  struct tm *timeInfo;
  timeInfo = localtime(&mytime);
  timeInfo->tm_year+=1900;
  return timeInfo;
}

int dodavanjeRacuna(int idRad, int idFilm) {
  FILE *f = fopen(racuniFajl, "rb");
  if (f == NULL)
    return 1;
  Racun_t tempRacun;
  int brRacuna = 0;
  while (fread(&tempRacun, sizeof(Racun_t), 1, f))
    brRacuna++;
  fclose(f);
  f = fopen(racuniFajl, "ab");
  if (f == NULL)
    return 1;
  Racun_t racun;
  racun.id = brRacuna;
  racun.idIzdavaca = idRad;
  racun.idFilma = idFilm;
  printf("Pre vremena\n");
  //racuni[brRacuna-1].vreme = TrnVreme();
  racun.vremeIzdavanja = trenutnoVreme();
  printf("Posle vremena\n");
  fwrite(&racun, sizeof(Racun_t), 1, f);
  fclose(f);
  return 0;
}

int vracanjeFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  int rBr;
  Film_t film;
  int o = odabirFilma();
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id == o) {
      film.stanje = 1;
    }
  }
  fclose(f);
  f = fopen(videotekaFajl, "wb");
  if (f == NULL)
    return 1;
  fseek(f, sizeof(Film_t) * rBr, SEEK_SET);
  fwrite(&film, sizeof(Film_t), 1, f);
  fclose(f);
  return 0;
}

int ispisRacuna() {
  FILE *f = fopen(racuniFajl, "rb");
  if (f == NULL)
    return 1;
  Racun_t racun;
  while (fread(&racun, sizeof(Racun_t), 1, f)) {
    clearScreen();
    printf("ID racuna: %i\n", racun.id);
    printf("ID izdatog filma: %i\n", racun.idFilma);
    FILE *ffilmovi = fopen(videotekaFajl, "rb");
    if (ffilmovi == NULL) {
      fclose(f);
      return 1;
    }
    Film_t film;
    while (fread(&film, sizeof(Film_t), 1, ffilmovi)) {
      if (film.id == racun.idFilma)
        break;
    }
    fclose(ffilmovi);
    
    printf("Ime izdatog filma: %s\n", film.ime);
    printf("Vreme izdavanja filma: %i:%i\n", racun.vremeIzdavanja->tm_hour, racun.vremeIzdavanja->tm_min);
    printf("Da li zelite sledeci racun ili da prekinete pregled? (enter/q) ");
    int provera = 0;
    while (provera != 'q' && provera != '\n') {
      fflush(stdin);
      provera = fgetc(stdin);
      fflush(stdin);
    }
    if (provera == 'q')
      break;
  }
  fclose(f);
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