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

Film_t popularnost[5];

int clearScreen() {
  system("@cls||clear");
  return 0;
}

int obrisiSlRed(char *string) {
  int i = 0;
  while (string[i] != '\0') {
    if (string[i] == '\n')
      string[i] = '\0';
    i++;
  }
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
      if (!film.status) {
        printf("\b%i. %s\n", film.id, film.ime);
        lastId = film.id;
      }
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
      if (!tempZanr.status) {
        printf("\b%i. %s\n", tempZanr.id, tempZanr.ime);
        lastId = tempZanr.id;
      }
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
  fflush(stdin);
  fgets(film.ime, 50, stdin);
  obrisiSlRed(film.ime);
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
  makeTempFilmovi();
  azurirajFilmove(film);
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
      fflush(stdin);
      fgets(film.ime, 50, stdin);
      obrisiSlRed(film.ime);
      fflush(stdin);
      printf("Unseite cenu filma (%.2f): ", film.cena);
      scanf("%f", &(film.cena));
      fflush(stdin);
      break;
    }
    rBr++;
  }
  fclose(f);
  makeTempFilmovi();
  azurirajFilmove(film);
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
      scanf("%s", zanr.ime);
      fflush(stdin);
      break;
    }
    rBr++;
  }
  fclose(f);
  makeTempZanrovi();
  azurirajZanrove(zanr);
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
  makeTempZanrovi();
  azurirajZanrove(zanr);
  return 0;
}

// kubini ispisi

int glavniMeni() {
  int state = 1;
  int filmId;
  while (state) {
    int o = izborFilma();
    switch (o) {
      case 0:
        state = 0;
        break;
      case 1:
        state = 0;
        filmId = izborFilmaPoImenu();
        break;
      case 2:
        state = 0;
        filmId = izborFilmaPoZanru();
        break;
      case 3:
        state = 0;
        filmId = izborFilmaPoPopularnosti();
        break;
    }
  }
  return filmId;
}

int sortirajPoPopularnosti() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  Film_t film;
  popularnost[0].brIzdavan = 0;
  popularnost[1].brIzdavan = 0;
  popularnost[2].brIzdavan = 0;
  popularnost[3].brIzdavan = 0;
  popularnost[4].brIzdavan = 0;
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.brIzdavan >= popularnost[0].brIzdavan && !film.status) {
      popularnost[0] = film;
    }
  }
  fseek(f, 0, SEEK_SET);
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id != popularnost[0].id && film.brIzdavan >= popularnost[1].brIzdavan && !film.status) {
      popularnost[1] = film;
    }
  }
  fseek(f, 0, SEEK_SET);
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id != popularnost[0].id && \
        film.id != popularnost[1].id && \
        film.brIzdavan >= popularnost[2].brIzdavan && \
        !film.status) {
      popularnost[2] = film;
    }
  }
  fseek(f, 0, SEEK_SET);
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id != popularnost[0].id && \
        film.id != popularnost[1].id && \
        film.id != popularnost[2].id && \
        film.brIzdavan >= popularnost[3].brIzdavan && \
        !film.status) {
      popularnost[3] = film;
    }
  }
  fseek(f, 0, SEEK_SET);
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (film.id != popularnost[0].id && \
        film.id != popularnost[1].id && \
        film.id != popularnost[2].id && \
        film.id != popularnost[3].id && \
        film.brIzdavan >= popularnost[4].brIzdavan && \
        !film.status) {
      popularnost[4] = film;
    }
  }
  return 0;
}

int izborFilma() {
  int o;
  while (1) {
    clearScreen();
    printf("\b1) Odabir filma po imenu\n");
    printf("\b2) Odabir filma zanru\n");
    printf("\b3) Odabir filma po popularnosti\n");
    printf("\b0) Prekinite biranje\n");
    printf("Unesite vas izbor: ");
    scanf("%i", &o);
    if (o > 0 && o < 4)
      break;
  }
  return o;
}

int izborFilmaPoImenu() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return -1;
  Film_t film;
  char imeFilma[50];
  printf("Unesite ime filma za trazenje: ");
  fflush(stdin);
  fgets(imeFilma, 50, stdin);
  obrisiSlRed(imeFilma);
  fflush(stdin);
  while (fread(&film, sizeof(Film_t), 1, f)) {
    if (strcmp(imeFilma, film.ime) == 0 && !film.status)
      break;
  }
  return film.id;
}

int izborFilmaPoZanru() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return -1;
  int o = odabirZanra();
  Film_t film;
  int p;
  int minId = -1, maxId = 0;
  while (1) {
    fseek(f, 0, SEEK_SET);
    clearScreen();
    while (fread(&film, sizeof(Film_t), 1, f)) {
      if (film.idZanr == o && !film.status) {
        if (minId < 0)
          minId = film.id;
        maxId = film.id;
        printf("%i. %s\n", film.id, film.ime);
      }
    }
    printf("Unesite id izabranog filma: ");
    fflush(stdin);
    scanf("%i", &p);
    fflush(stdin);
    if (p >= minId && p <= maxId)
      break;
  }
  return p;
}

int izborFilmaPoPopularnosti() {
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 0;
  sortirajPoPopularnosti();
  int i;
  int o;
  clearScreen();
  for (i = 0; i < 5; i++) {
    printf("%i) %s\n", popularnost[i].id, popularnost[i].ime);
  }
  printf("-1) Prekinite biranje\n");
  printf("Unesite id izabranog filma: ");
  fflush(stdin);
  scanf("%i", &o);
  fflush(stdin);
  return o;
}

int izdavanjeFilma(int idIzdavaca) {
  clearScreen();
  FILE *f = fopen(videotekaFajl, "rb");
  if (f == NULL)
    return 1;
  int rBr = 0;
  Film_t film;
  int o = glavniMeni();
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

int vracanjeFilma() { // ne koristi se
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
    printf("\n\n\n\n\tID racuna: %i\n\n", racun.id);
    printf("\tID izdatog filma: %i\n\n", racun.idFilma);
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

    printf("\tIme izdatog filma: %s\n\n", film.ime);
    printf("\tVreme izdavanja filma: %i:%i\n\n", racun.vremeIzdavanja->tm_hour, racun.vremeIzdavanja->tm_min);
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
  Film_t film;
  FILE *f = fopen(videotekaFajl, "wb");
  if (f != NULL) {
    fwrite(&film, sizeof(Film_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n\b(filmovi)\n");

  Zanr_t zanr;
  f = fopen(zanroviFajl, "wb");
  if (f != NULL) {
    fwrite(&zanr, sizeof(Zanr_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n\b(zanrovi)\n");

  Racun_t racun;
  f = fopen(racuniFajl, "wb");
  if (f != NULL) {
    fwrite(&racun, sizeof(Racun_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n\b(racuni)\n");

  f = fopen("temp.dat", "wb");
  if (f != NULL) {
    fwrite(&film, sizeof(Film_t), br, f);
  } else
    printf("Greska pri radu sa fajlom\n\b(temp)\n");

  printf("Baza podataka je uspesno resetovana!\n");
  return 0;
}
