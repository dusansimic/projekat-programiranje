#ifndef FUNKCIJE_H_INCLUDED
#define FUNKCIJE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define duzina_stringa 100
#define broj_zaposlenih 50
#define broj_filmova 100
#define broj_zanrova 10
#define DATUM_LEN 100
#define VREME_LEN 100
#include <unistd.h>
#include <string.h>
#include "videoteka.h"
///*****************************STRUKTURE*****************************///

struct Zaposlen{
    int ID;
    char ime[duzina_stringa];
    char prezime[duzina_stringa];
    char zasnivanje[DATUM_LEN];
    char prestanak[DATUM_LEN];
    int id_statusa;///0-radnik 1-sef 2-obrisan NE RADI VISE
    char sifra[duzina_stringa];
};


struct Status{
    int ID;
    char datum[duzina_stringa];
    char vreme[duzina_stringa];
    int id_statusa;
};

///*****************************GLOBALNE PROMENLJIVE*****************************///

struct Status s[broj_zaposlenih];
struct Zaposlen z[broj_zaposlenih];
char datum[DATUM_LEN];
char vreme[VREME_LEN];

///*****************************FUNKCIJE*****************************///
void clrscr()
{
    system("@cls||clear");
}

void Zasnivanje()
{
    time_t t;
    t = time(NULL);
    struct tm *info;

    time(&t);
    info = localtime(&t);
    strftime(datum, DATUM_LEN, "%x", info);
    strftime(vreme, VREME_LEN, "%X", info);

}
void pravljenjeFajlova(){
    FILE *f;
    f = fopen("Zaposleni.dat","wb");
    fclose(f);
    f = fopen("Statusi zaposlenih.dat","wb");
    fclose(f);
    f = fopen("statusi.dat","wb");
    fclose(f);
    f = fopen("videoteka.dat","wb");
    fclose(f);
    f = fopen("zanrovi.dat","wb");
    fclose(f);
    f = fopen("racuni.dat","wb");
    fclose(f);
}


void dodajZaposlenog(){
    FILE *f;
    FILE *f2;
    f2 = fopen("Statusi zaposlenih.dat","ab+");
    f = fopen("Zaposleni.dat","ab+");
    int n;
    printf("unesi koliko zaposlenih hoces \n");
    scanf("%d",&n);
    int i = 0;
    for(i=0;i<n;i++){

        printf("unesi ID zaposlenog \n");
        scanf("%d",&z[i].ID);
        s[i].ID = z[i].ID;

        printf("unesi ime zaposlenog \n");
        fflush(stdin);
        gets(z[i].ime);

        printf("unesi prezime zaposlenog \n");
        fflush(stdin);
        gets(z[i].prezime);

        Zasnivanje();
        strcpy(z[i].zasnivanje, datum);
        strcpy(s[i].datum, datum);
        strcpy(s[i].vreme, vreme);

        printf("unesi id_statusa zaposlenog \n");
        scanf("%d",&z[i].id_statusa);
        s[i].id_statusa = z[i].id_statusa;

        printf("unesi sifru zaposlenog \n");
        fflush(stdin);
        gets(z[i].sifra);

        fwrite(&z[i],sizeof(z),1,f);
        fwrite(&s[i],sizeof(s),1,f2);

        clrscr();



    }
    fclose(f);
    fclose(f2);


}


void ispisSvih(){
    FILE *f;
    f = fopen("Zaposleni.dat","rb+");
    int i =0;
    while( (fread(&z[i],sizeof(z),1,f)) != NULL ){
        printf("ID: %d \n",z[i].ID);
        printf("Ime : %s \n",z[i].ime);
        printf("Prezime: %s \n",z[i].prezime);
        printf("zasnivanje: %s \n",z[i].zasnivanje);
        printf("id Statusa: %d \n",z[i].id_statusa);
        system("pause");
        clrscr();

    }
}



void proglasavanje_radnika_za_sefa(){
    FILE *f;
    FILE *f2;
    f2 = fopen("Statusi zaposlenih.dat","ab+");

    int id;
    int i = 0;
    int brojac = 0;
    int x = 0;

    f = fopen("Zaposleni.dat","rb+");
    printf("unesi id radnika \n");
    scanf("%d",&id);

    while( (fread(&z[i],sizeof(z),1,f)) != NULL ){
        i++;
        brojac++;
    }


    fclose(f);
    f = fopen("Zaposleni.dat","wb+");


    for(i=0;i<brojac;i++){

        if( id == z[i].ID && z[i].id_statusa == 0 ){

            z[i].id_statusa = 1;
            s[i].ID = z[i].ID;

            Zasnivanje();
            strcpy(s[i].datum, datum);
            strcpy(s[i].vreme, vreme);

            s[i].id_statusa = z[i].id_statusa;


            fwrite(&s[i],sizeof(s),1,f2);

        }
    }

    i = 0;

    for(i=0;i<brojac;i++){
        fwrite(&z[i],sizeof(z),1,f);
    }

    fclose(f);
    fclose(f2);

}


void davanje_otkaza(){
    FILE *f;
    FILE *f2;
    f2 = fopen("Statusi zaposlenih.dat","ab+");
    f = fopen("Zaposleni.dat","rb+");


    int i = 0;
    int brojac = 0;
    int id;

    while( (fread(&z[i],sizeof(z),1,f)) != NULL ){
        i++;
        brojac++;
    }


    printf("unesi ID zaposlenog \n");
    scanf("%d",&id);


    for(i=0;i<brojac;i++){

            if(z[i].ID == id){

                z[i].id_statusa = 2;
                s[i].ID = z[i].ID;

                Zasnivanje();
                strcpy(z[i].prestanak, datum);
                strcpy(s[i].datum, datum);
                strcpy(s[i].vreme, vreme);


                s[i].id_statusa = z[i].id_statusa;
                fwrite(&s[i],sizeof(s),1,f2);

            }

    }


    fclose(f);
    fclose(f2);


    f = fopen("Zaposleni.dat","wb");


    for(i=0;i<brojac;i++){
        if( z[i].id_statusa != 2 ){
            fwrite(&z[i],sizeof(z),1,f);
        }
    }

    system("pause");
    clrscr();
    fclose(f);
}



void ispisStatusa(){

        FILE *f2;
        f2 = fopen("Statusi zaposlenih.dat","rb+");

        int i=0;
        int brojac=0;

        while( fread(&s[i],sizeof(s),1,f2) != NULL ){
            i++;
            brojac++;
        }

        fclose(f2);

        for(i=0;i<brojac;i++){

            printf("ID: %d \n",s[i].ID);
            printf("Datum: %s \n",s[i].datum);
            printf("vreme: %s \n",s[i].vreme);
            printf("id statusa: %d \n",s[i].id_statusa);
            system("pause");
            clrscr();
        }

}

void Login(){

  char username[duzina_stringa];
  char sifra[duzina_stringa];
  int brojac = 0;//broji zaposlene
  int i = 0;
  FILE *f;
  f = fopen("zaposleni.dat","rb+");

  while( (fread(&z[i],sizeof(z),1,f)) != NULL ){
    brojac++;
    i++;
  }

  if( brojac == 0 ){

    clrscr();
    printf("ne postoji ni jedan zaposleni, dodaj zaposlenog: \n");
    pravljenjeFajlova();
    dodajZaposlenog();
  }
  brojac = 0;
  i = 0;
  while( (fread(&z[i],sizeof(z),1,f)) != NULL ){
    brojac++;
    i++;
  }

  printf("unesi username:\n");
  fflush(stdin);
  gets(username);

  printf("unesi sifru :\n");
  fflush(stdin);
  gets(sifra);



  i = 0;
  int x = -1;///redni broj;

  for(i=0;i<brojac;i++){
    if( (strcmp(z[i].sifra , sifra) == 0) && (strcmp(z[i].ime , username) == 0) ){
      x = i;
    }
  }


  if( x != -1 ){

    if( z[x].id_statusa == 0 ){

      int izbor;

      do{
        printf("1) Unos novog filma \n");
        printf("2) Brisanje filma\n");
        printf("3) Azuriranje filma\n");
        printf("4) Izdavanje filma \n");
        printf("5) Unos novog zanra \n");
        printf("6) Brisanje zanra \n");
        printf("7) Azuriranje zanra\n");
        printf("8) Ispis racuna\n");
        printf("9) Resetovanje videoteke\n");
        printf("10) Kraj rada \n");
        scanf("%d",&izbor);
        clrscr();
        switch(izbor){
          case 1:
            dodavanjeFilma();
            break;
          case 2:
            brisanjeFilma();
            break;
          case 3:
            azuriranjeFilma();
            break;
          case 4:
            izdavanjeFilma(x);
            break;
          case 5:
            dodavanjeZanra();
            break;
          case 6:
            brisanjeZanra();
            break;
          case 7:
            azuriranjeZanra();
            break;
          case 8:
            ispisRacuna();
            break;
          case 9:
            resetujBazu();
            break;
        }
      }while( izbor != 10 );

    }
    else if( z[x].id_statusa == 1 ){

      int izbor;

      do{
        printf("1) dodaj zaposlenog \n");
        printf("2) proglasavanje radnika za sefa \n");
        printf("3) davanje Otkaza \n");
        printf("4) ispis Svih \n");
        printf("5) ispis statusa zaposlenih \n");
        printf("6) brisanje fajlova \n");
        printf("7) KRAJ \n");
        scanf("%d",&izbor);
        clrscr();
        switch(izbor){
        case 1:
          dodajZaposlenog();
          break;
        case 2:
          proglasavanje_radnika_za_sefa();
          break;
        case 3:
          davanje_otkaza();
          break;
        case 4:
          ispisSvih();
          break;
        case 5:
          ispisStatusa();
          break;
        case 6:
          do{
            printf("1) brisanje zaposlenih \n");
            printf("2) brisanje statusa zaposlenih \n");
            printf("3) back \n");
            scanf("%d",&izbor);
            system("pause");
            clrscr();
            switch( izbor ){
              case 1:
                f = fopen("Zaposleni.dat","wb");
                fclose(f);
                break;
              case 2:
                f = fopen("Statusi zaposlenih.dat","wb");
                fclose(f);
                break;
            }
          }while( ((izbor != 1) && (izbor != 2)) && (izbor != 3) );

          break;
        }

      }while( izbor != 7 );
    }

  }
  else{
      printf("Zaposleni ne postoji \n");
  }

}

#endif // FUNKCIJE_H_INCLUDED
