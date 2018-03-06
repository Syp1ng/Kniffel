#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
printf("Kategorie      : Wertung :Spieler\n");
printf("Einser         : Augen(1): %i\n", Werte[0][aktSpieler-1]);
printf("Zweier         : Augen(2): %i\n", Werte[1][aktSpieler-1]);
printf("Dreier         : Augen(3): %i\n", Werte[2][aktSpieler-1]);
printf("Vierer         : Augen(4): %i\n", Werte[3][aktSpieler-1]);
printf("Fuenfer        : Augen(5): %i\n", Werte[4][aktSpieler-1]);
printf("Sechser        : Augen(6): %i\n", Werte[5][aktSpieler-1]);
printf("Dreierpasch    :  Summe  : %i\n", Werte[6][aktSpieler-1]);
printf("Viererpasch    :  Summe  : %i\n", Werte[7][aktSpieler-1]);
printf("Full House     :    25   : %i\n", Werte[8][aktSpieler-1]);
printf("Kleine Strasse :    30   : %i\n", Werte[9][aktSpieler-1]);
printf("Grosse Strasse :    40   : %i\n", Werte[10][aktSpieler-1]);
printf("Kniffel        :    50   : %i\n", Werte[11][aktSpieler-1]);
printf("Chance         :  Summe  : %i\n", Werte[12][aktSpieler-1]);
}

void SpielerAnDerReihe(){

    AnzeigeTafel();
    generate();   // generate a Random number
    AnzeigeTafel();
    //eingabe();
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
    Werte =(int **) calloc(13,sizeof(int *));
    for(int i=0;i<13;i++) Werte[i]=(int *) calloc(anzSpieler,sizeof(int));


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
    WuerfelAnzeige();
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
        if (Wuerfel[i]==x) rueckgabe+=x;
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
int zaehlengleiche(){
int gleiche = 0, tempgleiche = 0;

for(int i = 1; i<=6;i++){

    for(int j = 0;j<5;j++){

        if (Wuerfel[j]== i) tempgleiche++;
    }
    if (tempgleiche >gleiche) gleiche= tempgleiche;
    tempgleiche=0;

}
return gleiche;
}

void eingabe(){
    int aktion;
    while (getchar() != '\n')
        continue;
        scanf(" %i", &aktion);
    int punkte= 0;
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
    if (zaehlengleiche()>=3) punkte = zaehlenalles();
    break;
case 8:
    if (zaehlengleiche()>=4) punkte = zaehlenalles();
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
    }
    AnzeigeTafel();
   // Werte[aktion-1][aktSpieler-1] = punkte;
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
