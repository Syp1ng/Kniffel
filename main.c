#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
////hallo

//Globale Variablen
int anzSpieler;
int aktSpieler=1;
int Wuerfel[];
int WuerfelMitgenommen =0;
int Wurf = 0; //Wurf <=3
int *p;



int main()
{
    //Program start
    init();
    SpielerAnDerReihe();
    return 0;
}
void SpielerAnDerReihe(){
    while(Wurf <=3){
    generate();   // generate a Random number
    WuerfelAnzeige();
    SelectCube();
    }
    WuerfelAnzeige();
    aktSpieler++;
    if(aktSpieler>anzSpieler)aktSpieler-anzSpieler;
}

void init() {
    printf("Geben Sie die Anzahl der Spieler ein: ");

    scanf("%i", &anzSpieler);

    printf("Anzahl der Spieler: %i\n", anzSpieler);
    char spielername [anzSpieler][30];

    printf("Bitte geben Sie %i Namen ein:\n", anzSpieler);

    for (int i = 0; i < anzSpieler; i++) {
        printf("Geben Sie Spielername %d an: ",i+1);
        scanf("%s", &spielername[i]);
    }

    for(int i = 0; i < anzSpieler; i++) {
        printf("Spieler %d = %s\n", i+1, spielername[i]);
    }

}
// the random function
void RandomNumberGenerator(const int nMin,const int nMax,const int  nNumOfNumsToGenerate){
    int nRandomNumber = 0;
    for (int i = 0; i < nNumOfNumsToGenerate; i++)
    {
        nRandomNumber = rand()%(nMax-nMin) + nMin;
        printf("%d ", nRandomNumber);
        Wuerfel[i+WuerfelMitgenommen]= nRandomNumber;

    }
}

void generate(){
    srand(time(NULL));
    RandomNumberGenerator(1,7,(5-WuerfelMitgenommen));   // generate a Random number
}

void SelectCube(){
    int tempWuerfel[5];
    WuerfelMitgenommen = 0;
    for(int i =1; i<= 6; i++){
        char ctemp;
        printf("Möchtest du Würfel %d speichern?",i); //Gib j--> für Ja, n --> nein, #--> alles neu
        do{
        scanf("%c", &ctemp);
        }while(ctemp != 'j'|| ctemp !='n' || ctemp!='#');

        if(ctemp == 'j'){
            tempWuerfel[WuerfelMitgenommen] = Wuerfel[i-1];          //Save it
            printf("Würfel %i wurde gespeichert!", i);
            WuerfelMitgenommen++;*/
        }
            else if(ctemp == 'n'){
                printf("Würfel %i wurde nicht gespeichert!", i);
            }
    }
    memccpy(Wuerfel, tempWuerfel,6*sizeof(int));
}

void WuerfelAnzeige(){
   for(int i = 0;i<6; i++){
    switch(Wuerfel[i]){
   case 1:
       printf("  _______   ");
       printf(" /______/|  ");
       printf("|       ||  ");
       printf("|       ||  ");
       printf("|   #   ||  ");
       printf("|       ||  ");
       printf("|_______|/  ");
       break;
    case 2:
       printf("  _______   ");
       printf(" /______/|  ");
       printf("| #     ||  ");
       printf("|       ||  ");
       printf("|       ||  ");
       printf("|       ||  ");
       printf("|_____#_|/  ");
       break;
    case 3:
       printf("  _______   ");
       printf(" /______/|  ");
       printf("| #     ||  ");
       printf("|       ||  ");
       printf("|   #   ||  ");
       printf("|       ||  ");
       printf("|_____#_|/  ");
       break;
    case 4:
       printf("  _______   ");
       printf(" /______/|  ");
       printf("| #   # ||  ");
       printf("|       ||  ");
       printf("|       ||  ");
       printf("|       ||  ");
       printf("| #___#_|/  ");
       break;
    case 5:
       printf("  _______   ");
       printf(" /______/|  ");
       printf("| #   # ||  ");
       printf("|       ||  ");
       printf("|   #   ||  ");
       printf("|       ||  ");
       printf("| #___#_|/  ");
       break;
    case 6:
       printf("  _______   ");
       printf(" /______/|  ");
       printf("| #   # ||  ");
       printf("|       ||  ");
       printf("| #   # ||  ");
       printf("|       ||  ");
       printf("|_#___#_|/  ");
       break;
    default: break;
   }
}
