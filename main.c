#include <stdio.h> //printf getchar
#include <stdlib.h> //srand, malloc, qsort, system
#include <ctype.h> //toUpper
#include <string.h> //memcpy, strncpy
#include <time.h> //time

//Developed by Andreas Wörrlein, Dennis Wohlfarth, Fabian Schurk
//The created zip with the Kniffel.exe triggered an alarm in our company. It says it's a trojaner.....
//additional features: colormode, sorting of the cubes.

int PlayerNumber; //How many Players play the game
int CurrentPlayer=1; //Which Player plays right now
int Cube[5]; //Saves the values of the cubes, 5 Cubes
int CubesPutAway =0; //How many cubes the player saves, the other cubes reroll
int Throw = 0; //Throws <=3 //Player has 3 throws a round
int ColorMode =0;//Player can select a color
int Finish = 0; //Tells when player has filled out table
int **Values; //Saves the score table [field][player]
char **Names;//Saves the names of the [player]
char *Colors;//Saves the color of the [player]
char oe=(char)148; //Helpchar Ö
char ue = (char)129;//Helpchar Ü
char ss= (char) 225;//Helpchar ß

void Clear(){ // Buffer clear of scanf
while (getchar() != '\n')
        continue;}
void ShowCubes(){ // display dices graphically
printf("\n");
printf("%d. Wurf:\n",Throw+1);
for(int i=0;i<5; i++) printf("  _______   "); // first line is the same for all dices
printf("\n");
for(int i=0;i<5; i++) printf(" /______/|  "); // secound line is the same for all dices
printf("\n");
for(int i=0;i<5; i++) //third line is not equal
{
    switch(Cube[i]){         //Adapt third line to the corresponding number
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
    switch(Cube[i]){     //Adapt third line to the corresponding number
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
    switch(Cube[i]){
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
int SumTop(int player){//calculates the sum of the top score table
    int sum = 0;
for(int i=0;i<6;i++){
    if(Values[i][player-1]!=-1){//-1 is cross
    sum += Values[i][player-1];}
}
    return sum;
}
int SumButtom(int player){//calculates the sum of the buttom score table
    int sum = 0;
for(int i=6;i<14;i++){
    if(Values[i][player-1]!=-1){//-1 is cross
    sum += Values[i][player-1];}
}
    return sum;
}
int Bonus(int player){ //Bonus if SumTop>63
if (SumTop(player)>=63)return 35;
return 0;
}
int TotalSum(int player){ //Total Score of Player

return Bonus(player)+SumTop(player)+SumButtom(player);
}
void GameOver(){ // Function 4 gameover, to set winner, display winner
    printf("\n\n\n");
for(int i = 1;i<=PlayerNumber;i++)
    {
        Values[0][i-1] = TotalSum(i); //save the score of each player in index 0
    }
for(int i = 1;i<=PlayerNumber;i++){
    int maxvalue=0;
    int maxvaluespieler=0;
    for(int j = 0;j<PlayerNumber;j++)
    {
        if (Values[0][j]>maxvalue) {maxvalue=Values[0][j];
        maxvaluespieler = j;}
    }

    printf("%d. Platz ist %s mit %d Punkten!\n", i,Names[maxvaluespieler],maxvalue);
    Values[0][maxvaluespieler]=-100;
}

printf("Kniffel: Developed by Andreas W%crrlein, Dennis Wohlfarth, Fabian Schurk.\n",oe);
}
void ShowColorsAvailible(){  //Shows the color table with number
printf("0 = Schwarz      8 = Grau\n");
printf("1 = Blau         9 = Hellblau\n");
printf("2 = Gr%cn         A = Hellgr%cn\n", ue, ue);
printf("3 = T%crkis       B = Hellt%crkis\n", ue, ue);
printf("4 = Rot          C = Hellrot\n");
printf("5 = Lila         D = Helllila\n");
printf("6 = Gelb         E = Hellgelb\n");
printf("7 = Hellgrau     F = Weiss\n");
}
void ChangeColor(char color){ //Changes Color of the console
    color = toupper(color);
switch(color){ //different color for char
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
void ShowScoreTable(){ //Shows the scoretable of the current Player
printf("   Kategorie      : Wertung : Punkte  \n");
printf("1  Einser         : Augen(1):   %d\n", Values[0][CurrentPlayer-1]);
printf("2  Zweier         : Augen(2):   %d\n", Values[1][CurrentPlayer-1]);
printf("3  Dreier         : Augen(3):   %d\n", Values[2][CurrentPlayer-1]);
printf("4  Vierer         : Augen(4):   %d\n", Values[3][CurrentPlayer-1]);
printf("5  F%cnfer         : Augen(5):   %d\n", ue, Values[4][CurrentPlayer-1]);
printf("6  Sechser        : Augen(6):   %d\n", Values[5][CurrentPlayer-1]);
printf("   Summe oben     :         :   %d\n", SumTop(CurrentPlayer));
printf("   Bonus (bei 63P):   35    :   %d\n", Bonus(CurrentPlayer));
printf("   Oberer Teil    :         :   %d\n", SumTop(CurrentPlayer)+Bonus(CurrentPlayer));
printf("7  Dreierpasch    :  Summe  :   %d\n", Values[6][CurrentPlayer-1]);
printf("8  Viererpasch    :  Summe  :   %d\n", Values[7][CurrentPlayer-1]);
printf("9  Full House     :    25   :   %d\n", Values[8][CurrentPlayer-1]);
printf("10 Kleine Stra%ce  :    30   :   %d\n", ss, Values[9][CurrentPlayer-1]);
printf("11 Gro%ce Stra%ce   :    40   :   %d\n", ss, ss, Values[10][CurrentPlayer-1]);
printf("12 Kniffel        :    50   :   %d\n", Values[11][CurrentPlayer-1]);
printf("13 Chance         :  Summe  :   %d\n", Values[12][CurrentPlayer-1]);
printf("   Weitere Kniffel:         :   %d\n", Values[13][CurrentPlayer-1]);
printf("   Summe unten    :         :   %d\n", SumButtom(CurrentPlayer)+Bonus(CurrentPlayer));
printf("   Gesamt         :         :   %d\n", TotalSum(CurrentPlayer));
}
//Evaluation
int Count(int x){ //summ all the x-cubes
    int rueckgabe = 0;
    for(int i = 0; i<5;i++)
    {
        if (Cube[i]==x) rueckgabe+=x;
    }
    return rueckgabe;
}
int CountEverything(){ //counts the sum of all cubes
    int rueckgabe = 0;
    for(int i = 0; i<5;i++)
    {
        rueckgabe+=Cube[i];
    }
    return rueckgabe;
}
int CountSameValues(){ //checks how many times the most number is there
int same = 0, tempSame = 0;

for(int i = 1; i<=6;i++){

    for(int j = 0;j<5;j++){

        if (Cube[j]== i) tempSame++;
    }
    if (tempSame >same) same= tempSame;
    tempSame=0;
//////////////////////////////////////////////////////////////////////////////
}
return same;
}
int FullHouseCheck(){ //checks if it's FullHouse
    int same = 0, tempSame = 0, tempSame2=0;

for(int i = 1; i<=6;i++){//Zahlen

    for(int j = 0;j<5;j++){//Würfel

        if (Cube[j]== i) tempSame++;
    }
    if (tempSame >same){tempSame2= same; same = tempSame;}
    else if (tempSame>tempSame2)tempSame2= tempSame;
    tempSame=0;
//////////////////////////////////////////////////////////////////////////////
}
if(same+tempSame2==5)return 1;
return 0;
}
void FillTable(){ //here the user is able to tell the programm, where he writes something down
    wrong: //used goto :(
    printf("Wo eintragen? Zahl der Tabelle eingeben, \"0\" f%cr Streichen.\n", ue);
    int points= 0;//how many points to add
    int action=-1; //Which field to fill
    Clear();
        scanf("%d",&action);
if(action == 0||action ==12)//no check, later check
    {}
else if(action<1||action>13) goto wrong;//Wrong input
else if(Values[action-1][CurrentPlayer-1]!=0){ printf("Feld schon besetzt! \n"); goto wrong;} //field is already filled
    switch(action){
case 0:
    printf("Welches Feld wollen Sie streichen?");
    Clear();
        int feld=-1;
        if(scanf("%d",&feld)==0) goto wrong;
    if(feld<1|| feld>13){printf("Feld nicht verf%cgbar!.\n", ue); goto wrong;}
    else if(Values[feld-1][CurrentPlayer-1]==0){
        action=feld;
        points=-1;
    }
    else{
        printf("Kann nicht gestrichen werden.\n");
        goto wrong;
    }
    break;
case 1:
    if (Count(1)>0)points = Count(1);
    break;
case 2:
    if (Count(2)>0)points = Count(2);
    break;
case 3:
    if (Count(3)>0)points = Count(3);
    break;
case 4:
    if (Count(4)>0)points = Count(4);
    break;
case 5:
    if (Count(5)>0)points = Count(5);
    break;
case 6:
    if (Count(6)>0)points = Count(6);
    break;
case 7:
    if (CountSameValues()>=3) points = CountEverything();
    break;
case 8:
    if (CountSameValues()>=4) points = CountEverything();
    break;
case 9:
    if (FullHouseCheck()==1 )points = 25;
    break;
case 10:
    if ((Count(1)>=1&&Count(2)>=1&&Count(3)>=1&&Count(4)>=1)||
        (Count(2)>=1&&Count(3)>=1&&Count(4)>=1&&Count(5)>=1)||
        (Count(3)>=1&&Count(4)>=1&&Count(5)>=1&&Count(6)>=1))
        points=30;
    break;
case 11:
    if ((Count(1)>=1&&Count(2)>=1&&Count(3)>=1&&Count(4)>=1&&Count(5)>=1)||
        (Count(2)>=1&&Count(3)>=1&&Count(4)>=1&&Count(5)>=1&&Count(6)>=1)
        )points = 40;
    break;
case 12:
    if (CountSameValues()== 5){
        if(Values[action-1][CurrentPlayer-1]==0)points = 50;//1st
        else if(Values[action-1][CurrentPlayer-1]!=0&&Values[Cube[0]-1][CurrentPlayer-1]==0){ //for more then 1 Kniffel
            action=14;
            points = 50;
            Values[Cube[0]-1][CurrentPlayer-1]+=(Cube[0]*5);
        }
        else goto wrong;//next Kniffel not possible
    }
    break;
case 13:
    points = CountEverything();
    break;
default:
    printf("Fehler!\n");
    goto wrong;
    break;
    }
if(points==0){printf("Aktion nicht m%cglich!\n", oe);goto wrong;}
   Values[action-1][CurrentPlayer-1] = points;//Fill the table with the points to the current player
   Finish=1;//End players train --> next player
}
int Compare (const void * a, const void * b) { //compare function for the cubes
   int value1=*(int*)a;
   int value2=*(int*)b;
   return value1-value2;
}
// the random functions
void RandomNumberGenerator(int NumbersGenerate){ //generates random number
    int RandomNumber = 0;
    for (int i = 0; i < NumbersGenerate; i++)
    {
        RandomNumber = rand()%(6) + 1;
        Cube[i+CubesPutAway]= RandomNumber;
    }
}
void Generate(){//random number
    printf("\nSie haben mit %i W%crfel gew%crfelt!",5-CubesPutAway,ue,ue);
    RandomNumberGenerator(5-CubesPutAway);   // generate a Random number
    qsort(Cube, 5, sizeof(int), Compare);
    ShowCubes();
}
int IsEverythingFilledOut(){ //Checks the score table if it's full
for(int i=0;i<13;i++){
    if(Values[i][PlayerNumber-1]==0)
    return 0;
}
return 1;
}
void SelectCube(){ //here the user tells the programm, which cubes he want to reroll or not
    int tempWuerfel[5];
    CubesPutAway = 0;
    printf("\"J\" f%cr ja, \"N\" f%cr nein, \"E\" f%cr gleich eintragen(Sie k%cnnen dann nicht mehr weiterw%crfeln!)\n", ue, ue, ue, oe,ue);
    printf("und \"#\" f%cr alle W%crfel neu w%crfeln.\n",ue,ue,ue);
    printf("Bei Falscheingabe wird W%crfel nicht behalten!\n", ue);
    for(int i =1; i<= 5; i++){
        char ctemp;
        printf("%s, m%cchten Sie W%crfel %d behalten? ", Names[CurrentPlayer-1], oe, ue,i);
        Clear();
        scanf("%c", &ctemp);
        ctemp = toupper(ctemp);
        if(ctemp == 'J'){
            tempWuerfel[CubesPutAway] = Cube[i-1];          //Save it
            printf("W%crfel %d wird nicht neu gew%crfelt!\n",ue, i,ue);
            CubesPutAway++;
        }
        else if(ctemp == 'E'){
            FillTable();
            break;
        }
        else if(ctemp == '#'){
            CubesPutAway=0;
            break;
        }
        else{
            printf("W%crfel %d wird neu gew%crfelt!\n", ue, i,ue);
        }
    }
    memcpy(Cube, tempWuerfel,CubesPutAway*sizeof(int));
    if(CubesPutAway==5)FillTable();
}
void GameStructure(){//control structure for the game and playerchange
    CubesPutAway=0;
    printf("\nSpieler %s ist an der Reihe!\n\n", Names[CurrentPlayer-1]);
    if(ColorMode==1)ChangeColor(Colors[CurrentPlayer-1]);
    while(Throw<3 && Finish== 0){
            ShowScoreTable();
            Generate();
            if(Throw<2)SelectCube();
            Throw++;
          }
    if(Finish==0)FillTable();
          printf("Dein Spielstand:\n");
          ShowScoreTable();
    CurrentPlayer++;
    if(CurrentPlayer>PlayerNumber)CurrentPlayer=1;//Change player to 1 when everyone played
    Finish = 0;//for next player
    Throw =0;//for next player
    if(IsEverythingFilledOut()==1)GameOver();//Ends game when table is full
    else{GameStructure();}//Otherwise go on
}
void Initialize() { //initiallize array, player names
    printf("Tipp: bei Eingaben wird Gro%c/Kleinschreibung nicht beachtet.\n",ss);
    printf("Das \"-1\" in der Tabelle steht daf%cr, dass Sie dieses Feld gestrichen haben.\n",ue);
    printf("Geben Sie die Anzahl der Spieler ein (Begrenzt bis auf 1000): ");
    scanf("%d", &PlayerNumber);
    if (PlayerNumber<1||PlayerNumber>1000){ //Error if <1 .... Max 1000 players
        printf("Fehler. Spieleranzahl wurde automatisch auf 1 gesetzt\n");
            PlayerNumber=1;
        }

    printf("Anzahl der Spieler: %d\n", PlayerNumber);
    char playerName [PlayerNumber][30];

    char colorRead;
    Clear();
    printf("M%cchten Sie mit unterschiedlichen Farben Spielen? F%cr ja bitte \"J\" oder \"1\", der Rest Bedeutet nein: ", oe, ue);
    scanf(" %c", &colorRead);
    colorRead= toupper(colorRead);
    if(colorRead=='1'||colorRead=='J'){ColorMode=1;
    printf("Hier sind die Farben: Jeder Spieler soll sich eine heraussuchen und dann danach eingeben.\n");
    Colors = malloc((PlayerNumber+1) * sizeof(char*));//colors
    ShowColorsAvailible();}
    else{printf("Farbfunktion nicht aktiv.\n");}
    Names = malloc(PlayerNumber * sizeof(char*));//names
    for(int i = 0; i < PlayerNumber; i++) {//Names array
    Names[i] = malloc((12 + 1) * sizeof(char));}
    printf("Der Name des Spielers wird auf 13 Stellen abgek%crzt.\n", ue);
    Clear();
    for (int i = 0; i < PlayerNumber; i++) {
        printf("Geben Sie Spielername %d an: ",i+1);
        scanf(" %s", playerName[i]);
        strncpy(Names[i], playerName[i],13);//Only size of 13
        Names[i][13] = '\0'; //string has to end, set manually
        if(ColorMode==1){ //Only with ColorMode activated
                printf("Ihre Spielerfarbe bitte. Nur eine Zahl/Buchstabe: ");
                scanf(" %c", &Colors[i]);
                }
    }
    for(int i = 0; i < PlayerNumber; i++) {
        printf("Spieler %d hei%ct %s\n", i+1,ss, playerName[i]);

    }
    //Initalize score table
    Values =(int **) malloc(14*sizeof(int *));
    for(int i=0;i<14;i++) Values[i]=(int *) malloc(PlayerNumber*sizeof(int));
    for(int i = 0;i<14;i++){ //set to 0
        for(int j = 0; j<PlayerNumber; j++){
            Values[i][j] =0;
        }
    }

}

int main()//Program start
{
    printf("Willkommen zu Kniffel!\n");
    srand(time(NULL));
    //Program start
    Initialize();
    GameStructure();
    return 0;
}
