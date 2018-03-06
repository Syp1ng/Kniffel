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
int **Werte;


int main()
{
    //Program start
    init();
    SpielerAnDerReihe();
    return 0;
}
void AnzeigeTafel(){
printf("Kategorie      : Wertung :\n");
printf("Einser         : Augen(1):\n");
printf("Zweier         : Augen(2):\n");
printf("Dreier         : Augen(3):\n");
printf("Vierer         : Augen(4):\n");
printf("Fuenfer        : Augen(5):\n");
printf("Dreierpasch    :  Summe  :\n");
printf("Viererpasch    :  Summe  :\n");
printf("Full House     :    25   :\n");
printf("Kleine Strasse :    30   :\n");
printf("Grosse Strasse :    40   :\n");
printf("Kniffel        :    50   :\n");
printf("Chance         :  Summe  :\n");}
void SpielerAnDerReihe(){

    AnzeigeTafel();
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
    //Initalize Table
    Werte =(int **) malloc(13*sizeof(int *));
    for(int i=0;i<anzSpieler;i++) Werte[i]=(int *) malloc(anzSpieler*sizeof(int));


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
    for(int i =1; i<= 5; i++){
        char ctemp;
        printf("Moechtest du Wuerfel %d speichern? \n",i); //Gib j--> für Ja, n --> nein, #--> alles neu
        /*do{
        while (getchar() != '\n')
        continue;
        scanf(" %c", &ctemp);
        }while(ctemp != 'j'|| ctemp !='n' || ctemp!='#');*/
        while (getchar() != '\n')
        continue;
        scanf(" %c", &ctemp);

        if(ctemp == 'j'){
            tempWuerfel[WuerfelMitgenommen] = Wuerfel[i-1];          //Save it
            printf("Wuerfel %i wurde gespeichert!", i);
            WuerfelMitgenommen++;
        }
        else if(ctemp == 'n'){
            printf("Wuerfel %i wurde nicht gespeichert!", i);
        }

    }

    memccpy(Wuerfel, tempWuerfel,6*sizeof(int));
}

int zaehlen(int x){
    int rueckgabe = 0;
    for(int i = 0; i<5;i++)
    {
        if (Wuerfel[i]= x) rueckgabe+=x;
    }
    return rueckgabe;
}
int zaehlenalles(){
    int rueckgabe = 0;
    for(int i = 0; i<5;i++)
    {
        rueckgabe+=Wuerfel[i];
    }
    return rueckgabe;
}

void eingabe(){
    int punkte= 0;
    int aktion =0; //test
    switch(aktion){
case 0:
    //streichen
    break;
case 1:
    if (zaehlen(1)>0)punkte = zaehlen(1);
    break;
case 2:
    if (zaehlen(2)>0)punkte = zaehlen(2);
    break;
case 3:
    if (zaehlen(3)>0)punkte = zaehlen(3);
    break;
case 4:
    if (zaehlen(4)>0)punkte = zaehlen(4);
    break;
case 5:
    if (zaehlen(5)>0)punkte = zaehlen(5);
    break;
case 6:
    if (zaehlen(6)>0)punkte = zaehlen(6);
    break;
case 7:
    if (zaehlen(1)>0)punkte = zaehlen(1);
    break;
case 8:
    if (zaehlen(1)>0)punkte = zaehlen(1);
    break;
case 9:
    if (zaehlen(2)>0)punkte = zaehlen(2);
    break;
case 10:
    if (zaehlen(3)>0)punkte = zaehlen(3);
    break;
case 11:
    if (zaehlen(4)>0)punkte = zaehlen(4);
    break;
case 12:
    if (Wuerfel[0]==Wuerfel[1]&&Wuerfel[0]==Wuerfel[2]&&Wuerfel[0]==Wuerfel[3]&&Wuerfel[0]==Wuerfel[4]&&Wuerfel[0]==Wuerfel[5]) punkte = zaehlenalles();
    break;
case 13:
    punkte = zaehlenalles();
    break;
default:
    break;

    Werte[aktion][anzSpieler-1];

}
}

void WuerfelAnzeige(){
for(int i = 0;i<5; i++){
    switch(Wuerfel[i]){
   case 1:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|   #   ||  \n");
       printf("|       ||  \n");
       printf("|_______|/  \n");
       break;
    case 2:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| #     ||  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|_____#_|/  \n");
       break;
    case 3:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| #     ||  \n");
       printf("|       ||  \n");
       printf("|   #   ||  \n");
       printf("|       ||  \n");
       printf("|_____#_|/  \n");
       break;
    case 4:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| #   # ||  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("| #___#_|/  \n");
       break;
    case 5:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| #   # ||  \n");
       printf("|       ||  \n");
       printf("|   #   ||  \n");
       printf("|       ||  \n");
       printf("| #___#_|/  \n");
       break;
    case 6:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| #   # ||  \n");
       printf("|       ||  \n");
       printf("| #   # ||  \n");
       printf("|       ||  \n");
       printf("|_#___#_|/  \n");
       break;
    default: break;
   }
   }
}
