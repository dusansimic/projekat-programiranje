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

int clearScreen() {
  system("@cls||clear");
  return 0;
}

int makeTempFilmovi() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  FILE *ftemp = fopen("temp.dat", "wb");
  if (ftemp == NULL)
    return 2;
  Film_t film;
  while (fread(&film, sizeof(Film_t), 1, f)) {
    fwrite(&film, sizeof(Film_t), 1, ftemp);
  }
  fclose(f);
  fclose(ftemp);
  return 0;
}

int azurirajFilmove(Film_t filmZaUnos) {
  FILE *f = fopen(videotekaFajl, "wb");
  if (f == NULL)
    return 1;
  FILE *ftemp = fopen("temp.dat", "rb");
  if (ftemp == NULL)
    return 2;
  Film_t film;
  while (fread(&film, sizeof(Film_t), 1, ftemp)) {
    if (film.id == filmZaUnos.id) {
      fwrite(&filmZaUnos, sizeof(Film_t), 1, f);
    } else {
      fwrite(&film, sizeof(Film_t), 1, f);
    }
  }
  fclose(f);
  fclose(ftemp);
  return 0;
}

int makeTempZanrovi() {
  FILE *f = fopen(zanroviFajl, "rb");
  if (f == NULL)
    return 1;
  FILE *ftemp = fopen("temp.dat", "wb");
  if (ftemp == NULL)
    return 2;
  Zanr_t zanr;
  while (fread(&zanr, sizeof(Zanr_t), 1, f)) {
    fwrite(&zanr, sizeof(Zanr_t), 1, ftemp);
  }
  fclose(f);
  fclose(ftemp);
  return 0;
}

int azurirajZanrove(Zanr_t zanrZaUnos) {
  FILE *f = fopen(zanroviFajl, "wb");
  if (f == NULL)
    return 1;
  FILE *ftemp = fopen("temp.dat", "rb");
  if (ftemp == NULL)
    return 2;
  Zanr_t zanr;
  while (fread(&zanr, sizeof(Zanr_t), 1, ftemp)) {
    if (zanr.id == zanrZaUnos.id) {
      fwrite(&zanrZaUnos, sizeof(Zanr_t), 1, f);
    } else {
      fwrite(&zanr, sizeof(Zanr_t), 1, f);
    }
  }
  fclose(f);
  fclose(ftemp);
  return 0;
}

int odabirFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return -1;
  Film_t film;
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
  clearScreen();
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
  int rBr = 0;
  Film_t film;
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id == o) {
      printf("Unesite ime filma (%s): ", film.ime);
      fgets(film.ime, 50, stdin);
      fflush(stdin);
      printf("Unseite cenu filma (%f): ", film.cena);
      scanf("%f", &(film.cena));
      fflush(stdin);
      break;
    }
    rBr++;
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
  int rBr = 0;
  Zanr_t zanr;
  while (fread(&zanr, sizeof(Zanr_t), 1, f)) {
    if (zanr.id == o) {
      printf("Unesite ime zanra (%s): ", zanr.ime);
      fgets(zanr.ime, 50, stdin);
      fflush(stdin);
      break;
    }
    rBr++;
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
  clearScreen();
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  int rBr = 0;
  Film_t film;
  int o = odabirFilma();
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id == o) {
      film.brIzdavan++;
      break;
    }
    rBr++;
  }
  fclose(f);
  makeTempFilmovi(); // pravljenje privremene datoteke za azuriranje
  azurirajFilmove(film); // azuriranje originalne datoteke
  dodavanjeRacuna(idIzdavaca, film.id);
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
  racun.vremeIzdavanja = trenutnoVreme();
  fwrite(&racun, sizeof(Racun_t), 1, f);
  fclose(f);
  return 0;
}

int vracanjeFilma() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  int rBr = 0;
  Film_t film;
  int o = odabirFilma();
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id == o) {
      break;
    }
    rBr++;
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

// srediti da se koriste nove funkcije za citanje i pisanje
int resetujBazu() {
  int br = 0;
  Film_t *filmovi = malloc(0);
  FILE *f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(filmovi, sizeof(Film_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n\b(filmovi)\n");
  free(filmovi);

  Zanr_t *zanrovi = malloc(0);
  f = fopen(zanroviFajl, "wb");
  if (f != NULL) {
    fwrite(zanrovi, sizeof(Zanr_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n\b(zanrovi)\n");
  free(zanrovi);

  Racun_t *racuni = malloc(0);
  f = fopen(racuniFajl, "wb");
  if (f != NULL) {
    fwrite(racuni, sizeof(Racun_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n\b(racuni)\n");
  free(racuni);

  Film_t film;
  f = fopen("temp.dat", "wb");
  if (f != NULL) {
    fwrite(&film, sizeof(Film_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n\b(temp)\n");

  printf("Baza podataka je uspesno resetovana!\n");
  return 0;
}