#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dosya_kelimeler
{
    char dosya_kelime[50];
    int dosya_kelime_adet;
    struct dosya_kelimeler *dosya_kelime_sonraki;
    struct dosya_kelimeler *dosya_kelime_onceki;
};
typedef struct dosya_kelimeler dsy_klm;

dsy_klm *dsy_klm_ilk=NULL, *dsy_klm_son=NULL;
dsy_klm *dsy_klm_gezici=NULL;


struct kelimeler
{
    char kelime[50];
    int adet;
    struct kelimeler *sonraki;
    struct kelimeler *onceki;
};
typedef struct kelimeler klm;
klm *klm_ilk=NULL,*klm_son=NULL;
klm *klm_gezici=NULL;


int Liste_Ara(char aranacak[50])
{

    dsy_klm *gezici = dsy_klm_ilk;

    while(gezici!=NULL)
    {
        if (strcmp(gezici->dosya_kelime,aranacak)==0)
        {
            gezici->dosya_kelime_adet++;
            return 1;
        }
        gezici=gezici->dosya_kelime_sonraki;
    }
    return 0;
}


void Dosya_Liste_Yap(char gelen_kelime[50])
{
    int kelime_kontrol=0;
    kelime_kontrol=Liste_Ara(gelen_kelime);
    if(kelime_kontrol==0)
    {
        if(dsy_klm_ilk==NULL)
        {

            dsy_klm *dosya_yeni_dugum=(dsy_klm*)malloc(sizeof(dsy_klm));
            strcpy(dosya_yeni_dugum->dosya_kelime,gelen_kelime);
            dosya_yeni_dugum->dosya_kelime_adet=1;
            dosya_yeni_dugum->dosya_kelime_onceki=NULL;
            dosya_yeni_dugum->dosya_kelime_sonraki=NULL;
            dsy_klm_ilk=dosya_yeni_dugum;
            dsy_klm_son=dosya_yeni_dugum;
            return;

        }
        else
        {

            dsy_klm *gecici=dsy_klm_ilk;
            dsy_klm *dosya_yeni_dugum=(dsy_klm*)malloc(sizeof(dsy_klm));
            strcpy(dosya_yeni_dugum->dosya_kelime,gelen_kelime);
            dosya_yeni_dugum->dosya_kelime_adet=1;

            while(gecici->dosya_kelime_sonraki!=NULL)
            {
                gecici=gecici->dosya_kelime_sonraki;
            }
            gecici->dosya_kelime_sonraki=dosya_yeni_dugum;
            dosya_yeni_dugum->dosya_kelime_sonraki=NULL;
            dosya_yeni_dugum->dosya_kelime_onceki=NULL;

        }

    }
}


void Dosya_Okuma()
{
    FILE *dosya;
    char dosyaYolu[100]="C:\\Users\\hp\\Desktop\\MetinİslemeC\\Metin.txt";
    char satir[250];
    const char bosluk[2]=" ";
    char *token;
    char satirKontrol;
    char kelimeGecici[50];

    if((dosya=fopen(dosyaYolu,"r"))!=NULL)
    {
        while(!feof(dosya))
        {
            fscanf(dosya,"%s",&satir);
            token = strtok(satir, bosluk);
            strcpy(kelimeGecici,token);
            Dosya_Liste_Yap(kelimeGecici);
            token = strtok(NULL,bosluk);
            while( token != NULL )
            {
                strcpy(kelimeGecici,token);
                Dosya_Liste_Yap(kelimeGecici);
                token = strtok(NULL,bosluk);

            }
        }
    }
}

void Kelime_Liste_Basa_Ekle(char gelen_kelime[50],int gelen_adet)
{
    klm *yeni_dugum=(klm*)malloc(sizeof(klm));
    strcpy(yeni_dugum->kelime,gelen_kelime);
    yeni_dugum->adet=gelen_adet;

    yeni_dugum->sonraki=klm_gezici;
    yeni_dugum->onceki=NULL;
    klm_ilk=yeni_dugum;
    return;
}

void Kelime_Liste_Sona_Ekle(char gelen_kelime[50],int gelen_adet)
{
    klm *yeni_dugum=(klm*)malloc(sizeof(klm));
    strcpy(yeni_dugum->kelime,gelen_kelime);
    yeni_dugum->adet=gelen_adet;

    klm_gezici->sonraki=yeni_dugum;
    yeni_dugum->onceki=klm_gezici;
    yeni_dugum->sonraki=NULL;
    klm_son=yeni_dugum;
    return;
}

void Kelime_Liste_Araya_Ekle(char gelen_kelime[50],int gelen_adet)
{
    klm *yeni_dugum=(klm*)malloc(sizeof(klm));
    strcpy(yeni_dugum->kelime,gelen_kelime);
    yeni_dugum->adet=gelen_adet;

    klm *gecici=klm_gezici->sonraki;
    klm_gezici->sonraki=yeni_dugum;
    yeni_dugum->sonraki=gecici;
    yeni_dugum->onceki=klm_gezici;
    gecici->onceki=yeni_dugum;
}


void Kelime_Liste_Olustur(char gelen_kelime[50],int gelen_adet)
{
    if(klm_ilk==NULL)
    {
        klm *yeni_dugum=(klm*)malloc(sizeof(klm));
        strcpy(yeni_dugum->kelime,gelen_kelime);
        yeni_dugum->adet=gelen_adet;

        yeni_dugum->sonraki=NULL;
        yeni_dugum->onceki=NULL;
        klm_ilk=yeni_dugum;
        klm_son=yeni_dugum;
        return;
    }
    else
    {
        klm_gezici=klm_ilk;
        if(klm_gezici->adet < gelen_adet && klm_gezici==klm_ilk)
        {
            Kelime_Liste_Basa_Ekle(gelen_kelime,gelen_adet);
            return;
        }

        while(klm_gezici->sonraki!=NULL && klm_gezici->sonraki->adet > gelen_adet)
        {
            klm_gezici=klm_gezici->sonraki;
        }

        if(klm_gezici->sonraki==NULL)
        {
            Kelime_Liste_Sona_Ekle(gelen_kelime,gelen_adet);
            return;
        }
        Kelime_Liste_Araya_Ekle(gelen_kelime,gelen_adet);
        return;
    }
}

void Birlestirici()
{
    dsy_klm *gezici=dsy_klm_ilk;
    while(gezici!=NULL)
    {
        Kelime_Liste_Olustur(gezici->dosya_kelime,gezici->dosya_kelime_adet);
        gezici=gezici->dosya_kelime_sonraki;
    }
}

void Listele()
{
   klm *gezici=klm_ilk;
    while(gezici!=NULL)
    {
        printf("Kelime : %s  Kelime Adeti : %d \n",gezici->kelime,gezici->adet);
        gezici=gezici->sonraki;
    }
}


int main()
{
Dosya_Okuma();
Birlestirici();
Listele();
    return 0;
}
