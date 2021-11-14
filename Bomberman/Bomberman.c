#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
*This function is used to return random values between the bounds
*which are given as a parameter
*/
int randomInt(int lower,int upper){
  int difference = upper - lower;
  int random = ( rand() % difference) + lower;
  return random;
}
/*
*This function is used to calculate the score of every explosion
*/
float calculateScore(float *score, float points){ //returns overall score
    *score += points;
    return *score;
}

/*
*This function is used to return random values between the bounds
*which are given as a
*/
float randomNum(int lower,int upper ,int neg){
    int repeat = 1;
    float decimal;
    while (repeat == 1){
        int difference = (upper - lower);
        float mod = (rand() & difference)+ lower; // using bitwise  to mask the random number
        decimal = (rand()/(float)RAND_MAX);
        decimal = decimal + mod;
        decimal = (int)(decimal *100);
        decimal = decimal/100;
        if (neg){
            decimal = -1 * decimal;
        }
        repeat = 0; // to make sure that its a nonzero number and less than 15 and greater than -15
        if( decimal == 0.00 ||decimal >15 ||decimal< -15 ){ 
            repeat = 1;
        }   
    }
  return decimal;
}

/*
*This function is used to initialize the backboard 
*with a random float and suprise packs
*/
void initializeBackboard(int row, int col, float fMatrix[row][col],int *negCount){
    int neg;// populating with random  positive and negative float 
    for(int iterRow = 0; iterRow < row; iterRow++){            
        for(int iterCol = 0; iterCol < col; iterCol++){
            if ((rand() & 4) == 4){
                neg = 1;  
            }else{
                neg = 0;
            }  
            fMatrix[iterRow][iterCol] = randomNum(0,15,neg);
            if(fMatrix[iterRow][iterCol] < 0){
                ++*negCount;
            }
        }
    }
    int total = row * col;
    int randRow;
    int randCol;
    int special = 0.2 *total;  // randomly scattering special packs 
    for (int iterSpecial = 0; iterSpecial < special; iterSpecial++){  
        randRow =randomInt(0,row);
        randCol=randomInt(0,col);
        int curSpecial =randomInt(60,63);
        float flSpecial = (float)curSpecial;
        //flSpecial = floor(100*flSpecial)/100;
        if(fMatrix[randRow][randCol]>15) iterSpecial--;
        if(fMatrix[randRow][randCol] < 0) --*negCount;
        fMatrix[randRow][randCol] = flSpecial; 
    }      
    
    //setting up exit and keeping the negCount consistant
    randRow =randomInt(0,row);
    randCol=randomInt(0,col);
    if(fMatrix[randRow][randCol] < 0) --*negCount; 
    fMatrix[randRow][randCol] = 69.00; //69 is exit

    // making sure there is atleast 40% negative numbers
    while (*negCount < 0.40*total ){
        neg = 1;
        randRow =randomInt(0,row);
        randCol=randomInt(0,col);
        if(fMatrix[randRow][randCol]<15 && fMatrix[randRow][randCol] > 0){ 
            fMatrix[randRow][randCol] = randomNum(0,15,neg);
            ++*negCount;
        }
    }
    // making sure there is atleast 40% negative numbers
    while (*negCount > 0.41*total ){ 
        neg = 0;
        randRow =randomInt(0,row);
        randCol=randomInt(0,col); 
        if(fMatrix[randRow][randCol]>-15 && fMatrix[randRow][randCol] < 0){  
            fMatrix[randRow][randCol] = randomNum(0,15,neg);
           --*negCount;
        }

    }  
     return;
}

/*
*This function fills the gameboard initially at the
*start of the game
*/
void fillGameboard (int rows, int cols, char cMatrix[rows][cols]){
    for (int iterRows = 0; iterRows < rows; iterRows++){
        for (int iterCol= 0; iterCol < cols; iterCol++){
            cMatrix[iterRows][iterCol] = 'x';
        }
    }
    return;
}

/*
*This function is used to display the backboard for TAs 
* to grade project easier.
*/
int displayBackboard (int rows, int cols, float fMatrix[rows][cols]){
    float current ;
    for (int iterRows = 0; iterRows < rows; iterRows++){
        for (int iterCol= 0; iterCol < cols; iterCol++){
            current = fMatrix[iterRows][iterCol] ;
            if (current == 69.00f){
                printf("   *   ");//displaying special characters
            }else if (current == 60.00f){ 
                printf("   $   ");
            }else if(current == 61.00){
                printf("   &   ");
            }else if(current == 62.00){
                printf("   #   ");
            }else{
                if(current > 0) printf(" ");
                if(current < 10 && current > 0) printf(" ");
                if(current > -10 && current < 0) printf(" "); 
                printf("%0.2f ", current);
            }   
        }
        printf("\n");
    }
}

/*
*This function is used to show that actual game board that the player uses to 
*play the game.
*/
int displayGame(int rows, int cols, char cMatrix[rows][cols]){
    for (int iterRows = 0; iterRows < rows; iterRows++){//iterating through the character matrix
        for (int iterCol= 0; iterCol < cols; iterCol++){
           printf("%c ", cMatrix[iterRows][iterCol]);
        }
        printf("\n");
    }

}

/*
*This function is used to check if the file exists and returns a 1 if it exists
*/
int fileExist(){
  FILE *txt;
  if(txt = fopen("Bomberman.log","r")){
    fclose(txt);
    return 1;
  }else return 0;
}

/*
*This function is used to log the score given into a log file 
*/
void logScore( const char *c, float score, int time){
    //if file doesnt exist then creates one
    if(fileExist() == 0 ){
        FILE *log = fopen("Bomberman.log", "w");
        fprintf(log,"%s %0.2f %d\n", c,score,time);
        fclose(log);
    }
    //if file exists the it appends to the document
    else{
        FILE *log = fopen("Bomberman.log","a");
            fprintf(log,"%s %0.2f %d\n", c, score,time);
            fclose(log);
    } 
   return;
}

/*
*This structure is used to hold the users data to display the top scores
*/
struct Bomberman{
    char player[50];
    float score;
    int time;
};

/*
*This function is used to count the amount of lines in the logfile
*/
int countLines()
{
    FILE *log = fopen("Bomberman.log", "r");
    char ch;
    int lines = 0;
    while(!feof(log))
    {
        ch = fgetc(log);
        if (ch == '\n')
        {
            ++lines;
        }
    }
    fclose(log);
    return lines;
}

/*
*This function displays the top scores in the log file
*/
void displayTopScores(int topScores){
    int lines = countLines();
    struct Bomberman scoreList[lines];
    FILE* log = fopen("Bomberman.log", "r"); // starting to read log file
    for(int i = 0; i < lines; ++i){
        fscanf(log, "%s %f %d", &scoreList[i].player, &scoreList[i].score, &scoreList[i].time); //putting the log file into array
    }
    float current;
    int scoreIndex;
    float largest;
    int playerSize;
    printf("\n\n");
    printf("                    <-<-<-<-<-<-<-<-<-LEADERBOARD->->->->->->->->->\n\n");
    printf("                     Name               Score              Time(s)   \n");
    printf("                     _____________________________________________   \n\n");
    for (int b = 0; b< topScores; b++ ){
        largest = -9999;
        for (int a = 0; a < lines; a++ ){ 
            current = scoreList[a].score;       //self made sorting algorithym to sort through the whole file of scores
            if (current > largest) {
                largest = current;
                scoreIndex = a ;
            }
        }
        printf("                     %s",scoreList[scoreIndex].player);
        if (scoreList[scoreIndex].score >= 0) printf(" ");
        for (playerSize = 0; scoreList[scoreIndex].player[playerSize] != '\0'; playerSize++);
    
        int space = 18;
        while((space - playerSize) > 0){// making the Scores aligned
            printf(" ");
            playerSize++;
        }
        printf("%0.2f", scoreList[scoreIndex].score);
        if(scoreList[scoreIndex].score >=0 ){ // making the player duration aligned
            if(scoreList[scoreIndex].score < 1000) printf(" ");
            if(scoreList[scoreIndex].score < 100) printf(" ");
            if(scoreList[scoreIndex].score < 10 ) printf(" ");
        } 
        if(scoreList[scoreIndex].score <0 ){
            if(scoreList[scoreIndex].score > -1000) printf(" ");
            if(scoreList[scoreIndex].score > -100) printf(" ");
            if(scoreList[scoreIndex].score > -10 ) printf(" ");
        }
        printf(" ");
        printf("              %d\n", scoreList[scoreIndex].time);
        scoreList[scoreIndex].score =-10000;
    }
    fclose(log);
}

/*
*This function handles the types of game exits and responds accordingly
*/
int exitgame(int num, int *lives,int rows,int columns, char cMatrix[rows][columns],float *score){
    if((num == 1 && *lives== 0)){ // exit game when no lives remain
        displayGame(rows,columns,cMatrix); 
        printf("You have no remaining lives left, YOU LOSE!\n");
        printf( "Your final score was %0.2f\n", *score);
        printf("The game will now exit, Your loss has been automatically added to the leaderboard!\n");
    }else if(num == 1 ){// exit game when chosing to leave
        printf("I see you have chosen to leave\n");
        printf( "Your final score was %0.2f\n", *score);
        printf("Have a great Day! The game will now exit, Your participation has been automatically added to the leaderboard!\n"); 
    }else if (num == 2){// exit game when win game
        if(*score < 0){
            *score = 0;
        }
        displayGame(rows,columns,cMatrix); 
        printf("YOU WIN!, your final score was %0.2f\n", *score);
        printf("You have been automatically added to the leaderboard!\n");
    }else if (num == 3){// exit gme when no bombs remain
        displayGame(rows,columns,cMatrix);
        printf("You have no remaining bombs left, YOU LOSE!\n");
        printf( "Your final score was %0.2f\n", *score);
        printf("The game will now exit, Your loss has been automatically added to the leaderboard!\n");
    }  
}

/*
*This is function is used for the main logic of the game, such as revealing the squares and adding up points
*/
float explode(int rows,int cols,char cMatrix[rows][cols],float fMatrix[rows][cols],int chooseRow,int chooseCol,int *bomb,int *multi,int *lives,int *hashcount,int* bombcount,int*win){
    if(chooseRow == -1 || chooseCol == -1) return 0.0;
    float current;
    float points = 0;
    char setval;
    int currRow;
    int currCol;
    int bombMulti =0;

    if (*multi>0){ 
        if(*multi>11){
            bombMulti = ((1+bombMulti)<<11)-1;
        }else{
        bombMulti = ((1+bombMulti)<<*multi)-1; // using bitwise  to do exponent calculations
        } 
        *multi = 0;
       
    }// uncovering the char matrix 
    for(int iterRow = -1 -bombMulti; iterRow < 2+bombMulti; iterRow++){
        for(int iterCol = -1 -bombMulti; iterCol < 2+bombMulti; iterCol++){
            currRow = chooseRow + iterRow;
            currCol = chooseCol + iterCol;
            if (currRow >= rows || currRow < 0|| currCol >= cols ||currCol < 0){
               continue; // if current row is out of bounds skip loop
           }
            current = fMatrix[currRow][currCol];
            fMatrix[currRow][currCol] = 0;
            if(current == 0){
                setval = cMatrix[currRow][currCol];
            }else if(current < 0){ 
                setval = '-';
                points = points + current;
            }else if (current > 0 && current < 15 ) {
                setval ='+';
                points = points + current;
            }else if (current == 60.00f){ 
                setval = '$';
                ++*multi;
            }else if(current == 61.00){
                setval = '&';
                ++*bombcount;//counting up the collection of &
                if(*bombcount == 10){
                    printf("You collected 10 Ampersands, have a bomb!\n");
                    ++*bomb;
                    *bombcount =0;
                }
            }else if (current == 62.00){
               setval = '#';
               ++*hashcount;//counting up the collection of #
               if (*hashcount == 10){    
                    ++*lives;
                    printf("Awesome you collected 10 Hashes, you gain an Extra life!\n");
                    *hashcount = 0;
               }
            }else if (current == 69.00) {
                setval ='*'; //setting exit tile
                *win = 2;    
            }
            cMatrix[currRow][currCol] = setval;
        }
    }
    bombMulti = 0;
    if(*multi > 0){ // printing $ statements
        printf("Bang!! you found %d $, your bomb range has ",*multi);
        if(*multi == 1){
            printf("Doubled!");
        }else if (*multi ==2){
            printf("Quadrupled!");
        }else if (*multi == 3){
            printf("Octupled!");
        }else{
            printf("has multiplied %d fold",1<<*multi);
        }
        printf("\n");
    }     
    printf("Total uncovered score of %0.2f points from current explosion\n", points);
    return points;
}

/*
*This function is used to help the displayTopScores() function with input validation 
*/
void requestScores(int end, int *quit){
    
    char temp;
    int repeat = 1;

    if (end == 0){
        while(repeat != 0){ 
            printf("\nWould you like to view the high scores?[y/n] (or 'q' to quit):");
            scanf("  %c", &temp);
            if(temp == 'y'){
                if(fileExist() == 1 ){
                    int lines = countLines();
                    int num;
                    printf("How many top scores would you like to see?");
                    scanf(" %d",&num); // taking in number to display top scores
                    while(num > lines || num < 0){
                        printf("\n The number provided was beyond the bounds of the entries in the log, try a number between [0,%d] ",lines);    
                        scanf(" %d",&num); 
                    }
                    displayTopScores(num);
                }else{
                        printf("\n\nThe score log file is nonexistant, therefore there is no database to pull from\n");
                        printf("please play an iteration of the game to create a file\n");
                }  
                return; 
            }else if (temp == 'n'){
                printf("Have a great Day!\n");
                return ;
            }else if (temp == 'q'){
                printf("you have chosen to quit, have a great day!\n");
                *quit = 1;
                return;
            }else{
                printf("\nThe character typed was not recognized as an option, please try again");
            }
        }

    }else{
            while(repeat != 0){ 
        printf("\nWould you like to view the high scores?[y/n]:");
        scanf("  %c", &temp);
        if(temp == 'y'){
            if(fileExist() == 1 ){
                int lines = countLines();
                int num;
                printf("How many top scores would you like to see?");
                scanf(" %d",&num); // taking in number to display top scores
                while(num > lines|| num < 0){
                    printf("\n The number provided was beyond the bounds of the entries in the log, try a number between [0,%d] ",lines);   
                    scanf(" %d",&num); 
                }
                displayTopScores(num);
            }else{
                printf("\n\nThe score log file is nonexistant, therefore there is no database to pull from\n");
                printf("please play an iteration of the game to create a file\n");
            }  
            return;  
        }else if (temp == 'n'){
            printf("Have a great Day!\n");
            return;
        }else{
            printf("\nThe character typed was not recognized as an option, please try again");
        }
    }
        
    }
}

/*
*This function is used to display the rules of the game
*/
void rules(){ 
    
printf("\n\n                                Welcome to Bomberman !\n"); // printing rules
printf("                  Here are some rules to help guide your gameplay:\n");
printf("   To play this game, please type the coordinate where you would like to place the bomb\n");
printf("             Here is an example of how to place coordinates\n");
printf("        x,y coordinate:4 5\n");
printf("  In this case the 4 represents the vertical coordinate, and the 5 represents the horizontal coordinate\n\n");
printf("                                        SYMBOLS\n");
printf("              __________________________________________________________\n");
printf("              $ -The next explosion will be doubled (they also stack)\n");
printf("              # - Collect 10 Hashes and get an Extra life!\n");
printf("              & - Collect 10 Ampersand to recieve an extra bomb \n");
printf("              * - Finally to win this game you need to find this symbol\n\n");
printf("             **IMPORTANT**: To exit the game please type \"-1 -1\" \n ");

}

/*
*This is the main function
*The game runs off of this function
*/
void main(int argc, char* argv[]){
   
    //validating commandline input
    if (argc != 4){
        printf("number of commandline arguements invalid, the program will now exit, 3 arguements are required"); 
        return;
    }
    int rows  =  atoi(argv[2]);
    int columns =  atoi(argv[3]);
    if(rows < 10){
        printf( "Error: The number of Rows must be atleast 10");
        return;
    }
    if(columns < 10){
        printf( "Error: The number of Columns must be atleast 10");
        return;
    }
    float score = 0;
    srand(time(0));
    int playtime = time(0);
    int lives = 3;
    int total = rows*columns;
    int bomb = (0.04*total);
    int pickRow =5;
    int pickColumn=5;
    int negcount = 0;
    int hashcount = 0;
    int bombcount = 0;
    float backBoard[rows][columns];
    int winCond = 0;
    char gameBoard[rows][columns];
    float points;
    int quit= 0;
    requestScores(winCond,&quit); //asking user if he wants to see the top scores
    if(quit == 1) return;
    rules();
    initializeBackboard(rows, columns, backBoard, &negcount);
    fillGameboard(rows, columns, gameBoard);
    printf("\n");    
    displayBackboard(rows,columns, backBoard);
    printf("\nTotal negative numbers %d/%d = %d%% ",negcount, total,( (int)(((float)negcount/total)*100) ));
    int multi =0;
    while(lives != 0 && winCond == 0 && bomb !=0){  
        
        printf("\n\n");
        displayGame(rows,columns,gameBoard);
        //creating the dashboard 
         printf("# Collected = %d\n",hashcount);
        printf("& Collected = %d\n",bombcount);
        printf("Bomb range:%d fold\n",1<<multi); //using bitwise to do calculations
        printf("Lives = %d\n", lives);
        printf("Bombs: %d\n",bomb);
        printf("Score = %0.2f\n",score);
        printf("x,y coordinate:");
        scanf(" %d%d", &pickRow,&pickColumn);
        while(pickRow<-1 ||pickRow >=rows || pickColumn<-1 || pickColumn>= columns){
            printf("please make sure your rows are between [0,%d] and your columns are between[0,%d]\n",rows-1,columns-1);
            printf("x,y coordinate:");
            scanf(" %d%d", &pickRow,&pickColumn);
        }
        if(pickColumn == -1 || pickRow == -1) winCond = 1;
        printf("\n");
        points = explode(rows,columns,gameBoard,backBoard,pickRow,pickColumn,&bomb,&multi,&lives,&hashcount,&bombcount,&winCond);
        calculateScore(&score,points);
        if(score < 0 && winCond == 0){
            lives--;
           printf("\nAWW shucks your score is %0.2f there goes a life, now your down to %d lives\n", score,lives);
            if (lives != 0){
            score = 0;
            }else{
                winCond= 1; 
            }
        }
      bomb--; 
      if(bomb == 0){
          winCond =3;
      }  
    }
    //exiting game and logging score and asking to see leaderboard
    exitgame(winCond,&lives,rows,columns,gameBoard,&score);
    playtime = time(0)- playtime;
    logScore(argv[1], score,playtime);
    printf("Your playtime was %d seconds",playtime);
    requestScores(winCond,&quit);
}


