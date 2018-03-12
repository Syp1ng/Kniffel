#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

//Globale Variablen
int anzSpieler;
int aktSpieler=1;
int Wuerfel[];
int WuerfelMitgenommen =0;
int Wurf = 0; //Wurf <=3
int **Werte;
//bool fertig = false;
char **name;
int main()
{
    //Program start
FarbeAendern();
    printf("hello");
    init();
    SpielerAnDerReihe();
    return 0;
}
void FarbeAendern(){
    char color;
printf("0 = Schwarz       8 = Grau/n");
printf("1 = Blau        9 = Hellblau/n");
printf("2 = Grün       A = Hellgrün/n");
printf("3 = Türkis        B = Helltürkis/n");
printf("4 = Rot         C = Hellrot/n");
printf("5 = Lila      D = Helllila/n");
printf("6 = Gelb      E = Hellgelb/n");
printf("7 = Hellgrau       F = Weiß/n");
printf("Bitte Farbe eingeben\n");
        scanf("%c", &color);
    switch(color){
case '0':
    system("color 00");
    break;
case '1':
    system("color 01");
    break;
case '2':
    system("color 02");
    break;
case '3':
    system("color 03");
    break;
case '4':
    system("color 04");
    break;
case '5':
    system("color 05");
    break;
case '6':
    system("color 06");
    break;
case '7':
    system("color 07");
    break;
case '8':
    system("color 08");
    break;
case '9':
    system("color 09");
    break;
case 'A':
    system("color 0A");
    break;
case 'B':
    system("color 0B");
    break;
case 'C':
    system("color 0C");
    break;
case 'D':
    system("color 0D");
    break;
case 'E':
    system("color 0E");
    break;
case 'F':
    system("color 0F");
    break;
default:
    system("color 0F");
    break;
}
}


void AnzeigeTafel(){ //Shows the scoretable
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

void SpielerAnDerReihe(){//controll structur 4 the game and playerchange
/////////////Test
    AnzeigeTafel();
    generate();   // generate a Random number

    printf("%s\n", name[0]);
    printf("%s\n", name[1]);
    //AnzeigeTafel();

    //eingabe();
    /////////////////////////////// Productiv
    /*while(wurf<3|| fertig!=false){
    }
    aktSpieler++;
    if(aktSpieler>anzSpieler)aktSpieler-anzSpieler;
    fertig = false;
    */

}

void init() { //initiallize array, player names
    printf("Geben Sie die Anzahl der Spieler ein: ");

    scanf("%i", &anzSpieler);

    printf("Anzahl der Spieler: %i\n", anzSpieler);
    char spielername [anzSpieler][30];


    name = malloc(anzSpieler * sizeof(char*));

    for(int i = 0; i < anzSpieler; i++) {
    name[i] = malloc((12 + 1) * sizeof(char));}
    printf("Bitte geben Sie %i Namen ein:\n", anzSpieler);

    for (int i = 0; i < anzSpieler; i++) {
        printf("Geben Sie Spielername %d an: ",i+1);
        scanf("%s", &spielername[i]);
        strcpy(name[i], spielername[i]);
    }

    for(int i = 0; i < anzSpieler; i++) {
        printf("Spieler %d = %s\n", i+1, spielername[i]);

    }
    //Initalize Table
    Werte =(int **) calloc(13,sizeof(int *));
    for(int i=0;i<13;i++) Werte[i]=(int *) calloc(anzSpieler,sizeof(int));

}

void generate(){//random number
    srand(time(NULL));
    RandomNumberGenerator(1,7,(5-WuerfelMitgenommen));   // generate a Random number
    WuerfelAnzeige();
}
// the random function
void RandomNumberGenerator(const int nMin,const int nMax,const int  nNumOfNumsToGenerate){ //generates random number
    int nRandomNumber = 0;
    for (int i = 0; i < nNumOfNumsToGenerate; i++)
    {
        nRandomNumber = rand()%(nMax-nMin) + nMin;
        printf("%d ", nRandomNumber);
        Wuerfel[i+WuerfelMitgenommen]= nRandomNumber;
    }
}

void SelectCube(){ //here the user tells the programm, which cubes he want to reroll or not
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

int zaehlen(int x){ //summ all the x-cubes
    int rueckgabe = 0;
    for(int i = 0; i<5;i++)
    {
        if (Wuerfel[i]==x) rueckgabe+=x;
    }
    return rueckgabe;
}
int zaehlenalles(){ //chekcs the sum of all cubes
    int rueckgabe = 0;
    for(int i = 0; i<5;i++)
    {
        rueckgabe+=Wuerfel[i];
    }
    return rueckgabe;
}
int zaehlengleiche(){ //chekcs how many times the most number is there
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

void eingabe(){ //here the user is able to tell the programm, where he writes something down
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
    if (zaehlengleiche()>3/*            */)punkte = zaehlen(2);
    break;
case 10:
    if ((zaehlen(1)>=1&&zaehlen(2)>=1&&zaehlen(3)>=1&&zaehlen(4)>=1)||
        (zaehlen(2)>=1&&zaehlen(3)>=1&&zaehlen(4)>=1&&zaehlen(5)>=1)||
        (zaehlen(3)>=1&&zaehlen(4)>=1&&zaehlen(5)>=1&&zaehlen(6)>=1))
        punkte=30;
    break;
case 11:
    if ((zaehlen(1)>=1&&zaehlen(2)>=1&&zaehlen(3)>=1&&zaehlen(4)>=1&&zaehlen(5)>=1)||
        (zaehlen(2)>=1&&zaehlen(3)>=1&&zaehlen(4)>=1&&zaehlen(5)>=1&&zaehlen(6)>=1)
        )punkte = 40;
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
   //fertig=true;
}

void WuerfelAnzeige(){ //Shows the number graphicaly
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

void GameOver(){ // Function 4 gameover, to set winner, display winner
    for(int i = 0; i<anzSpieler;i++){
        int ergebnis = 0;
        for(int j = 0; j<13;j++){
            ergebnis += Werte[j][i];
        }
        Werte[0][i] = ergebnis;
    }
    // Gewinner ausgeben in geordneter Reihenfolge;



    /*for(int i =0; i<anzSpieler;i++){
            printf("Platz %i: %s \n", (i+1);
    }
    printf("Ende");*/

}
