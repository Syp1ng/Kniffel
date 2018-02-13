#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
////hallo

//Globale Variablen
int anzSpieler;
int aktSpieler=1;
int aktWuerfel[];
int saveWuerfel[];
int main()
{
    //Program start
    init();
    wuerfeln();
    AnzeigeSpieler();
    return 0;
}


    void init() {

    printf("Geben Sie die Anzahl der Spieler ein: ");

    scanf("%i", &anzSpieler);

    printf("Anzahl der Spieler: %i\n", anzSpieler);

    char spielername [anzSpieler][30];

    printf("Bitte geben Sie %i Namen ein:\n", anzSpieler);

    for (int i = 0; i < anzSpieler; i++) {
        printf("spielername[%i] = ",i);
        scanf("%s", &spielername[i]);
    }

    printf("\nTesten\n\n");

    for(int i = 0; i < anzSpieler; i++) {
        printf("%s\n", spielername[i]);
    }
}

// the random function
void RandomNumberGenerator(const int nMin,const int nMax,const int  nNumOfNumsToGenerate)
{
int nRandomNumber = 0;
for (int i = 0; i < nNumOfNumsToGenerate; i++)
{
nRandomNumber = rand()%(nMax-nMin) + nMin;
aktWuerfel[i]= nRandomNumber;
printf("%d ", aktWuerfel[i]);
}
printf("\n");
printf("%d\n",aktWuerfel[0]);
}

void generate()
{
srand(time(NULL));
RandomNumberGenerator(1,7,5);   // generate a Random number
}

void wuerfeln()
{
    generate();

}

void AnzeigeSpieler()
{

    int antwort;
    printf("Spielername[i]");
    printf("Nochmal neu wuerfeln ? 0 = no/1 = yes?");
    scanf("%i", &antwort);
    if(antwort == 0)
    {
        //wuerfeln();
        printf("Wie viel Wuerfel möchtest du speichern? zwischen 1-4");
        scanf("%i",&antwort);
        if(antwort <=0 || antwort >4)
        {
            printf("Wie viel Wuerfel möchtest du speichern? zwischen 1-4");
        }
        else if(antwort>0&& antwort <5)
        {
            for(int i = 0;i<antwort;i++)
            printf("Welche Wuerfelnummer willst du speichern ? 0-4");
           // scanf("%d",&saveWuerfel[i]);
        }

    }
    else if(antwort == 1)
    {
        wuerfeln();


    }



    //////////////////helllllloooooooooooooooooooooooooooooo

}

