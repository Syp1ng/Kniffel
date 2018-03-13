#include <stdio.h>
////TODO
//////////Abfrage/EIntragung nicht doppelt
//////////Fehlerüberprüfung Eingabe


//Globale Variablen
int anzSpieler;
int aktSpieler=1;
int Wuerfel[5];
int WuerfelMitgenommen =0;
int Wurf = 0; //Wurf <=3
int FarbenAktiviert =0;
int fertig = 0;
int **Werte;
char **name;
char *Farben;
char oe=(char)148; //Helpchars
char ue = (char)129;
char ss= (char) 225;


int main()
{
    //Program start
    //FarbeAendern();
    init();
    //Fuellen();
    SpielerAnDerReihe();
    return 0;
}

void FarbeAnzeigen(){
printf("0 = Schwarz      8 = Grau\n");
printf("1 = Blau         9 = Hellblau\n");
printf("2 = Gr%cn         A = Hellgr%cn\n", ue, ue);
printf("3 = T%crkis       B = Hellt%crkis\n", ue, ue);
printf("4 = Rot          C = Hellrot\n");
printf("5 = Lila         D = Helllila\n");
printf("6 = Gelb         E = Hellgelb\n");
printf("7 = Hellgrau     F = Weiss\n");
}
void FarbeAendern(char color){
    color = toupper(color);
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

void Fuellen(){ //test function
/*for(int i = 0;i<5; i++){
    for(int j = 0; j<12; j++){
        Werte[j][i]=i*5+1;
    }
}*/
}
void AnzeigeTafel(){ //Shows the scoretable
printf("   Kategorie      : Wertung :Spieler\n");
printf("1  Einser         : Augen(1): %i\n", Werte[0][aktSpieler-1]);
printf("2  Zweier         : Augen(2): %i\n", Werte[1][aktSpieler-1]);
printf("3  Dreier         : Augen(3): %i\n", Werte[2][aktSpieler-1]);
printf("4  Vierer         : Augen(4): %i\n", Werte[3][aktSpieler-1]);
printf("5  F%cnfer         : Augen(5): %i\n", ue, Werte[4][aktSpieler-1]);
printf("6  Sechser        : Augen(6): %i\n", Werte[5][aktSpieler-1]);
printf("   Summe oben     :         : %i\n", SummeOben(aktSpieler));
printf("   Bonus (bei 63P):   35    : %i\n", Bonus(aktSpieler));
printf("   Oberer Teil    :         : %i\n", SummeOben(aktSpieler)+Bonus(aktSpieler));
printf("7  Dreierpasch    :  Summe  : %i\n", Werte[6][aktSpieler-1]);
printf("8  Viererpasch    :  Summe  : %i\n", Werte[7][aktSpieler-1]);
printf("9  Full House     :    25   : %i\n", Werte[8][aktSpieler-1]);
printf("10 Kleine Stra%ce  :    30   : %i\n", ss, Werte[9][aktSpieler-1]);
printf("11 Gro%ce Stra%ce   :    40   : %i\n", ss, ss, Werte[10][aktSpieler-1]);
printf("12 Kniffel        :    50   : %i\n", Werte[11][aktSpieler-1]);
printf("13 Chance         :  Summe  : %i\n", Werte[12][aktSpieler-1]);
printf("   Summe unten    :         : %i\n", SummeUnten(aktSpieler)+Bonus(aktSpieler));
printf("   Gesamt         :         : %i\n", gesamt(aktSpieler));
}

void SpielerAnDerReihe(){//controll structur 4 the game and playerchange
    WuerfelMitgenommen=0;
    printf("\nSpieler %s ist an der Reihe!\n\n", name[aktSpieler-1]);
    if(FarbenAktiviert==1)FarbeAendern(Farben[aktSpieler-1]);
    while(Wurf<3 && fertig== 0){
            AnzeigeTafel();
            generate();
            if(Wurf<2)SelectCube();
            Wurf++;
          }
    if(fertig==0)eingabe();
          printf("Dein Spielstand:\n");
          AnzeigeTafel();
    aktSpieler++;
    if(aktSpieler>anzSpieler)aktSpieler=1;
    fertig = 0;
    Wurf =0;
    //Wenn alles ausgefüllt
    if(AllesAusgefuellt()==1)GameOver();
    else{SpielerAnDerReihe();}
}

int AllesAusgefuellt(){
for(int i=0;i<13;i++){
    if(Werte[i][anzSpieler-1]==0)
    return 0;
}
return 1;
}

void init() { //initiallize array, player names
    printf("Geben Sie die Anzahl der Spieler ein: ");
    scanf("%i", &anzSpieler);
    if (anzSpieler<1||anzSpieler>2147483647){ //Error if <0 ....
        printf("Fehler. Spieleranzahl wurde automatisch auf 1 gesetzt\n");
            anzSpieler=1;
        }

    printf("Anzahl der Spieler: %i\n", anzSpieler);
    char spielername [anzSpieler][30];

    char farbelesen;
    printf("M%cchten Sie mit unterschiedlichen Farben Spielen? F%cr ja bitte \"j\" oder \"1\": ", oe, ue);
    scanf(" %c", &farbelesen);
    farbelesen= tolower(farbelesen);
    if(farbelesen=='1'||farbelesen=='j'){FarbenAktiviert=1;
    printf("Hier sind die Farben: Jeder Spieler soll sich eine heraussuchen und nach seinem Namen eingeben.\n");
    Farben = malloc((anzSpieler+1) * sizeof(char*));//Farben
    FarbeAnzeigen();}
    else{printf("Farbfunktion nicht aktiv.\n");}
    name = malloc(anzSpieler * sizeof(char*));//Namen
    for(int i = 0; i < anzSpieler; i++) {
    name[i] = malloc((12 + 1) * sizeof(char));}
    printf("Bitte geben Sie %i Namen ein:\n", anzSpieler);

    for (int i = 0; i < anzSpieler; i++) {
        printf("Geben Sie Spielername %d an: ",i+1);
        scanf(" %s", &spielername[i]);
        strncpy(name[i], spielername[i],13);//Only size of 13
        name[i][13] = '\0'; //sting has to end, set manually
        if(FarbenAktiviert==1){
                printf("Deine Spielerfarbe bitte. Nur eine Zahl/Buchstabe: ");
                scanf(" %c", &Farben[i]);
                }
    }
    for(int i = 0; i < anzSpieler; i++) {
        printf("Spieler %d = %s\n", i+1, spielername[i]);

    }
    //Initalize Table
    Werte =(int **) malloc(13*sizeof(int *));
    for(int i=0;i<13;i++) Werte[i]=(int *) malloc(anzSpieler*sizeof(int));
    for(int i = 0;i<13;i++){ //set to 0
        for(int j = 0; j<anzSpieler; j++){
            Werte[i][j] =0;
        }
    }

}

int compare (const void * a, const void * b) {
   int value1=*(int*)a;
   int value2=*(int*)b;
   return value1-value2;
}
void generate(){//random number
    srand(time(NULL));
    RandomNumberGenerator(5-WuerfelMitgenommen);   // generate a Random number
    qsort(Wuerfel, 5, sizeof(int), compare);
    WuerfelAnzeige();
}
// the random function
void RandomNumberGenerator(int NumbersGenerate){ //generates random number
    int RandomNumber = 0;
    for (int i = 0; i < NumbersGenerate; i++)
    {
        RandomNumber = rand()%(6) + 1;
        printf("%d ", RandomNumber);//////MUSSSSSSSSSSSSSSSSSSSSS RAUS
        Wuerfel[i+WuerfelMitgenommen]= RandomNumber;
    }
}

void SelectCube(){ //here the user tells the programm, which cubes he want to reroll or not
    int tempWuerfel[5];
    WuerfelMitgenommen = 0;
    printf("\"J\" f%cr ja, \"N\" f%cr nein, \"e\" f%cr gleich eintragen und \"#\" f%ccr alle W%crfel neu w%crfeln. ", ue, ue, ue, ue,ue,ue);
    printf("Bei Falscheingabe wird Würfel nicht gespeichert!\n");
    for(int i =1; i<= 5; i++){
        char ctemp;
        printf("%s: Moechtest du Wuerfel %d speichern? \n", name[aktSpieler-1],i);
        /*do{
        while (getchar() != '\n')
        continue;
        scanf(" %c", &ctemp);
        }while(ctemp != 'j'|| ctemp !='n' || ctemp!='#');*/
        while (getchar() != '\n')
        continue;
        /*do{
            while (getchar() != '\n')
            continue;*/
            scanf(" %c", &ctemp);//}while(ctemp!='j'|| ctemp!='n'||ctemp!='e'|| ctemp!='#');
        ctemp = tolower(ctemp);
        if(ctemp == 'j'){
            tempWuerfel[WuerfelMitgenommen] = Wuerfel[i-1];          //Save it
            printf("W%crfel %i wurde gespeichert!\n",ue, i);
            WuerfelMitgenommen++;
        }
        else if(ctemp == 'e'){
            eingabe();
            break;
        }
        else if(ctemp == '#'){
            WuerfelMitgenommen=0;
            break;
        }
        else{
            printf("W%crfel %i wurde nicht gespeichert!\n", ue, i);
        }
    }
    memcpy(Wuerfel, tempWuerfel,WuerfelMitgenommen*sizeof(int));
    if(WuerfelMitgenommen==5)eingabe();
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
//////////////////////////////////////////////////////////////////////////////
}
return gleiche;
}
int FullHouseCheck(){
    int gleiche = 0, tempgleiche = 0, tempgleiche2=0;

for(int i = 1; i<=6;i++){//Zahlen

    for(int j = 0;j<5;j++){//Würfel

        if (Wuerfel[j]== i) tempgleiche++;
    }
    if (tempgleiche >gleiche){tempgleiche2= gleiche; gleiche = tempgleiche;}
    else if (tempgleiche>tempgleiche2)tempgleiche2= tempgleiche;
    tempgleiche=0;
//////////////////////////////////////////////////////////////////////////////
}
if(gleiche+tempgleiche2==5)return 1;
return 0;
}

void eingabe(){ //here the user is able to tell the programm, where he writes something down
    falsch:
    printf("Zahl eingeben, \"0\" f%cr Streichen.\n", ue);
    int punkte= 0;
    int aktion;
    while (getchar() != '\n')
        continue;
        scanf(" %i", &aktion);
if(aktion == 0)
    {}
else if(aktion>13)goto falsch;
else if(Werte[aktion-1][aktSpieler-1]!=0){ printf("Feld schon besetzt! \n"); goto falsch;}
    switch(aktion){
case 0:
    printf("Welches Feld willst du streichen?");
    while (getchar() != '\n')
        continue;
        int feld;
        scanf(" %i", &feld);
    if(Werte[feld-1][aktSpieler-1]==0){
        aktion=feld;
        punkte=-1;
    }
    else{
        printf("Kann nicht gestrichen werden.\n");
        goto falsch;
    }
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
    if (FullHouseCheck()==1 )punkte = 25;
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
    if (zaehlengleiche()== 5) punkte = 50;
    break;
case 13:
    punkte = zaehlenalles();
    break;
default:
    printf("Fehler!\n");
    goto falsch;
    break;
    }
   Werte[aktion-1][aktSpieler-1] = punkte;
   fertig=1;
}

void WuerfelAnzeige(){ // display dices graphically
printf("\n");
for(int i=0;i<5; i++) printf("  _______   "); // first line is the same for all dices
printf("\n");
for(int i=0;i<5; i++) printf(" /______/|  "); // secound line is the same for all dices
printf("\n");
for(int i=0;i<5; i++) // third line is not equal
{
    switch(Wuerfel[i]){         //Adapt third line to the corresponding number
    case 1:
        printf("|       ||  ");
        break;
    case 2:
    case 3:
        printf("| O     ||  "); // Number 2 and 3 have the same third line ( case 2 go to case 3 because no break)
        break;
    case 4:
    case 5:
    case 6:
        printf("| O   O ||  "); // Number 4,5,6 have the same third line ( case 4 and 5 go to case 6 because no break)
        break;
    default: break;
    }
}
printf("\n");
for(int i=0; i<5;i++) printf("|       ||  "); // fourth line is the same for all dices
printf("\n");
for(int i=0;i<5; i++)   //fifth line is not equal
{
    switch(Wuerfel[i]){     //Adapt third line to the corresponding number
    case 1:
    case 3:
    case 5:
        printf("|   O   ||  ");     // Number 1,3 and 5 have the same fifth line ( case 1 go to case 5 because no break)
        break;
    case 2:
    case 4:
        printf("|       ||  ");     // Number 2 and 4 have the same fifth line ( case 2 go to case 4 because no break)
        break;
    case 6:
        printf("| O   O ||  ");
        break;
    default: break;
    }
}
printf("\n");
for(int i=0; i<5;i++) printf("|       ||  ");   // // sixth line is the same for all dices
printf("\n");
for(int i=0;i<5; i++)       // seventh line is not equal
{
    switch(Wuerfel[i]){
    case 1:
        printf("|_______|/  ");
        break;
    case 2:
    case 3:
        printf("|_____O_|/  ");     // Number 2 and 3 have the same seventh line ( case 2 go to case 3 because no break)
        break;
    case 4:
    case 5:
    case 6:
        printf("|_O___O_|/  ");     // Number 4, 5 and 6 have the same seventh line ( case 4 and 5 go to case 6 because no break)
        break;
    default: break;
   }
}
printf("\n");
printf("\n");
/*Old Version:
for(int i = 0;i<5; i++){
    switch(Wuerfel[i]){
   case 1:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|   O   ||  \n");
       printf("|       ||  \n");
       printf("|_______|/  \n");
       break;
    case 2:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| O     ||  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|_____O_|/  \n");
       break;
    case 3:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| O     ||  \n");
       printf("|       ||  \n");
       printf("|   O   ||  \n");
       printf("|       ||  \n");
       printf("|_____O_|/  \n");
       break;
    case 4:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| O   O ||  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|       ||  \n");
       printf("|_O___O_|/  \n");
       break;
    case 5:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| O   O ||  \n");
       printf("|       ||  \n");
       printf("|   O   ||  \n");
       printf("|       ||  \n");
       printf("|_O___O_|/  \n");
       break;
    case 6:
       printf("  _______   \n");
       printf(" /______/|  \n");
       printf("| O   O ||  \n");
       printf("|       ||  \n");
       printf("| O   O ||  \n");
       printf("|       ||  \n");
       printf("|_O___O_|/  \n");
       break;
    default: break;
   }
   }
   */

}

void GameOver(){ // Function 4 gameover, to set winner, display winner
    printf("\n\n\n");
for(int i = 1;i<=anzSpieler;i++)
    {
        Werte[0][i-1] = gesamt(i); //save the score of each player in index 0
    }
for(int i = 1;i<=anzSpieler;i++){
    int maxvalue=0;
    int maxvaluespieler=0;
    for(int j = 0;j<anzSpieler;j++)
    {
        if (Werte[0][j]>maxvalue) {maxvalue=Werte[0][j];
        maxvaluespieler = j;}
    }

    printf("%i. Platz ist %s mit %i Punkten!\n", i,name[maxvaluespieler],maxvalue);
    Werte[0][maxvaluespieler]=-100;
}

printf("Kniffel: Developed by Andres Woerrlein, Dennis Wohlfarth, Fabian Schurk.\n");
}

int SummeOben(int Spieler){
    int sum = 0;
for(int i=0;i<6;i++){
    if(Werte[i][Spieler-1]!=-1){
    sum += Werte[i][Spieler-1];}
}
    return sum;
}
int SummeUnten(int Spieler){
    int sum = 0;
for(int i=6;i<13;i++){
    if(Werte[i][Spieler-1]!=-1){
    sum += Werte[i][Spieler-1];}
}
    return sum;
}
int Bonus(int Spieler){
if (SummeOben(Spieler)>=63)return 35;
return 0;
}
int gesamt(int Spieler){

return Bonus(Spieler)+SummeOben(Spieler)+SummeUnten(Spieler);
}
