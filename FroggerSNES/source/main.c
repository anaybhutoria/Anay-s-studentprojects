//FROGGER GAME MADE BY SUVRAT KUMRA(30089629) AND ANAY BHUTORIA (30066860)
//INCLUDING ALL THE HEADER FILES WHICH WILL BE REQUIRED IN THE CODE

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include "Base.h"
#include "frog.h"
#include "Car1.h"
#include<pthread.h>
#include "truck.h"
#include "truck2.h"
#include "car2.h"
#include "car3.h"
#include "actor1.h"
#include "actor2.h"
#include "actor3.h"
#include "actor4.h"
#include "actor5.h"
#include "actor6.h"
#include "actor7.h"
#include "actor8.h"
#include "Base2.h"
#include "log1.h"
#include "turtle1.h"
#include "turtle2.h"
#include "path1.h"
#include "start1.h"
#include "start2.h"
#include "pause1.h"
#include "pause2.h"
#include "pause3.h"
#include<time.h>
#include "winning.h"
#include "surprise.h"
#include "losing.h"
#include "0.h"
#include "1.h"
#include "2.h"
#include "3.h"
#include "4.h"
#include "5.h"
#include "6.h"
#include "7.h"
#include "8.h"
#include "9.h"
#include "score.h"
#include "timee.h"
#include "lives.h"
#include "moves.h"
#include "waterTile.h"
#include "blackTile.h"
#include "blueTile.h"



/* Definitions OF ALL THE STRUCTURES USED IN THE CODE*/
//TO DRAW THE IMAGE
typedef struct {
	short int color;
	int x, y;
} Pixel;

//FOR THE PLAYER, ALL THE ATTRIBUTES TO BE CONSIDERED, THE FROG IS ONLY INITIALIZED FOR THIS STRUCTURE
typedef struct {
	short int color;
	int xPos, yPos;
	int screenChange;
	int flag;		//this flag will be used so that when Start button is pressed the game pauses
	int tracker;    //used to differentiate btw the maps
	int surprise;   //surprise package
	int moves, lives, score, time;  //to keep the track of moves, lives, score and time
} Player;

//THIS WILL BE USED FOR ALL THE OBJECTS DEFINIED IN THE CODE
typedef struct {
	short int color; 
	int xPos, yPos;
} Objects;

//for the frog....
	Player frogObject;
//making the instance of all the objects used in the code for both map 1 and map2
	Objects truck3Object, truck4Object, car1Object, car2Object, car3Object, truck1Object, truck2Object, car4Object, car5Object, car6Object, car7Object, car8Object, truck5Object, truck6Object, car9Object, car10Object, car11Object;
	Objects actor1Object, actor2Object, actor3Object, actor4Object, actor5Object, actor6Object, actor7Object, actor8Object, actor9Object, actor10Object, actor11Object, actor12Object, actor13Object, actor14Object, actor15Object;
	Objects log1Object, log2Object, log3Object, log4Object, log5Object, turtle1Object, turtle2Object, turtle3Object, path1Object, path2Object, turtle4Object, turtle5Object, turtle6Object, turtle7Object, turtle8Object;
	Objects lastMap1Object, lastMap2Object, lastMap3Object, lastMap4Object, lastMap5Object, lastMap6Object;


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////READ SNES/////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////COPIED FROM THE PP1/////////////////////////////
#define LATCH 9
#define DATA 10
#define CLOCK 11

/*This function is used to set gpio pins to input
*/
 void INP_GPIO(unsigned int *GPIOaddr,int code){
 
 *(GPIOaddr + (code/10)) &= ~(7<<((code%10)*3)); //set gpio pin to input
}

/*This function is used to set gpio pins to out
*/
void OUT_GPIO(unsigned int *GPIOaddr,int code){

 *(GPIOaddr + (code/10)) |= (1<<((code%10)*3)); //set gpio pin to output
}

/* This function is used to make the program sleep for microseconds 
 */
void wait(int microseconds){ 
	delayMicroseconds(microseconds);
}

/*This function is used to initialize the pins 
*/
void init_GPIO(unsigned int *GPIOaddr, int flag, int code){
	if(flag == 1){ //if flag is 1 then set pin to output
		INP_GPIO(GPIOaddr,code);
		OUT_GPIO(GPIOaddr,code);
	}else{						//if flag is 0 then set pin to all zeros for input
		INP_GPIO(GPIOaddr,code);
	}
}
/*This function is used to write to the latch gpio pin
*/
void Write_Latch(unsigned int *GPIOaddr, int flag){
	if(flag == 1){ //if flag is set to 1 then write 1 to the latch pin
		GPIOaddr[7] = 1<<LATCH;
	}else if(flag == 0){//if flag is set to 0 then write 0 to the latch pin
		GPIOaddr[10] = 1<<LATCH;
	}
}


/*This function is used to write to the clock gpio pin
*/
void Write_Clock(unsigned int *GPIOaddr, int flag){
	if(flag == 1){ // if flag is 1 set clock gpio pin to 0
		GPIOaddr[7] = 1<<CLOCK;
	}else if(flag == 0){ // if flag is 0 set clock gpio pin to 0 
		GPIOaddr[10] = 1<<CLOCK;
	}
}

/* This function is used to read input from the data pin  
 */
int Read_Data(int forReading){
	int v = (forReading >> DATA) & 1;		
	return v;
}

/* This function is used to read inputs from the SNES controller
*/
int Read_SNES(unsigned int *GPIOaddr){	
	int button;
	int variable;
	init_GPIO(GPIOaddr, 1, CLOCK); //initializing the pins
	init_GPIO(GPIOaddr, 1, LATCH);
	init_GPIO(GPIOaddr, 0, DATA);
	Write_Clock(GPIOaddr, 1);
	Write_Latch(GPIOaddr, 1);
	wait(12);
	Write_Latch(GPIOaddr, 0);
	for(int i = 1; i<=16; i++){ //looping through all the buttons to see if button was pressed
		wait(6);
		Write_Clock(GPIOaddr, 0);
		wait(6);
		button = Read_Data(GPIOaddr[13]);
		if(button == 0){
			variable = i;
			goto next;
		}
		Write_Clock(GPIOaddr, 1);
	}
	next:
	return variable;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////DEFINING ALL THE FUNCTIONS WHICH ARE USED LATER IN THE CODE////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);
void drawPlayer(Player *player);
void *readingSnes(void *ID);
int threadReadingSnes();
void startingMap();
void* playingMapOne(void *invokedPlayer);
int displayMapOne();
void displayingMovingTruck();
void displayingMovingCar1();
void displayingMovingActor();
int displayMapTwo();
void displayingMovingLog();
void displayFrog();
void displayingMovingTurtles();
void displayingMovingPath();
void displayLastMap();

//THIS FUNCTION IS USED TO REPLACE THE PREVIOUS TILE MOVED BY THE FROG, THIS IS DONE IN ORDER TO AVOID FLICKERING OF THE OBJECT
void replacingTile(int previousX, int previousY, int button){
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	int i=0;
	short int *blueTilePtr=(short int *) BlueTile.pixel_data;
	short int *blackTilePtr=(short int *) BlackTile.pixel_data;

//IF the frog is at first screen then do all this method, cuz only blue and black type of tiles are there,
	if(button == 5){
	if(frogObject.screenChange == 0){		//When the starting screen is displayed
		if(frogObject.yPos == 624 || frogObject.yPos == 336){
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blueTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
		i=0;
		if((frogObject.yPos<624 && frogObject.yPos>=372) || (frogObject.yPos<336 && frogObject.yPos>36))
		{
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36is image width
				{	
					pixel->color = blackTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
	}
		
	else if(frogObject.tracker == 1){//For the watermap
		if(frogObject.yPos == 336){
			for (int y = previousY; y < previousY + 36; y++)//36is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blueTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
		i=0;
		if(frogObject.yPos < 336)
		{
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blackTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
	}
	}
	if(button == 6){
	if(frogObject.screenChange == 0){
		if(frogObject.yPos == 408 || frogObject.yPos == 120){
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blueTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
		i=0;
		if(frogObject.yPos == 660 || (frogObject.yPos<=624 && frogObject.yPos>=372 && frogObject.yPos != 408) || (frogObject.yPos<336 && frogObject.yPos>36 && frogObject.yPos!=120))
		{
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blackTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
	}
	else if(frogObject.tracker == 1){//For the watermap
		i=0;
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blackTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		
	}
	}
	//When the frog will move left or right, so there will be other conditions to take care of, cannot do in the same defined above
	if(button == 7 || button == 8){
	if(frogObject.screenChange == 0){
		//printf("\nFrog y : %d", frogObject.yPos);
		if(frogObject.yPos == 660 || frogObject.yPos == 372 || frogObject.yPos == 84){
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blueTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
		i=0;
		if((frogObject.yPos<=624 && frogObject.yPos>372) || (frogObject.yPos<=336 && frogObject.yPos>36 && frogObject.yPos!=84))
		{
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blackTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
	}
	else if(frogObject.tracker == 1){//For the watermap
		i=0;
		if(frogObject.yPos == 372){
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blueTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
		else{
			for (int y = previousY; y < previousY + 36; y++)//36 is the image height
			{
				for (int x = previousX; x < previousX+36; x++) // 36 is image width
				{	
					pixel->color = blackTilePtr[i]; 
					pixel->x = x;
					pixel->y = y;
		
					drawPixel(pixel);
					i++;
					
				}
			}
		}
	}
	}
}


//DISPLAYING THE LIVES OF THE FROG BY CREATING THE .H FILE OF EVERY NUMBER AND THEN IMPLEMENTING IT NECESSARILY JUST BY ALLOCATING THE POSITION AND THEN
//USING THE DRAWPIXEL FUNCTION TO DRAW IT. SIMPLE STUFF
void displayLives(){
	short int *livesPtr=(short int *) Lives.pixel_data;
	short int *zeroPtr=(short int *) Zero.pixel_data;
	short int *onePtr=(short int *) One.pixel_data;
	short int *twoPtr=(short int *) Two.pixel_data;
	short int *threePtr=(short int *) Three.pixel_data;
	short int *fourPtr=(short int *) Four.pixel_data;
	int onesPlace;
	
		Pixel *pixel;
		pixel = malloc(sizeof(Pixel));
		int i=0;

		for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 2; x < 107; x++) // 105 is image width
			{	
				pixel->color = livesPtr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}

	onesPlace = frogObject.lives;
	i=0;
	
	if(onesPlace == 4){
		for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 108; x < 133; x++) // 25 is image width
			{	
				pixel->color = fourPtr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}
	}

	if(onesPlace == 3){
		for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 108; x < 133; x++) // 25 is image width
			{	
				pixel->color = threePtr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}
	}

	if(onesPlace == 2){
		for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 108; x < 133; x++) // 25 is image width
			{	
				pixel->color = twoPtr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}
	}

	if(onesPlace == 1){
		for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 108; x < 133; x++) // 25 is image width
			{	
				pixel->color = onePtr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}
	}

	if(onesPlace == 0){
		for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 108; x < 133; x++) // 25 is image width
			{	
				pixel->color = zeroPtr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}
	}
}


//DISPLAYING THE MOVES and TIME OF THE FROG BY CREATING THE .H FILE OF EVERY NUMBER AND THEN IMPLEMENTING IT NECESSARILY JUST BY ALLOCATING THE POSITION AND THEN
//USING THE DRAWPIXEL FUNCTION TO DRAW IT. SIMPLE STUFF
void displayMoves(){
	short int *movesPtr=(short int *) Moves.pixel_data;
	short int *timePtr=(short int *) Timee.pixel_data;
	short int *scorePtr=(short int *) Score.pixel_data;
	short int *zeroPtr=(short int *) Zero.pixel_data;
	short int *onePtr=(short int *) One.pixel_data;
	short int *twoPtr=(short int *) Two.pixel_data;
	short int *threePtr=(short int *) Three.pixel_data;
	short int *fourPtr=(short int *) Four.pixel_data;
	short int *fivePtr=(short int *) Five.pixel_data;
	short int *sixPtr=(short int *) Six.pixel_data;
	short int *sevenPtr=(short int *) Seven.pixel_data;
	short int *eightPtr=(short int *) Eight.pixel_data;
	short int *ninePtr=(short int *) Nine.pixel_data;
	int hundredthPlace, tenthPlace, onesPlace, ThundredthPlace, TtenthPlace, TonesPlace;
	int i = 0;
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));

	//Displaying the text "Moves"
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 200; x < 320; x++) // 120 is image width
		{	
			pixel->color = movesPtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}
	i=0;
	//DISPLAYING THE TEXT "TIME"
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 455; x < 544; x++) // 89 is image width
		{	
			pixel->color = timePtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}

	i=0;
	//DISPLAYING THE TEXT "Score"
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 765; x < 870; x++) // 105 is image width
		{	
			pixel->color = scorePtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}

	//TO calculate the score 
	int hundredScore = frogObject.score/100;
	int tensScore = frogObject.score/10;
	int onesScore = frogObject.score%10;

	// storing the hundred value digit in the ThundredthPlace variable
	ThundredthPlace = frogObject.time/100;
	if(ThundredthPlace == 0)
		TtenthPlace = frogObject.time/10;
	else{
		int n = frogObject.time/10;
		TtenthPlace = n%10;
	}
	TonesPlace = frogObject.time%10;

	// storing the hundred value digit in the ThundredthPlace variable	
	hundredthPlace = frogObject.moves/100;
	tenthPlace = frogObject.moves/10;
	onesPlace = frogObject.moves%10;


//for the score
	if(hundredScore == 0){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 874; x < 899; x++) // 25 is image width
		{	
			pixel->color = zeroPtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}}
	if(hundredScore == 1){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 874; x < 899; x++) // 25 is image width
		{	
			pixel->color = onePtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}}

	
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 899; x < 924; x++) // 25 is image width
		{	
			pixel->color = zeroPtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}
	
	if(onesScore == 0){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 924; x < 949; x++) // 25 is image width
		{	
			pixel->color = zeroPtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}}



	i=0;
	
	// then compare to see what that ThundredthPlace value is
	if(hundredthPlace == 1){
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 325; x < 350; x++) // 25 is image width
		{	
			pixel->color = onePtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}
	}
	// then compare to see what that ThundredthPlace value is
	if(hundredthPlace == 0){	
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 325; x < 350; x++) // 25 is image width
			{	
				pixel->color = zeroPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that tenthPlace value is
	if(tenthPlace == 0 || tenthPlace == 10){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = zeroPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}
	
	// then compare to see what that tenthPlace value is
	if(tenthPlace == 1){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = onePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that tenthPlace value is
	if(tenthPlace == 2){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = twoPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that tenthPlace value is
	if(tenthPlace == 3){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = threePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that tenthPlace value is
	if(tenthPlace == 4){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = fourPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that tenthPlace value is
	if(tenthPlace == 5){
	i=0;	
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = fivePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that tenthPlace value is
	if(tenthPlace == 6){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = sixPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that tenthPlace value is
	if(tenthPlace == 7){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = sevenPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}
	
	// then compare to see what that tenthPlace value is
	if(tenthPlace == 8){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = eightPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that tenthPlace value is

	if(tenthPlace == 9){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 353; x < 378; x++) // 25 is image width
			{	
				pixel->color = ninePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that onesPlace value is
	if(onesPlace== 0 || onesPlace== 10){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width
			{	
				pixel->color = zeroPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}
	
	// then compare to see what that onesPlace value is
	if(onesPlace== 1){
	i=0;	
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width
			{	
				pixel->color = onePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that onesPlace value is

	if(onesPlace== 2){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width

			{	
				pixel->color = twoPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that onesPlace value is
	if(onesPlace== 3){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width

			{	
				pixel->color = threePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that onesPlace value is
	if(onesPlace== 4){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width

			{	
				pixel->color = fourPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that onesPlace value is
	if(onesPlace== 5){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width

			{	
				pixel->color = fivePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}
	
	// then compare to see what that onesPlace value is
	if(onesPlace== 6){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width

			{	
				pixel->color = sixPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that onesPlace value is
	if(onesPlace== 7){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width
			{	
				pixel->color = sevenPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that onesPlace value is
	if(onesPlace== 8){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width

			{	
				pixel->color = eightPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that onesPlace value is
	if(onesPlace == 9){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 381; x < 406; x++) // 25 is image width

			{	
				pixel->color = ninePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	i=0;
	// then compare to see what that ThundredthPlace value is
	if(ThundredthPlace == 2){
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 543; x < 568; x++) // 25 is image width
		{	
			pixel->color = twoPtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}
	}


	i=0;
	// then compare to see what that ThundredthPlace value is
	if(ThundredthPlace == 1){
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
	{
		for (int x = 543; x < 568; x++) // 25 is image width
		{	
			pixel->color = onePtr[i]; 
			pixel->x = x;
			pixel->y = y;
	
			drawPixel(pixel);
			i++;
				
		}
	}
	}
	// then compare to see what that ThundredthPlace value is
	if(ThundredthPlace == 0){	
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 543; x < 568; x++) // 25 is image width
			{	
				pixel->color = zeroPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 0 || TtenthPlace == 10){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = zeroPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}
	
	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 1){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = onePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 2){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = twoPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 3){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
		for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = threePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is

	if(TtenthPlace == 4){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = fourPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 5){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = fivePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 6){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = sixPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 7){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = sevenPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 8){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = eightPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TtenthPlace value is
	if(TtenthPlace == 9){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 570; x < 595; x++) // 25 is image width
			{	
				pixel->color = ninePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is
	if(TonesPlace == 0 || TonesPlace == 10){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width
			{	
				pixel->color = zeroPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is
	if(TonesPlace== 1){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width
			{	
				pixel->color = onePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is
	if(TonesPlace == 2){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width

			{	
				pixel->color = twoPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is
	if(TonesPlace == 3){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width

			{	
				pixel->color = threePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}
	
	// then compare to see what that TonesPlace value is
	if(TonesPlace == 4){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width

			{	
				pixel->color = fourPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is
	if(TonesPlace == 5){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width


			{	
				pixel->color = fivePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is

	if(TonesPlace == 6){
	int i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width

			{	
				pixel->color = sixPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is
	if(TonesPlace == 7){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width

			{	
				pixel->color = sevenPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is
	if(TonesPlace == 8){
	i=0;
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width


			{	
				pixel->color = eightPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}

	// then compare to see what that TonesPlace value is
	if(TonesPlace == 9){
	i=0;
	
	// draw the number on the screen
	for (int y = 700; y < 725; y++)//25 is the image height
		{
			for (int x = 599; x < 624; x++) // 25 is image width

			{	
				pixel->color = ninePtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
			}
		}
	}


}

void displayingBackground2(){
		short int *base2Ptr=(short int *) base2.pixel_data;

		Pixel *pixel;
		pixel = malloc(sizeof(Pixel));
		int i=0;

		for (int y = 0; y < 768; y++)//768 is the image height
		{
			for (int x = 0; x < 1024; x++) // 1024 is image width
			{	
				pixel->color = base2Ptr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}
}

void displayLosingScreen(){
	short int *basePtr=(short int *) Losing.pixel_data;

		Pixel *pixel;
		pixel = malloc(sizeof(Pixel));
		int i=0;

		for (int y = 0; y < 768; y++)//768 is the image height
		{
			for (int x = 0; x < 1024; x++) // 1024 is image width
			{	
				pixel->color = basePtr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}

}

void displayingBackground(){
/* initialize a pixel */
	
	if(frogObject.screenChange == 0){
		short int *basePtr=(short int *) base.pixel_data;

		Pixel *pixel;
		pixel = malloc(sizeof(Pixel));
		int i=0;

		for (int y = 0; y < 768; y++)//768 is the image height
		{
			for (int x = 0; x < 1024; x++) // 1024 is image width
			{	
				pixel->color = basePtr[i]; 
				pixel->x = x;
				pixel->y = y;
		
				drawPixel(pixel);
				i++;
					
			}
		}
	}
				
}


/* This is the function that will take care of the pause feature of the game */
void displayingPauseMenu(){
	/* initialize a pixel */		
	frogObject.screenChange = 5;

	// if the screen change of frog object is equal to 5
	first:
	if(frogObject.screenChange  == 5){
		short int *pause1Ptr = (short int *) Pause1.pixel_data;
		Pixel *pixel1;
		pixel1 = malloc (sizeof(Pixel));
		int i= 0;
		for (int y = 0; y < 768; y++)//768 is the image height
		{
			for (int x = 0; x < 1024; x++) // 1024 is image width
			{	
				pixel1->color = pause1Ptr[i]; 
				pixel1->x = x;
				pixel1->y = y;
		
				drawPixel(pixel1);
				i++;
					
			}
		}
	}
	
	// if the screen change of frog object is equal to 10
	third:
	if(frogObject.screenChange == 10){
		//printf("\nIn third");
		short int *pause2Ptr = (short int *) Pause2.pixel_data;
		Pixel *pixel2;
		pixel2 = malloc (sizeof(Pixel));
		int i= 0;
		for (int y = 0; y < 768; y++)//768 is the image height
		{
			for (int x = 0; x < 1024; x++) // 1024 is image width
			{	
				pixel2->color = pause2Ptr[i]; 
				pixel2->x = x;
				pixel2->y = y;
		
				drawPixel(pixel2);
				i++;
					
			}
		}
	}

	
	int pressed;
	again:
	pressed = threadReadingSnes();	
	//printf("\n\npressed: %d", pressed);
	// if the screen change of frog object is equal to 5
	if(frogObject.screenChange == 5){
		// is user pressed 9
		if(pressed == 9){	
			if(frogObject.tracker == 0)
				displayingBackground();
			else if(frogObject.tracker == 1)
				//printf("in the if");
				displayingBackground2();
			frogObject.screenChange = 8;
			
		}
		// or else if user pressed 6 or 5
		else if(pressed == 6 || pressed == 5){
			frogObject.screenChange = 10;
			goto third;
		}
		else{
			goto again;
		}
	}
	
	// if the screen change of frog object is equal to 10	
	again3:
	if(frogObject.screenChange == 10){
		// if user pressed 9
		if(pressed == 9){
			exit(0);
		}
		// or if the user pressed 5 or 6
		else if(pressed == 5 || pressed == 6){
			frogObject.screenChange = 5;
			goto first;
		}
		else{
			goto again;
		}
	}
	return 0;
}


/* This function will implement all the surpise packs used in this game */
/* @Param: randomGenX, randomGenY, randomSurprise, which will be used to generate random x and y numbers */
void displayingSurprise(int randomGenX, int randomGenY, int randomSurprise){
	if(frogObject.surprise = 1){
		
		short int *surprise1Ptr = (short int *) Surprise.pixel_data;
		Pixel *pixel2;
		pixel2 = malloc (sizeof(Pixel));
		int i= 0;
		for (int y = randomGenY; y < randomGenY+36; y++)//36 is the image height
		{
			for (int x = randomGenX; x < randomGenX+36; x++) //36 is image width
			{	
				pixel2->color = surprise1Ptr[i]; 
				pixel2->x = x;
				pixel2->y = y;
		
				drawPixel(pixel2);
				i++;
					
			}
		}
		//THIS WILL INCREASE THE MOVES FROG HAS BY 10
		if(randomSurprise == 1 || randomSurprise == 2){
			//printf("moves");
			if(frogObject.yPos >= randomGenY-15 && frogObject.yPos <= randomGenY+36){
				if(frogObject.xPos >= randomGenX-15 && frogObject.xPos <= randomGenX+50){
					frogObject.surprise = 0;
					frogObject.moves+=10;
				}
			}
		}

		//THIS WILL INCREASE THE SCORE OF FROG HAS BY 100
		else if(randomSurprise == 3 || randomSurprise == 4 || randomSurprise == 0){
			//printf("score");
			if(frogObject.yPos >= randomGenY-15 && frogObject.yPos <= randomGenY+36){
				if(frogObject.xPos >= randomGenX-15 && frogObject.xPos <= randomGenX+50){
					frogObject.surprise = 0;
					frogObject.score+=100;
				}
			}
		}
	
		//THIS WILL INCREASE THE LIFE OF FROG HAS BY 1
		else if(randomSurprise == 5){
			//printf("life");
			if(frogObject.yPos >= randomGenY-15 && frogObject.yPos <= randomGenY+36){
				if(frogObject.xPos >= randomGenX-15 && frogObject.xPos <= randomGenX+50){
					frogObject.surprise = 0;
					frogObject.lives+=1;
				}
			}
		}

	}


}

/* This function will display the start menu of the game */
void displayingStartMenu(){
	/* initialize a pixel */	

	// if the screenchange is equal to 2	
	first:
	if(frogObject.screenChange  == 2){

		// initializing
		short int *menu1Ptr = (short int *) Start1.pixel_data;
		Pixel *pixel2;
		pixel2 = malloc (sizeof(Pixel));
		int i= 0;
		
		// display the start screen 
		for (int y = 0; y < 768; y++)//768 is the image height
		{
			for (int x = 0; x < 1024; x++) // 1024 is image width
			{	
				pixel2->color = menu1Ptr[i]; 
				pixel2->x = x;
				pixel2->y = y;
		
				drawPixel(pixel2);
				i++;
					
			}
		}
	}

	// if the screenchange is equal to 3
	second:
	if(frogObject.screenChange == 3){
		//printf("\nIn second");

		// initialzing
		short int *menu2Ptr = (short int *) Start2.pixel_data;
		Pixel *pixel3;
		pixel3 = malloc (sizeof(Pixel));
		int i= 0;

		// display the screen 
		for (int y = 0; y < 768; y++)//768 is the image height
		{
			for (int x = 0; x < 1024; x++) // 1024 is image width
			{	
				pixel3->color = menu2Ptr[i]; 
				pixel3->x = x;
				pixel3->y = y;
		
				drawPixel(pixel3);
				i++;
					
			}
		}
	}
	
	int pressed;
	again:
	pressed = threadReadingSnes();	
	//printf("\n\npressed: %d", pressed);

	// check if screen change equals to 2
	if(frogObject.screenChange == 2){

		// if user pressed 9
		if(pressed == 9){
			frogObject.screenChange = 0;
		}
		// if user pressed 6 or 5
		else if(pressed == 6 || pressed == 5){
			frogObject.screenChange = 3;
			goto second;
		}
		else{
			goto again;
		}
	}

	// check if screen change equals to 3
	if(frogObject.screenChange == 3){

		// if user pressed 9
		if(pressed == 9){
			exit(0);
		}
		// or else if they pressed 5 or 6
		else if(pressed == 5 || pressed == 6){
			frogObject.screenChange = 2;
			goto first;
		}
	}

}


/* This function will display the win screen upon winning the game */
void displayWinScreen(){
/* initialize a pixel */		
		short int *win1Ptr = (short int *) Winning.pixel_data;
		Pixel *pixel1;
		pixel1 = malloc (sizeof(Pixel));
		int i= 0;
		// display the winning screen to the screen 
		for (int y = 0; y < 768; y++)//768 is the image height
		{
			for (int x = 0; x < 1024; x++) // 1024 is image width
			{	
				pixel1->color = win1Ptr[i]; 
				pixel1->x = x;
				pixel1->y = y;
		
				drawPixel(pixel1);
				i++;
					
			}
		}


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////MAIN FUNCTION///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
	frogObject.lives = 4;
	frogObject.moves = 100;
	frogObject.score = 0;

	frogObject.screenChange = 2;

	/* initialize + get FBS */
	framebufferstruct = initFbInfo();


//MAKING THE FOUR MAPS AND INVOKING THEIR METHOD OVER HERE.
	
	do{
		displayingStartMenu();
		//printf("\n value: %d", frogObject.screenChange); 
	}while(frogObject.screenChange!=0);
	startingMap();
	return 0;
}

/* This function is the function that intializes all the maps */
/* It also initializes all the objects for each map as well */

void startingMap(){

	time_t begin = time(NULL);

	displayingBackground();

	//INITIAL LOCATION OF THE CAR
	car1Object.yPos = 623;
	car1Object.xPos = 0;

	car3Object.yPos = 623;
	car3Object.xPos = 700;

	truck1Object.yPos = 587;
	truck1Object.xPos = 100;
	
	truck2Object.yPos = 587;
	truck2Object.xPos = 600;
	
	car4Object.yPos = 552;
	car4Object.xPos = 1024;

	car5Object.yPos = 552;
	car5Object.xPos = 666; 

	car6Object.yPos = 516;
	car6Object.xPos = 100;
	
	car7Object.yPos = 516;
	car7Object.xPos = 400;

	car8Object.yPos = 516;
	car8Object.xPos = 700;

	truck4Object.yPos = 480;
	truck4Object.xPos = 400;

	truck5Object.yPos = 445;
	truck5Object.xPos = 300;

	truck6Object.yPos = 445;
	truck6Object.xPos = 700;

	car9Object.yPos = 410;
	car9Object.xPos = 900;

	car10Object.yPos = 410;
	car10Object.xPos = 600;

	car11Object.yPos = 410;
	car11Object.xPos = 300;

	actor1Object.yPos = 337;	
	actor1Object.xPos = 0;

	actor2Object.yPos = 337;	
	actor2Object.xPos = 300;
	
	actor3Object.yPos = 337;	
	actor3Object.xPos = 700;

	actor4Object.yPos = 301;	
	actor4Object.xPos = 0;
	
	actor5Object.yPos = 301;	
	actor5Object.xPos = 512;

	actor6Object.yPos = 265;	
	actor6Object.xPos = 900;

	actor7Object.yPos = 229;	
	actor7Object.xPos = 900;

	actor8Object.yPos = 229;	
	actor8Object.xPos = 400;

	actor9Object.yPos = 193;	
	actor9Object.xPos = 300;

	actor10Object.yPos = 193;
	actor10Object.xPos = 800;

	actor11Object.yPos = 157;	
	actor11Object.xPos = 1023;

	actor12Object.yPos = 157;
	actor12Object.xPos = 700;
	
	actor13Object.yPos = 157;	
	actor13Object.xPos = 350;

	actor14Object.yPos = 120;
	actor14Object.xPos = 250;

	actor15Object.yPos = 120;	
	actor15Object.xPos = 750;

	log1Object.yPos = 623;
	log1Object.xPos = 0;

	log2Object.yPos = 623;
	log2Object.xPos = 512;

	turtle1Object.yPos = 587;
	turtle1Object.xPos = 1023;

	turtle2Object.yPos = 587;
	turtle2Object.xPos = 250;

	turtle3Object.yPos = 587;
	turtle3Object.xPos = 600;
	
	path1Object.yPos = 552;
	path1Object.xPos = 160;
	
	path2Object.yPos = 552;
	path2Object.xPos = 720;

	turtle4Object.yPos = 516;
	turtle4Object.xPos = 890;

	turtle5Object.yPos = 516;
	turtle5Object.xPos = 320;

	turtle6Object.yPos = 480;
	turtle6Object.xPos = 1023;

	turtle7Object.yPos = 480;
	turtle7Object.xPos = 721;

	turtle8Object.yPos = 480;
	turtle8Object.xPos = 233;

	log3Object.yPos = 444;
	log3Object.xPos = 400;

	log4Object.yPos = 408;
	log4Object.xPos = 720;

	log5Object.yPos = 408;
	log5Object.xPos = 40;

	car1Object.yPos = 623;
	car1Object.xPos = 0;

	car3Object.yPos = 623;
	car3Object.xPos = 700;

	truck1Object.yPos = 587;
	truck1Object.xPos = 100;
	
	truck2Object.yPos = 587;
	truck2Object.xPos = 600;
	
	lastMap1Object.yPos = 337;
	lastMap1Object.xPos = 1024;

	lastMap2Object.yPos = 301;
	lastMap2Object.xPos = 666; 

	lastMap3Object.yPos = 301;
	lastMap3Object.xPos = 100;
	
	lastMap4Object.yPos = 265;
	lastMap4Object.xPos = 400;

	lastMap5Object.yPos = 265;
	lastMap5Object.xPos = 700;

	lastMap6Object.yPos = 229;
	lastMap6Object.xPos = 400;
		
	srand(time(0));

	// generating few random numbers
	int randomGenX = rand() % 899 ;
	int randomGenY = (rand()%400) + 40;
	int randomSurprise = rand()%5;
	//printf("%d", randomSurprise);

	time_t middle, currentTime;
	int middleTime;

	// initializing few locations and variables
	frogObject.yPos = 660;
	frogObject.xPos = 500;
	frogObject.flag = 0;
	frogObject.screenChange = 0;

	// making a pthread for frogs
	pthread_t frog;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&frog, &attr, playingMapOne, "0");
	int flag=0;
	while(frogObject.lives >=1){
	
	frogObject.surprise = 1;
	int tracking;
	next:

	// if the screenchange of the frog object is equal to 0
	if(frogObject.screenChange == 0){
		frogObject.tracker = 0;
		while(frogObject.yPos!=48 && frogObject.flag == 0  && frogObject.screenChange!=5){
			currentTime = time(NULL);
			displayLives();
			displayMoves();
			frogObject.time = currentTime-begin;					//keeping track of the time elapsed
			middle  = time(NULL);
			middleTime = middle - begin;
			if(middleTime >=randomSurprise+32 && middleTime <= randomSurprise+52 && frogObject.surprise == 1){
 				displayingSurprise(randomGenX, randomGenY, randomSurprise);
			}	
			displayMapOne();
			displayingMovingCar1();
			displayingMovingTruck();
			displayingMovingActor();
		}	
		if(frogObject.yPos == 48)
			flag = 1;
		if(frogObject.flag == 1){
			goto finish;
		}
		
	}
	// check if flag is equal to 0
	if(flag == 0)
		goto next;
	
	frogObject.tracker = 1;
	frogObject.yPos = 660;
	frogObject.screenChange = 1;

	flag = 0;

	// display the background 2
	displayingBackground2();
	next2:
	
	// if the tracker of the frog object is equal to 1
	if(frogObject.tracker == 1){
		while(frogObject.yPos>=194 && frogObject.flag == 0 && frogObject.screenChange!=5){
			currentTime = time(NULL);
			displayLives();
			displayMoves();
			frogObject.time = currentTime-begin;					//keeping track of the time elapsed
			middle  = time(NULL);
			middleTime = middle - begin;
			if(middleTime >= randomSurprise+32 && middleTime <= randomSurprise+52 && frogObject.surprise == 1){
 				displayingSurprise(randomGenX, randomGenY, randomSurprise);
			}	
			// call few functions to implement the features of the game
			displayMapTwo();
			displayLastMap();
			displayingMovingPath();
			displayingMovingTurtles();
			displayingMovingLog();
		}
		if(frogObject.yPos<=194){
			displayWinScreen();
			int button = threadReadingSnes();
			time_t end = time(NULL);
			int timeTaken = end-begin;

			//printf("\nMoves Left: %d", frogObject.moves);
			//printf("\nTime Taken: %d", timeTaken);

		pthread_cancel(frog);
		goto end;
	}
	if(frogObject.flag==1)
		goto finish;
	}
	goto next2;
	
	// print out the number of lives left
	finish:
	printf("");

	}
	
	// call the displayLosingScreen function to display the losing screen; game over
	displayLosingScreen();

	// calculate the time and print it
	time_t end = time(NULL);
	int timeTaken = end-begin;
	//printf("\nMoves Left: %d", frogObject.moves);
	//printf("\nTime Taken: %d", timeTaken);

	// cancel the pthread for the frog
	pthread_cancel(frog);
	end:
	printf("");

	
}

/* This function will be displaying the moving path */
void displayingMovingPath(){

	//initializing useful variables
	Objects *path1;
	path1 = malloc(sizeof(path1));
	int i = 0;
	
	short int *path1Ptr = (short int*) Path1.pixel_data;

	// initializing the path1's start and end position
	int xPath1Start = path1Object.xPos;
	int yPath1Start = path1Object.yPos;
	int xPath1End = path1Object.xPos + 105;
	int yPath1End = path1Object.yPos + 37;
	
	// loop to draw the path 
	for (int y = yPath1Start; y < yPath1End; y++)//86 is the image height
	{
		for (int x = xPath1Start; x < xPath1End; x++) //140 is image width
		{	
			path1->color = path1Ptr[i]; 
				
			path1->xPos = x;
			path1->yPos = y;
	
			drawPlayer(path1);
			i++;
				
		}
	}

	// initializing the path2's start and end position
	int xPath2Start = path2Object.xPos;
	int yPath2Start = path2Object.yPos;
	int xPath2End = path2Object.xPos + 105;
	int yPath2End = path2Object.yPos + 37;
	i=0;
	
	// loop to draw path2 on screen 
	for (int y = yPath2Start; y < yPath2End; y++)//86 is the image height
	{
		for (int x = xPath2Start; x < xPath2End; x++) //140 is image width
		{	
			path1->color = path1Ptr[i]; 
				
			path1->xPos = x;
			path1->yPos = y;
	
			drawPlayer(path1);
			i++;
				
		}
	}

	// checking the path object's position, and reset it to 0 if applicable
	if(path1Object.xPos>=1024)
		path1Object.xPos = 0;
	path1Object.xPos+=5;

	if(path2Object.xPos>=1024)
		path2Object.xPos = 0;
	path2Object.xPos+=5;


	
}

/* This function is responsible for displaying the last map */
void displayLastMap(){
	
	// initializing useful variables 
	Objects *car1;
	car1 = malloc(sizeof(car1));
	int i = 0;	

	short int *car1Ptr = (short int*) Car1.pixel_data;
	
	// initializing the lastmap objects' start and end position
	int xLastMap1Start = lastMap1Object.xPos;
	int yLastMap1Start = lastMap1Object.yPos;
	int xLastMap1End =  lastMap1Object.xPos+46;
	int yLastMap1End = lastMap1Object.yPos + 36;

	// loop to display the map on the screen 

	for (int y = yLastMap1Start; y < yLastMap1End; y++)//86 is the image height
		{
			for (int x = xLastMap1Start; x < xLastMap1End; x++) //86 is image width
			{	
				car1->color = car1Ptr[i]; 
				
				car1->xPos = x;
				car1->yPos = y;
	
				drawPlayer(car1);
				i++;
				
			}
		}

	// initializing the lastmap objects' start and end position
	int xLastMap2Start = lastMap2Object.xPos;
	int yLastMap2Start = lastMap2Object.yPos;
	int xLastMap2End =  lastMap2Object.xPos+46;
	int yLastMap2End = lastMap2Object.yPos + 36;
	i=0;
	
	// loop to display the map on the screen 
	for (int y = yLastMap2Start; y < yLastMap2End; y++)//86 is the image height
		{
			for (int x = xLastMap2Start; x < xLastMap2End; x++) //86 is image width
			{	
				car1->color = car1Ptr[i]; 
				
				car1->xPos = x;
				car1->yPos = y;
	
				drawPlayer(car1);
				i++;
				
			}
		}

	// initializing
	Objects *car2;
	car2 = malloc(sizeof(car2));

	short int *car2Ptr = (short int*) Car3.pixel_data;

	// initializing the lastmap objects' start and end position
	int xLastMap3Start = lastMap3Object.xPos;
	int yLastMap3Start = lastMap3Object.yPos;
	int xLastMap3End =  lastMap3Object.xPos+46;
	int yLastMap3End = lastMap3Object.yPos + 36;
	i=0;

	// loop to display the map on the screen 
	for (int y = yLastMap3Start; y < yLastMap3End; y++)//36 is the image height
		{
			for (int x = xLastMap3Start; x < xLastMap3End; x++) //39 is image width
			{	
				car2->color = car2Ptr[i]; 
				
				car2->xPos = x;
				car2->yPos = y;
	
				drawPlayer(car2);
				i++;
				
			}
		}


	// initializing the lastmap objects' start and end position
	int xLastMap4Start = lastMap4Object.xPos;
	int yLastMap4Start = lastMap4Object.yPos;
	int xLastMap4End =  lastMap4Object.xPos+46;
	int yLastMap4End = lastMap4Object.yPos + 36;
	i=0;

	// loop to display the map on the screen
	for (int y = yLastMap4Start; y < yLastMap4End; y++)//86 is the image height
		{
			for (int x = xLastMap4Start; x < xLastMap4End; x++) //86 is image width
			{	
				car2->color = car2Ptr[i]; 
				
				car2->xPos = x;
				car2->yPos = y;
	
				drawPlayer(car2);
				i++;
				
			}
		}

	// initializing the lastmap objects' start and end position
	int xLastMap5Start = lastMap5Object.xPos;
	int yLastMap5Start = lastMap5Object.yPos;
	int xLastMap5End =  lastMap5Object.xPos+46;
	int yLastMap5End = lastMap5Object.yPos + 36;
	i=0;

	// loop to display the map on the screen
	for (int y = yLastMap5Start; y < yLastMap5End; y++)//36 is the image height
		{
			for (int x = xLastMap5Start; x < xLastMap5End; x++) //39 is image width
			{	
				car2->color = car2Ptr[i]; 
				
				car2->xPos = x;
				car2->yPos = y;
	
				drawPlayer(car2);
				i++;
				
			}
		}
	
	// initializing 
	Objects *car3;
	car3 = malloc(sizeof(car3));


	short int *car3Ptr = (short int*) Truck.pixel_data;

	// initializing the lastmap objects' start and end position
	int xLastMap6Start = lastMap6Object.xPos;
	int yLastMap6Start = lastMap6Object.yPos;
	int xLastMap6End =  lastMap6Object.xPos+90;
	int yLastMap6End = lastMap6Object.yPos + 36;
	i=0;

	// loop to display the map on the screen
	for (int y = yLastMap6Start; y < yLastMap6End; y++)//86 is the image height
		{
			for (int x = xLastMap6Start; x < xLastMap6End; x++) //86 is image width
			{	
				car3->color = car3Ptr[i]; 
				
				car3->xPos = x;
				car3->yPos = y;
	
				drawPlayer(car3);
				i++;
				
			}
		}

	// checking the path object's position, and reset it to 0 if applicable
	if(lastMap1Object.xPos>=1024)
		lastMap1Object.xPos = 0;
	lastMap1Object.xPos+=11;

	// checking the path object's position, and reset it to 0 if applicable
	if(lastMap2Object.xPos>=1024)
		lastMap2Object.xPos = 0;
	lastMap2Object.xPos+=7;

	// checking the path object's position, and reset it to 0 if applicable
	if(lastMap3Object.xPos>=1024)
		lastMap3Object.xPos = 0;
	lastMap3Object.xPos+=7;

	// checking the path object's position, and reset it to 0 if applicable
	if(lastMap4Object.xPos>=1024)
		lastMap4Object.xPos = 0;
	lastMap4Object.xPos+=10;
	
	// checking the path object's position, and reset it to 0 if applicable
	if(lastMap5Object.xPos>=1024)
		lastMap5Object.xPos = 0;
	lastMap5Object.xPos+=10;

	// checking the path object's position, and reset it to 0 if applicable
	if(lastMap6Object.xPos>=1024)
		lastMap6Object.xPos = 0;
	lastMap6Object.xPos+=11;



	

}

/* This function will be displaying moving turtles */
void displayingMovingTurtles(){

	// initializing useful variables
	Objects *turtle1, *turtle2;
	turtle1 = malloc(sizeof(turtle1));
	turtle2 = malloc(sizeof(turtle2));
	int i = 0;

	short int *turtle1Ptr = (short int*) Turtle1.pixel_data;
	
	// initializing the turtle 1's start and end position
	int xTurtle1Start = turtle1Object.xPos;
	int yTurtle1Start = turtle1Object.yPos;
	int xTurtle1End = turtle1Object.xPos + 140;
	int yTurtle1End = turtle1Object.yPos + 37;

	// draw the turtle image on the screen
	for (int y = yTurtle1Start; y < yTurtle1End; y++)//86 is the image height
	{
		for (int x = xTurtle1Start; x < xTurtle1End; x++) //140 is image width
		{	
			turtle1->color = turtle1Ptr[i]; 
				
			turtle1->xPos = x;
			turtle1->yPos = y;
	
			drawPlayer(turtle1);
			i++;
				
		}
	}

	// initializing the turtle 3's start and end position
	int xTurtle3Start = turtle3Object.xPos;
	int yTurtle3Start = turtle3Object.yPos;
	int xTurtle3End = turtle3Object.xPos + 140;
	int yTurtle3End = turtle3Object.yPos + 37;
	i=0;

	// draw the turtle image on the screen
	for (int y = yTurtle3Start; y < yTurtle3End; y++)//86 is the image height
	{
		for (int x = xTurtle3Start; x < xTurtle3End; x++) //140 is image width
		{	
			turtle1->color = turtle1Ptr[i]; 
				
			turtle1->xPos = x;
			turtle1->yPos = y;
	
			drawPlayer(turtle1);
			i++;
				
		}
	}	
	
	// initializing the turtle 2's start and end position
	int xTurtle2Start = turtle2Object.xPos;
	int yTurtle2Start = turtle2Object.yPos;
	int xTurtle2End = turtle2Object.xPos + 150;
	int yTurtle2End = turtle2Object.yPos + 36;

	short int *turtle2Ptr = (short int*) Turtle2.pixel_data;
	i=0;
	for (int y = yTurtle2Start; y < yTurtle2End; y++)//86 is the image height
	{
		for (int x = xTurtle2Start; x < xTurtle2End; x++) //140 is image width
		{	
			turtle2->color = turtle2Ptr[i]; 
				
			turtle2->xPos = x;
			turtle2->yPos = y;
	
			drawPlayer(turtle2);
			i++;
				
		}
	}

	// initializing the turtle 4's start and end position
	int xTurtle4Start = turtle4Object.xPos;
	int yTurtle4Start = turtle4Object.yPos;
	int xTurtle4End = turtle4Object.xPos + 150;
	int yTurtle4End = turtle4Object.yPos + 36;
	i=0;

	// draw the turtle image on the screen
	for (int y = yTurtle4Start; y < yTurtle4End; y++)//86 is the image height
	{
		for (int x = xTurtle4Start; x < xTurtle4End; x++) //140 is image width
		{	
			turtle1->color = turtle2Ptr[i]; 
				
			turtle1->xPos = x;
			turtle1->yPos = y;
	
			drawPlayer(turtle1);
			i++;
				
		}
	}

	// initializing the turtle 5's start and end position
	int xTurtle5Start = turtle5Object.xPos;
	int yTurtle5Start = turtle5Object.yPos;
	int xTurtle5End = turtle5Object.xPos + 150;
	int yTurtle5End = turtle5Object.yPos + 36;
	i=0;

	// draw the turtle image on the screen
	for (int y = yTurtle5Start; y < yTurtle5End; y++)//86 is the image height
	{
		for (int x = xTurtle5Start; x < xTurtle5End; x++) //140 is image width
		{	
			turtle1->color = turtle2Ptr[i]; 
				
			turtle1->xPos = x;
			turtle1->yPos = y;
	
			drawPlayer(turtle1);
			i++;
				
		}
	}

	// initializing the turtle 6's start and end position
	int xTurtle6Start = turtle6Object.xPos;
	int yTurtle6Start = turtle6Object.yPos;
	int xTurtle6End = turtle6Object.xPos + 140;
	int yTurtle6End = turtle6Object.yPos + 37;

	i = 0;

	// draw the turtle image on the screen
	for (int y = yTurtle6Start; y < yTurtle6End; y++)//86 is the image height
	{
		for (int x = xTurtle6Start; x < xTurtle6End; x++) //140 is image width
		{	
			turtle1->color = turtle1Ptr[i]; 
				
			turtle1->xPos = x;
			turtle1->yPos = y;
	
			drawPlayer(turtle1);
			i++;
				
		}
	}

	// initializing the turtle 7's start and end position
	int xTurtle7Start = turtle7Object.xPos;
	int yTurtle7Start = turtle7Object.yPos;
	int xTurtle7End = turtle7Object.xPos + 140;
	int yTurtle7End = turtle7Object.yPos + 37;
	i=0;

	// draw the turtle image on the screen
	for (int y = yTurtle7Start; y < yTurtle7End; y++)//86 is the image height
	{
		for (int x = xTurtle7Start; x < xTurtle7End; x++) //140 is image width
		{	
			turtle1->color = turtle1Ptr[i]; 
				
			turtle1->xPos = x;
			turtle1->yPos = y;
	
			drawPlayer(turtle1);
			i++;
				
		}
	}		

	// initializing the turtle 8's start and end position
	int xTurtle8Start = turtle8Object.xPos;
	int yTurtle8Start = turtle8Object.yPos;
	int xTurtle8End = turtle8Object.xPos + 150;
	int yTurtle8End = turtle8Object.yPos + 36;
	i=0;

	// draw the turtle image on the screen
	for (int y = yTurtle8Start; y < yTurtle8End; y++)//86 is the image height
	{
		for (int x = xTurtle8Start; x < xTurtle8End; x++) //140 is image width
		{	
			turtle2->color = turtle2Ptr[i]; 
				
			turtle2->xPos = x;
			turtle2->yPos = y;
	
			drawPlayer(turtle2);
			i++;
				
		}
	}


	// checking the turtle1Object's position, and reset it to 1024; if applicable
	if(turtle1Object.xPos<=0)
		turtle1Object.xPos = 1024;
	turtle1Object.xPos-=4;

	// checking the turtle1Object's position, and reset it to 1024; if applicable
	if(turtle2Object.xPos<=0)
		turtle2Object.xPos = 1024;
	turtle2Object.xPos-=4;
	
	// checking the turtle1Object's position, and reset it to 1024; if applicable
	if(turtle3Object.xPos<=0)
		turtle3Object.xPos = 1024;
	turtle3Object.xPos-=4;

	// checking the turtle1Object's position, and reset it to 1024; if applicable
	if(turtle4Object.xPos<=0)
		turtle4Object.xPos = 1024;
	turtle4Object.xPos-=7;

	// checking the turtle1Object's position, and reset it to 1024; if applicable
	if(turtle5Object.xPos<=0)
		turtle5Object.xPos = 1024;
	turtle5Object.xPos-=7;

	// checking the turtle1Object's position, and reset it to 1024; if applicable
	if(turtle6Object.xPos<=0)
		turtle6Object.xPos = 1024;
	turtle6Object.xPos-=4;

	// checking the turtle1Object's position, and reset it to 1024; if applicable
	if(turtle7Object.xPos<=0)
		turtle7Object.xPos = 1024;
	turtle7Object.xPos-=4;

	// checking the turtle1Object's position, and reset it to 1024; if applicable
	if(turtle8Object.xPos<=0)
		turtle8Object.xPos = 1024;
	turtle8Object.xPos-=4;



}


// This function will display a moving log to the screen
void displayingMovingLog(){

	// initializing 
	Objects *log1;
	log1 = malloc(sizeof(log1));
	int i =0;
	int xLog1Start, yLog1Start, yLog1End, xLog1End;

	short int *log1Ptr = (short int*) Log1.pixel_data;	
	
	// initializing the log1's start and end position
	xLog1Start = log1Object.xPos;
	yLog1Start = log1Object.yPos;
	xLog1End = log1Object.xPos + 250;
	yLog1End = log1Object.yPos + 36;

	// draw the log image on the screen
	for (int y = yLog1Start; y < yLog1End; y++)//86 is the image height
	{
		for (int x = xLog1Start; x < xLog1End; x++) //86 is image width
		{	
			log1->color = log1Ptr[i]; 
				
			log1->xPos = x;
			log1->yPos = y;
	
			drawPlayer(log1);
			i++;
				
		}
	}

	// initializing the log2's start and end position
	int xLog2Start = log2Object.xPos;
	int yLog2Start = log2Object.yPos;
	int xLog2End = log2Object.xPos + 250;
	int yLog2End = log2Object.yPos + 36;
	i=0;

	// draw the log image on the screen
	for (int y = yLog2Start; y < yLog2End; y++)//86 is the image height
	{
		for (int x = xLog2Start; x < xLog2End; x++) //86 is image width
		{	
			log1->color = log1Ptr[i]; 
				
			log1->xPos = x;
			log1->yPos = y;
	
			drawPlayer(log1);
			i++;
				
		}
	}

	// initializing the log3's start and end position
	int xLog3Start = log3Object.xPos;
	int yLog3Start = log3Object.yPos;
	int xLog3End = log3Object.xPos + 250;
	int yLog3End = log3Object.yPos + 36;
	i=0;

	// draw the log image on the screen
	for (int y = yLog3Start; y < yLog3End; y++)//86 is the image height
	{
		for (int x = xLog3Start; x < xLog3End; x++) //86 is image width
		{	
			log1->color = log1Ptr[i]; 
				
			log1->xPos = x;
			log1->yPos = y;
	
			drawPlayer(log1);
			i++;
				
		}
	}

	// initializing the log4's start and end position
	int xLog4Start = log4Object.xPos;
	int yLog4Start = log4Object.yPos;
	int xLog4End = log4Object.xPos + 250;
	int yLog4End = log4Object.yPos + 36;
	i=0;

	// draw the log image on the screen
	for (int y = yLog4Start; y < yLog4End; y++)//86 is the image height
	{
		for (int x = xLog4Start; x < xLog4End; x++) //86 is image width
		{	
			log1->color = log1Ptr[i]; 
				
			log1->xPos = x;
			log1->yPos = y;
	
			drawPlayer(log1);
			i++;
				
		}
	}

	// initializing the log5's start and end position
	int xLog5Start = log5Object.xPos;
	int yLog5Start = log5Object.yPos;
	int xLog5End = log5Object.xPos + 250;
	int yLog5End = log5Object.yPos + 36;
	i=0;

	// draw the log image on the screen
	for (int y = yLog5Start; y < yLog5End; y++)//86 is the image height
	{
		for (int x = xLog5Start; x < xLog5End; x++) //86 is image width
		{	
			log1->color = log1Ptr[i]; 
				
			log1->xPos = x;
			log1->yPos = y;
	
			drawPlayer(log1);
			i++;
				
		}
	}


	// displaying the frog
	displayFrog();

	// waiting
	wait(30000);


	// checking the turtle1Object's position, and reset it to 0; if applicable
	if(log1Object.xPos>=1024)
		log1Object.xPos = 0;
	log1Object.xPos+=4;

	// checking the turtle1Object's position, and reset it to 0; if applicable
	if(log2Object.xPos>=1024)
		log2Object.xPos = 0;
	log2Object.xPos+=4;
	
	// checking the turtle1Object's position, and reset it to 0; if applicable
	if(log3Object.xPos>=1024)
		log3Object.xPos = 0;
	log3Object.xPos+=9;

	// checking the turtle1Object's position, and reset it to 0; if applicable
	if(log4Object.xPos>=1024)
		log4Object.xPos = 0;
	log4Object.xPos+=3;

	// checking the turtle1Object's position, and reset it to 0; if applicable
	if(log5Object.xPos>=1024)
		log5Object.xPos = 0;
	log5Object.xPos+=3;



}

int displayMapTwo(){

//	printf("\n FROG x: %d",frogObject.xPos);
//	printf("\n FROG y: %d", frogObject.yPos);
//	printf("\n LOG x: %d",lastMap2Object.xPos);		
//	printf("\n LOG y: %d", lastMap2Object.yPos);	
 	
	// initialize variables
	int variableLog1, variableLog2;

	// check of the frog y position matches with the log y position
	if(frogObject.yPos -1 == log1Object.yPos ){	
		variableLog1 = (log1Object.xPos + 230) - frogObject.xPos;
		variableLog2 = (log2Object.xPos + 230) - frogObject.xPos;
		if(frogObject.xPos>=log1Object.xPos && frogObject.xPos<=log1Object.xPos + 230){
			frogObject.xPos+=4;
			if(log1Object.xPos >=1024){
				frogObject.xPos = 234-variableLog1;
			}
		}else if(frogObject.xPos>=log2Object.xPos && frogObject.xPos<=log2Object.xPos + 230){
			frogObject.xPos+=4;
			if(log2Object.xPos >=1024){
				frogObject.xPos = 234-variableLog2;
			}

		}
		else{
			// reset the frog's position back to the beginning
			if(frogObject.lives>=1){				
				frogObject.yPos = 660;
				// decrement the life
				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}
			//set flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	int turtleLog1, turtleLog2, turtleLog3;

	// check of the frog y position matches with the turtle's y position
	if(frogObject.yPos -1 == turtle1Object.yPos ){
		turtleLog1 = frogObject.xPos;
		turtleLog2 = frogObject.xPos;
		turtleLog3 = frogObject.xPos;


		if((frogObject.xPos>=turtle1Object.xPos && frogObject.xPos<=turtle1Object.xPos + 140)){
			frogObject.xPos -= 4;
	
			if(turtle1Object.xPos <= 0){
				frogObject.xPos = 1020 + turtleLog1;
			}
		}else if(frogObject.xPos>=turtle2Object.xPos && frogObject.xPos<=turtle2Object.xPos + 150){
			frogObject.xPos-=4;
			
			if(turtle2Object.xPos == 0){
				frogObject.xPos = 1020 + turtleLog2;
			}
		}else if(frogObject.xPos>=turtle3Object.xPos && frogObject.xPos<=turtle3Object.xPos + 140){
			frogObject.xPos -= 4;
			if(turtle3Object.xPos <= 0){
				frogObject.xPos = 1020 + turtleLog3;
			}

		}
		else{		
			// reset the frog's position back to the beginning
			if(frogObject.lives>=1){				
				frogObject.yPos = 660;
				// decrement the life
				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);

				return 0;
			}
			// set flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	// check of the frog y position matches with the path's y position
	if(frogObject.yPos == path1Object.yPos){
		variableLog1 = (path1Object.xPos + 105) - frogObject.xPos;
		variableLog2 = (path2Object.xPos + 105) - frogObject.xPos;
		
		if(frogObject.xPos>=path1Object.xPos && frogObject.xPos<=path1Object.xPos + 105){
			frogObject.xPos+=5;
			if(path1Object.xPos >=1023){
				frogObject.xPos = 110-variableLog1;
			}
		}else if(frogObject.xPos>=path2Object.xPos && frogObject.xPos<=path2Object.xPos + 105){
			frogObject.xPos+=5;
			if(path2Object.xPos >=1023){
				frogObject.xPos = 110-variableLog2;
			}

		}
		else{		
			// reset the frog's position back to the beginning
			if(frogObject.lives>=1){				
				frogObject.yPos = 660;
				// decrement life 
				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}
			// set flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	// check of the frog y position matches with the turtle4's y position
	if(frogObject.yPos == turtle4Object.yPos){
		// initialize
		turtleLog1 = frogObject.xPos;
		turtleLog2 = frogObject.xPos;
		turtleLog3 = frogObject.xPos;


		if((frogObject.xPos>=turtle4Object.xPos && frogObject.xPos<=turtle4Object.xPos + 150)){
			frogObject.xPos -= 7;
			if(turtle4Object.xPos <= 0){
				frogObject.xPos = 1020 + turtleLog1;
			}
		}else if(frogObject.xPos>=turtle5Object.xPos && frogObject.xPos<=turtle5Object.xPos + 150)
		{
			frogObject.xPos-=7;
			if(turtle5Object.xPos <= 0)
			{
				frogObject.xPos = 1020 + turtleLog2;
			}

		}
		else{			
			// reset the frog's position back to the beginning
			if(frogObject.lives>=1)
			{				
				frogObject.yPos = 660;
				// decrement the life
				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}
			// set the flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	// check of the frog y position matches with the turtle6's y position
	if(frogObject.yPos == turtle6Object.yPos ){
		// initialize
		turtleLog1 = frogObject.xPos;
		turtleLog2 = frogObject.xPos;
		turtleLog3 = frogObject.xPos;


		if((frogObject.xPos>=turtle6Object.xPos && frogObject.xPos<=turtle6Object.xPos + 140)){
			frogObject.xPos -= 4;
			if(turtle6Object.xPos <= 0){
				frogObject.xPos = 1020 + turtleLog1;
			}
		}else if(frogObject.xPos>=turtle8Object.xPos && frogObject.xPos<=turtle8Object.xPos + 150){
			frogObject.xPos-=4;
			if(turtle8Object.xPos == 0){
				frogObject.xPos = 1020 + turtleLog2;
			}
		}else if(frogObject.xPos>=turtle7Object.xPos && frogObject.xPos<=turtle7Object.xPos + 140){
			frogObject.xPos -= 4;
			if(turtle7Object.xPos <= 0){
				frogObject.xPos = 1020 + turtleLog3;
			}

		}
		else{		
			// reset the frog's position back to the beginning
			if(frogObject.lives>=1){				
				frogObject.yPos = 660;

				// decrement the life
				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}
			// set flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	// check of the frog y position matches with the log3's y position
	if(frogObject.yPos  == log3Object.yPos ){	
		variableLog1 = (log3Object.xPos + 230) - frogObject.xPos;
		
		if(frogObject.xPos>=log3Object.xPos && frogObject.xPos<=log3Object.xPos + 230){
			frogObject.xPos+=9;
			if(log3Object.xPos >=1024){
				frogObject.xPos = 234-variableLog1;
			}
		}else{		
			if(frogObject.lives>=1){				
				frogObject.yPos = 660;

				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}
			frogObject.flag = 1;
			return 0;
		}
	}

	// check of the frog y position matches with the log4's y position
	if(frogObject.yPos == log4Object.yPos ){	
		variableLog1 = (log4Object.xPos + 230) - frogObject.xPos;
		variableLog2 = (log5Object.xPos + 230) - frogObject.xPos;

		if(frogObject.xPos>=log4Object.xPos && frogObject.xPos<=log4Object.xPos + 230)
		{
			frogObject.xPos+=3;
			if(log4Object.xPos >=1024)
			{
				frogObject.xPos = 234-variableLog1;
			}
		}else if(frogObject.xPos>=log5Object.xPos && frogObject.xPos<=log5Object.xPos + 230)
			{
			frogObject.xPos+=3;
			if(log5Object.xPos >=1024)
			{
				frogObject.xPos = 234-variableLog2;
			}

		}
		else{	
			// reset the frog's position back to the beginning	
			if(frogObject.lives>=1){	
				
				frogObject.yPos = 660;	
				// decrement the life
				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}
			//set flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	// check of the frog y position matches with the lastmap's y position
	if(frogObject.yPos +1 == lastMap1Object.yPos){
		if((frogObject.xPos >= lastMap1Object.xPos && frogObject.xPos <= lastMap1Object.xPos+45)){
				
			// reset the frog's position back to the beginning	
			if(frogObject.lives>=1){
				// decrement the life
				frogObject.lives--;
				frogObject.yPos = 660;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}

			
			//set flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	

	// check of the frog y position matches with the lastmap2's y position
	if(frogObject.yPos +1 == lastMap2Object.yPos){
			
		if((frogObject.xPos >= lastMap2Object.xPos && frogObject.xPos <= lastMap2Object.xPos+45) || (frogObject.xPos >= lastMap3Object.xPos && frogObject.xPos <= lastMap3Object.xPos+45)){
				
			// reset the frog's position back to the beginning
			if(frogObject.lives>=1){				
				frogObject.yPos = 660;

				// decrement the life
				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}

		
			// set flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	// check of the frog y position matches with the lastmap4's y position
	if(frogObject.yPos +1 == lastMap4Object.yPos){
		if((frogObject.xPos >= lastMap4Object.xPos && frogObject.xPos <= lastMap4Object.xPos+45) || (frogObject.xPos >= lastMap5Object.xPos && frogObject.xPos <= lastMap5Object.xPos+45)){
					
			// reset the frog's position back to the beginning
			if(frogObject.lives>=1){				
				frogObject.yPos = 660;
				
				// decrement the lives
				frogObject.lives--;
				//printf("LIVES LEFT: %d", frogObject.lives);
				return 0;
			}

			
			// set flag to 1
			frogObject.flag = 1;
			return 0;
		}
	}

	// check of the frog y position matches with the lastmap6's y position
	if(frogObject.yPos +1 == lastMap6Object.yPos){
		if((frogObject.xPos >= lastMap6Object.xPos && frogObject.xPos <= lastMap6Object.xPos+90)){
					
			// reset the frog's position back to the beginning	
			if(frogObject.lives>=1){				
				frogObject.yPos = 660;
	
				// decrement the life
				frogObject.lives--;
				return 0;
			}

			
			// set the flag to 1
			frogObject.flag = 1;
			//printf("LIVES LEFT: %d", frogObject.lives);
			return 0;
		}
	}

		
}


/* This function will diplay the frog to the screen */
void displayFrog(){
	
		// initilize 
		Player *player;
		player = malloc(sizeof(player));

		short int *frogPtr = (short int*) Frog.pixel_data;
		int i=0;

		//FOR UPDATING THE POSITION OF THE FROG
		int yFrogEnd, xFrogEnd, xFrogStart, yFrogStart;
		yFrogEnd = frogObject.yPos + 36;
		xFrogEnd = frogObject.xPos + 36;
		yFrogStart = frogObject.yPos;
		xFrogStart = frogObject.xPos;
	
		// displaying the frog to the screen 
		for (int y = yFrogStart; y < yFrogEnd; y++)//96 is the image height
		{
			for (int x = xFrogStart; x < xFrogEnd; x++) //96 is image width
			{	
				player->color = frogPtr[i]; 
				
				player->xPos = x;
				player->yPos = y;
	
				drawPlayer(player);
				i++;
				
			}
		}
	
		return 0;

}


/* This function will do the playing of Map one */
/* @Param: *invokedPlayer */
void* playingMapOne(void *invokedPlayer){
		int storePreviousScreen = frogObject.screenChange;
		frogObject.flag = 0;
		int buttonPressed = threadReadingSnes();
		do{		
			int previousXPos = frogObject.xPos;		
			int previousYPos = frogObject.yPos;
			//printf("\n y : %d", frogObject.yPos);

			// check if button 5 was pressed
			if(buttonPressed == 5){
				frogObject.moves--;
				//printf("\nMoves left: %d", frogObject.moves);
				if(frogObject.moves == 0){
					if(frogObject.lives>=1)
						frogObject.lives--;
					frogObject.moves = 100;
				}
				frogObject.yPos -= 36;
				//printf("\n y : %d", previousYPos);
				if(frogObject.tracker ==1 && frogObject.yPos>372)
					displayingBackground2();
				else if(frogObject.tracker == 1 && frogObject.yPos<=372)
					replacingTile(previousXPos, previousYPos, buttonPressed);
				else{
					replacingTile(previousXPos, previousYPos, buttonPressed);
				}
			}

			// check if button 6 was pressed
			else if(buttonPressed == 6){
				frogObject.moves--;
				//printf("\nMoves left: %d", frogObject.moves);
				if(frogObject.moves == 0){
					if(frogObject.lives>=1){
						frogObject.lives--;
					}
					frogObject.moves = 100;
				}
				if(frogObject.yPos == 660 ){	
					;
				}

				else{
					frogObject.yPos+=36;	
					if(frogObject.tracker ==1 && frogObject.yPos>372)
						displayingBackground2();
					else if(frogObject.tracker == 1 && frogObject.yPos<=372)
						replacingTile(previousXPos, previousYPos, buttonPressed);
					else{
						replacingTile(previousXPos, previousYPos, buttonPressed);
					}
				}
			}

			// check if button 7 was pressed
			else if(buttonPressed == 7){
				frogObject.xPos-=36;
				if(frogObject.xPos<=0)
					frogObject.xPos = 1000;
				frogObject.moves--;
				//printf("\nMoves left: %d", frogObject.moves);
				if(frogObject.moves == 0){
					if(frogObject.lives>=1){
						frogObject.lives--;
					}
					frogObject.moves = 100;
				}

				if(frogObject.tracker ==1 && frogObject.yPos>372)
					displayingBackground2();
				else if(frogObject.tracker == 1 && frogObject.yPos<=372)
					replacingTile(previousXPos, previousYPos, buttonPressed);
				else{
					replacingTile(previousXPos, previousYPos, buttonPressed);
				}
			}

			// check if button 8 was pressed
			else if(buttonPressed == 8){
				frogObject.moves--;
				//printf("\nMoves left: %d", frogObject.moves);
				if(frogObject.moves == 0){
					if(frogObject.lives>=1){
						frogObject.lives--;
					}
					frogObject.moves = 100;
				}

				frogObject.xPos+=36;
				if(frogObject.xPos>=1024)
					frogObject.xPos=0;
				if(frogObject.tracker ==1 && frogObject.yPos>372)
					displayingBackground2();
				else if(frogObject.tracker == 1 && frogObject.yPos<=372)
					replacingTile(previousXPos, previousYPos, buttonPressed);
				else{
					replacingTile(previousXPos, previousYPos, buttonPressed);
				}
			}
		
			// check if button 9 was pressed
			else if(buttonPressed == 9){
			//ADDING PAUSE MENU HERE
				while(frogObject.screenChange!=8){
					displayingPauseMenu();		
				}
				//printf("\nHere");
				frogObject.screenChange = storePreviousScreen;		

				if(frogObject.tracker == 0 || frogObject.screenChange == 0)
					displayingBackground();
				
				if(frogObject.tracker == 1)
					displayingBackground2();
			}
		
		// call threadReadingSnes() and make it equal to a variable button pressed to compare afterwards
		buttonPressed = threadReadingSnes();	
		}while(1);
		// set the flag to 1
		frogObject.flag = 1;
	// exit the pthread
	pthread_exit(0);
}


/* This function will display Map one */

int displayMapOne(){

//	printf("\n FROG x: %d",frogObject.xPos);
//	printf("\n FROG y: %d", frogObject.yPos);
//	printf("\n CAR x: %d",car4Object.xPos);		
//	printf("\n CAR y: %d",car4Object.yPos);	

		// check if frog's y position is equal to car1Object y Position
		if(frogObject.yPos -1 == car1Object.yPos){
			if((frogObject.xPos >= car1Object.xPos && frogObject.xPos <= car1Object.xPos+39) || (frogObject.xPos >= car3Object.xPos && frogObject.xPos <= car3Object.xPos+39 )){
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

				frogObject.lives--;
					//printf("LIVES LEFT: %d", frogObject.lives);
			return 0;
			}

				//printf("colliding");
				frogObject.flag = 1;
				return 0;
			}
		}
	
		// check if frog's y position is equal to truck1Object y Position
		if(frogObject.yPos -1 == truck1Object.yPos){
			if((frogObject.xPos >= truck1Object.xPos && frogObject.xPos <= truck1Object.xPos + 90) || (frogObject.xPos >= truck2Object.xPos && frogObject.xPos <= truck2Object.xPos + 90)){
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

				frogObject.lives--;
						//printf("LIVES LEFT: %d", frogObject.lives);
		return 0;
			}

				frogObject.flag = 1;
				return 0;
			}
		}
	
		// check if frog's y position is equal to car4Object y Position
		if(frogObject.yPos == car4Object.yPos){
			if((frogObject.xPos >= car5Object.xPos -36 && frogObject.xPos <= car5Object.xPos) || (frogObject.xPos >= car4Object.xPos - 36 && frogObject.xPos <= car4Object.xPos)){
				
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
							//printf("LIVES LEFT: %d", frogObject.lives);
		return 0;
				}
				frogObject.flag = 1;
				return 0;
			}
		}

		// check if frog's y position is equal to car6Object y Position
		if(frogObject.yPos == car6Object.yPos){
			if((frogObject.xPos >= car6Object.xPos && frogObject.xPos <= car6Object.xPos + 39) || (frogObject.xPos >= car7Object.xPos  && frogObject.xPos <= car7Object.xPos+36) || (frogObject.xPos >= car8Object.xPos && frogObject.xPos <= car8Object.xPos+39))
			{	
					
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
					return 0;
				}
				frogObject.flag = 1;
				return 0;
			}
		}

		// check if frog's y position is equal to truck4Object y Position
		if(frogObject.yPos == truck4Object.yPos){
			if(frogObject.xPos >= truck4Object.xPos - 10 && frogObject.xPos <= truck4Object.xPos + 90){
					
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
							//printf("LIVES LEFT: %d", frogObject.lives);
		return 0;
				}
				frogObject.flag = 1;
				return 0;
			}
		}

		// check if frog's y position is equal to truck5Object y Position
		if(frogObject.yPos + 1 == truck5Object.yPos){
			if((frogObject.xPos >= truck5Object.xPos && frogObject.xPos <= truck5Object.xPos + 90) || (frogObject.xPos >= truck6Object.xPos && frogObject.xPos <= truck6Object.xPos + 90)){
					
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
							//printf("LIVES LEFT: %d", frogObject.lives);
		return 0;
				}

				frogObject.flag = 1;
				return 0;
			}
		}

		// check if frog's y position is equal to car9Object y Position
		if(frogObject.yPos + 2== car9Object.yPos){
			if((frogObject.xPos >= car9Object.xPos -36 && frogObject.xPos <= car9Object.xPos +36) || (frogObject.xPos >= car10Object.xPos - 36 && frogObject.xPos <= car10Object.xPos + 36) || (frogObject.xPos >= car11Object.xPos - 36 && frogObject.xPos <= car11Object.xPos + 36)){
					
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
							//printf("LIVES LEFT: %d", frogObject.lives);
		return 0;
				}
			
				frogObject.flag = 1;
				return 0;
			}
		}


		// check if frog's y position is equal to actor1Object y Position
		if(frogObject.yPos + 1 == actor1Object.yPos){
			if((frogObject.xPos >= actor1Object.xPos && frogObject.xPos <= actor1Object.xPos + 210) || (frogObject.xPos >= actor2Object.xPos && frogObject.xPos <= actor2Object.xPos + 130) || (frogObject.xPos >= actor3Object.xPos && frogObject.xPos <= actor3Object.xPos + 210)){
						
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
							//printf("LIVES LEFT: %d", frogObject.lives);
		return 0;
				}

				frogObject.flag = 1;
				return 0;
			}
		}

		// check if frog's y position is equal to actor41Object y Position
		if(frogObject.yPos + 1 == actor4Object.yPos){
			if((frogObject.xPos >= actor4Object.xPos && frogObject.xPos <= actor4Object.xPos + 45) || (frogObject.xPos >= actor5Object.xPos && frogObject.xPos <= actor5Object.xPos + 45)){
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
							//printf("LIVES LEFT: %d", frogObject.lives);
		return 0;
				}

			
				frogObject.flag = 1;
				return 0;
			}
		}
		
		// check if frog's y position is equal to actor6Object y Position
		if(frogObject.yPos + 1== actor6Object.yPos){
			if(frogObject.xPos >= actor6Object.xPos && frogObject.xPos <= actor6Object.xPos +150){
					
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
								//printf("LIVES LEFT: %d", frogObject.lives);
	return 0;
				}


				frogObject.flag = 1;
				return 0;
			}
		}

		// check if frog's y position is equal to actor7Object y Position
		if(frogObject.yPos+1 == actor7Object.yPos){
			if((frogObject.xPos >= actor7Object.xPos  && frogObject.xPos <= actor7Object.xPos + 45) || (frogObject.xPos >= actor8Object.xPos  && frogObject.xPos <= actor8Object.xPos + 45)){
	
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
								//printf("LIVES LEFT: %d", frogObject.lives);
	return 0;
				}

				frogObject.flag = 1;
				return 0;
			}
		}
	
		// check if frog's y position is equal to actor9Object y Position
		if(frogObject.yPos + 1 == actor9Object.yPos){
			if((frogObject.xPos >= actor9Object.xPos && frogObject.xPos <= actor9Object.xPos + 42) || (frogObject.xPos >= actor10Object.xPos && frogObject.xPos <= actor10Object.xPos + 42)){

	
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
								//printf("LIVES LEFT: %d", frogObject.lives);
	return 0;
				}

				frogObject.flag = 1;
				return 0;
			}
		}

		// check if frog's y position is equal to actor11Object y Position
		if(frogObject.yPos + 1 == actor11Object.yPos){
			if((frogObject.xPos >= actor11Object.xPos && frogObject.xPos - 25 <= actor11Object.xPos) || (frogObject.xPos >= actor12Object.xPos - 25 && frogObject.xPos <= actor12Object.xPos) || (frogObject.xPos >= actor13Object.xPos - 25 && frogObject.xPos <= actor13Object.xPos)){

	
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
								//printf("LIVES LEFT: %d", frogObject.lives);
	return 0;
				}

				frogObject.flag = 1;
				return 0;
			}
		}

		// check if frog's y position is equal to actor14Object y Position
		if(frogObject.yPos == actor14Object.yPos){
			if((frogObject.xPos >= actor14Object.xPos - 20 && frogObject.xPos <= actor14Object.xPos + 150) || (frogObject.xPos >= actor15Object.xPos - 20 && frogObject.xPos <= actor15Object.xPos + 150)){

	
				if(frogObject.lives>=1){				
				frogObject.yPos = 660;

					frogObject.lives--;
								//printf("LIVES LEFT: %d", frogObject.lives);
	return 0;
				}
				frogObject.flag = 1;
				return 0;
			}
		}


	
		
		Player *player;
		player = malloc(sizeof(player));

		short int *frogPtr = (short int*) Frog.pixel_data;
		int i=0;

		//FOR UPDATING THE POSITION OF THE FROG

		int yFrogEnd, xFrogEnd, xFrogStart, yFrogStart;
		yFrogEnd = frogObject.yPos + 36;
		xFrogEnd = frogObject.xPos + 36;
		yFrogStart = frogObject.yPos;
		xFrogStart = frogObject.xPos;
	

		// display the frog to the screen 
		for (int y = yFrogStart; y < yFrogEnd; y++)//96 is the image height
		{
			for (int x = xFrogStart; x < xFrogEnd; x++) //96 is image width
			{	
				player->color = frogPtr[i]; 
				
				player->xPos = x;
				player->yPos = y;
	
				drawPlayer(player);
				i++;
				
			}
		}
	
	return 0;
}	


/* This function displays moving actors to the screen */
void displayingMovingActor(){

	// initializing 
	Objects *actor;
	actor = malloc(sizeof(actor));
	int i =0;
	int xActor1Start, yActor1Start, yActor1End, xActor1End;

	short int *actorPtr = (short int*) Actor1.pixel_data;	
	
	//FOR UPDATING THE POSITION OF THE FROG
	xActor1Start = actor1Object.xPos;
	yActor1Start = actor1Object.yPos;
	xActor1End = actor1Object.xPos + 200;
	yActor1End = actor1Object.yPos + 36;

	// this loop will draw actor 1, including the pixels, colors 
	//86 is the image height
	for (int y = yActor1Start; y < yActor1End; y++)
	{
		for (int x = xActor1Start; x < xActor1End; x++) //86 is image width
		{	
			actor->color = actorPtr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	short int *actor2Ptr = (short int*) Actor2.pixel_data;	
	int xActor2Start = actor2Object.xPos;
	int yActor2Start = actor2Object.yPos;
	int xActor2End = actor2Object.xPos + 140;
	int yActor2End = actor2Object.yPos + 36;
	i=0;

	// this loop will draw actor 2, including the pixels, colors 
	//86 is the image height
	for (int y = yActor2Start; y < yActor2End; y++)//86 is the image height
	{
		for (int x = xActor2Start; x < xActor2End; x++) //86 is image width
		{	
			actor->color = actor2Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}
	
	//FOR UPDATING THE POSITION OF THE FROG
	int xActor3Start = actor3Object.xPos;
	int yActor3Start = actor3Object.yPos;
	int xActor3End = actor3Object.xPos + 200;
	int yActor3End = actor3Object.yPos + 36;
	i=0;
 
	// this loop will draw actor 3, including the pixels, colors 
	// 36 is the image height
	for (int y = yActor3Start; y < yActor3End; y++)
	{
		for (int x = xActor3Start; x < xActor3End; x++) //140 is image width
		{	
			actor->color = actorPtr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	short int *actor3Ptr = (short int*) Actor3.pixel_data;	
	int xActor4Start = actor4Object.xPos;
	int yActor4Start = actor4Object.yPos;
	int xActor4End = actor4Object.xPos + 45;
	int yActor4End = actor4Object.yPos + 36;
	i=0;

	// this loop will draw actor 4, including the pixels, colors 
	// 36 is the image height
	for (int y = yActor4Start; y < yActor4End; y++)
	{
		for (int x = xActor4Start; x < xActor4End; x++) //45 is image width
		{	
			actor->color = actor3Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	int xActor5Start = actor5Object.xPos;
	int yActor5Start = actor5Object.yPos;
	int xActor5End = actor5Object.xPos + 45;
	int yActor5End = actor5Object.yPos + 36;
	i=0;

	// this loop will draw actor 5, including the pixels, colors 
	// 36 is the image height
	for (int y = yActor5Start; y < yActor5End; y++)
	{
		for (int x = xActor5Start; x < xActor5End; x++) //45 is image width
		{	
			actor->color = actor3Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}


	//FOR UPDATING THE POSITION OF THE FROG
	short int *actor4Ptr = (short int*) Actor4.pixel_data;	
	int xActor6Start = actor6Object.xPos;
	int yActor6Start = actor6Object.yPos;
	int xActor6End = actor6Object.xPos + 210;
	int yActor6End = actor6Object.yPos + 36;
	i=0;

	// this loop will draw actor 6, including the pixels, colors 
	// 36 is the image height
	for (int y = yActor6Start; y < yActor6End; y++)
	{
		for (int x = xActor6Start; x < xActor6End; x++) //210 is image width
		{	
			actor->color = actor4Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}
	
	//FOR UPDATING THE POSITION OF THE FROG
	short int *actor5Ptr = (short int*) Actor5.pixel_data;	
	int xActor7Start = actor7Object.xPos;
	int yActor7Start = actor7Object.yPos;
	int xActor7End = actor7Object.xPos + 45;
	int yActor7End = actor7Object.yPos + 36;
	i=0;

	// this loop will draw actor 7, including the pixels, colors 
	// 36 is the image height
	for (int y = yActor7Start; y < yActor7End; y++)
	{
		for (int x = xActor7Start; x < xActor7End; x++) //210 is image width
		{	
			actor->color = actor5Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	int xActor8Start = actor8Object.xPos;
	int yActor8Start = actor8Object.yPos;
	int xActor8End = actor8Object.xPos + 45;
	int yActor8End = actor8Object.yPos + 36;
	i=0;

	// this loop will draw actor 8, including the pixels, color
	//836 is the image height 
	for (int y = yActor8Start; y < yActor8End; y++)
	{
		for (int x = xActor8Start; x < xActor8End; x++) //210 is image width
		{	
			actor->color = actor5Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	int xActor9Start = actor9Object.xPos;
	int yActor9Start = actor9Object.yPos;
	int xActor9End = actor9Object.xPos + 45;
	int yActor9End = actor9Object.yPos + 36;
	i=0;

	// this loop will draw actor 9, including the pixels, colors 	
	// 36 is the image height
	for (int y = yActor9Start; y < yActor9End; y++)
	{
		for (int x = xActor9Start; x < xActor9End; x++) //210 is image width
		{	
			actor->color = actor3Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	short int *actor7Ptr = (short int*) Actor7.pixel_data;	
	int xActor10Start = actor10Object.xPos;
	int yActor10Start = actor10Object.yPos;
	int xActor10End = actor10Object.xPos + 45;
	int yActor10End = actor10Object.yPos + 36;
	i=0;

	// this loop will draw actor 10, including the pixels, colors 
	//36 is the image height
	for (int y = yActor10Start; y < yActor10End; y++)
	{
		for (int x = xActor10Start; x < xActor10End; x++) //210 is image width
		{	
			actor->color = actor7Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}


	//FOR UPDATING THE POSITION OF THE FROG
	short int *actor8Ptr = (short int*) Actor8.pixel_data;	
	int xActor11Start = actor11Object.xPos;
	int yActor11Start = actor11Object.yPos;
	int xActor11End = actor11Object.xPos + 45;
	int yActor11End = actor11Object.yPos + 36;
	i=0;

	// this loop will draw actor 11, including the pixels, colors
	for (int y = yActor11Start; y < yActor11End; y++)
	{
		for (int x = xActor11Start; x < xActor11End; x++) //210 is image width
		{	
			actor->color = actor8Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	int xActor12Start = actor12Object.xPos;
	int yActor12Start = actor12Object.yPos;
	int xActor12End = actor12Object.xPos + 45;
	int yActor12End = actor12Object.yPos + 36;
	i=0;

	// this loop will draw actor 12, including the pixels, colors 
	for (int y = yActor12Start; y < yActor12End; y++)//36 is the image height
	{
		for (int x = xActor12Start; x < xActor12End; x++) //210 is image width
		{	
			actor->color = actor8Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	int xActor13Start = actor13Object.xPos;
	int yActor13Start = actor13Object.yPos;
	int xActor13End = actor13Object.xPos + 45;
	int yActor13End = actor13Object.yPos + 36;
	i=0;

	// this loop will draw actor 13, including the pixels, colors 
	for (int y = yActor13Start; y < yActor13End; y++)//36 is the image height
	{
		for (int x = xActor13Start; x < xActor13End; x++) //210 is image width
		{	
			actor->color = actor8Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}

	//FOR UPDATING THE POSITION OF THE FROG
	int xActor14Start = actor14Object.xPos;
	int yActor14Start = actor14Object.yPos;
	int xActor14End = actor14Object.xPos + 210;
	int yActor14End = actor14Object.yPos + 36;
	i=0;

	// this loop will draw actor 14, including the pixels, colors 
	for (int y = yActor14Start; y < yActor14End; y++)//36 is the image height
	{
		for (int x = xActor14Start; x < xActor14End; x++) //210 is image width
		{	
			actor->color = actor4Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}
	
	//FOR UPDATING THE POSITION OF THE FROG
	int xActor15Start = actor15Object.xPos;
	int yActor15Start = actor15Object.yPos;
	int xActor15End = actor15Object.xPos + 210;
	int yActor15End = actor15Object.yPos + 36;
	i=0;

	// this loop will draw actor 15, including the pixels, colors 
	for (int y = yActor15Start; y < yActor15End; y++)//36 is the image height
	{
		for (int x = xActor15Start; x < xActor15End; x++) //210 is image width
		{	
			actor->color = actor4Ptr[i]; 
				
			actor->xPos = x;
			actor->yPos = y;
	
			drawPlayer(actor);
			i++;
				
		}
	}


	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor1Object.xPos>=1024)
		actor1Object.xPos = 0;
	actor1Object.xPos+=5;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor2Object.xPos>=1024)
		actor2Object.xPos = 0;
	actor2Object.xPos+=5;
	
	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor3Object.xPos>=1024)
		actor3Object.xPos = 0;
	actor3Object.xPos+=5;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor4Object.xPos>=1024)
		actor4Object.xPos = 0;
	actor4Object.xPos+=8;
	
	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor5Object.xPos>=1024)
		actor5Object.xPos = 0;
	actor5Object.xPos+=8;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor6Object.xPos<=0)
		actor6Object.xPos = 1024;
	actor6Object.xPos-=6;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor7Object.xPos<=0)
		actor7Object.xPos = 1024;
	actor7Object.xPos-=8;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor8Object.xPos<=0)
		actor8Object.xPos = 1024;
	actor8Object.xPos-=8;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor9Object.xPos>=1024)
		actor9Object.xPos = 0;
	actor9Object.xPos+=4;
	
	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor10Object.xPos>=1024)
		actor10Object.xPos = 0;
	actor10Object.xPos+=4;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor11Object.xPos<=0)
		actor11Object.xPos = 1024;
	actor11Object.xPos-=3;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor12Object.xPos<=0)
		actor12Object.xPos = 1024;
	actor12Object.xPos-=3;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor13Object.xPos<=0)
		actor13Object.xPos = 1024;
	actor13Object.xPos-=3;
	
	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor14Object.xPos<=0)
		actor14Object.xPos = 1024;
	actor14Object.xPos-=2;

	// checking all the conditions for the actors' position, to reset it to 0 when need be
	if(actor15Object.xPos<=0)
		actor15Object.xPos = 1024;
	actor15Object.xPos-=2;



	


}

/* This functions will display all the moving objects */
void displayingMovingTruck(){
	Objects *truck;
	truck = malloc(sizeof(truck));
	int i = 0;

	// Initilizing the positions, start and end  position for truck 4
	int xTruck1Start, yTruck1Start, yTruck1End, xTruck1End;
	int xTruck2Start, yTruck2Start, yTruck2End, xTruck2End;
	xTruck1Start = truck1Object.xPos;
	yTruck1Start = truck1Object.yPos;
	xTruck1End = truck1Object.xPos + 90;
	yTruck1End = truck1Object.yPos + 36;

	short int *truckPtr = (short int*) Truck.pixel_data;

	// this loop will draw truck 1, including the pixels, colors 
	// 86 is the image height
	for (int y = yTruck1Start; y < yTruck1End; y++)
	{
			//86 is image width
			for (int x = xTruck1Start; x < xTruck1End; x++) 
			{	
				truck->color = truckPtr[i]; 
				
				truck->xPos = x;
				truck->yPos = y;
	
				drawPlayer(truck);
				i++;
				
			}
	}

	// Initilizing the positions, start and end  position for truck 2
	xTruck2Start = truck2Object.xPos;
	yTruck2Start = truck2Object.yPos;
	xTruck2End = truck2Object.xPos + 90;
	yTruck2End = truck2Object.yPos + 36;
	i=0;

	// this loop will draw truck 2, including the pixels, colors 
	// 86 is the image height
	for (int y = yTruck2Start; y < yTruck2End; y++)
	{
			//191 is image width
			for (int x = xTruck2Start; x < xTruck2End; x++) 
			{	
				truck->color = truckPtr[i]; 
				
				truck->xPos = x;
				truck->yPos = y;
	
				drawPlayer(truck);
				i++;
				
			}
	}

	// Initilizing the positions, start and end  position for truck 5
	int xTruck5Start, yTruck5Start, yTruck5End, xTruck5End;
	int xTruck6Start, yTruck6Start, yTruck6End, xTruck6End;
	xTruck5Start = truck5Object.xPos;
	yTruck5Start = truck5Object.yPos;
	xTruck5End = truck5Object.xPos + 90;
	yTruck5End = truck5Object.yPos + 36;
	i=0;

	// this loop will draw truck 5, including the pixels, colors
	// 86 is the image height
	for (int y = yTruck5Start; y < yTruck5End; y++)
	{
			//86 is image width
			for (int x = xTruck5Start; x < xTruck5End; x++) 
			{	
				truck->color = truckPtr[i]; 
				
				truck->xPos = x;
				truck->yPos = y;
	
				drawPlayer(truck);
				i++;
				
			}
	}
	// Initilizing the positions, start and end  position for truck 6
	xTruck6Start = truck6Object.xPos;
	yTruck6Start = truck6Object.yPos;
	xTruck6End = truck6Object.xPos + 90;
	yTruck6End = truck6Object.yPos + 36;
	i=0;

	// this loop will draw truck 6, including the pixels, colors
	// 86 is the image height
	for (int y = yTruck6Start; y < yTruck6End; y++)
	{
			//191 is image width
			for (int x = xTruck6Start; x < xTruck6End; x++) 
			{	
				truck->color = truckPtr[i]; 
				
				truck->xPos = x;
				truck->yPos = y;
	
				drawPlayer(truck);
				i++;
				
			}
	}

	
	Objects *truck2;
	truck2 = malloc(sizeof(truck2));

	short int *truck2Ptr = (short int*) Truck2.pixel_data;

	int xTruck4Start, yTruck4Start, yTruck4End, xTruck4End;

	// Initilizing the positions, start and end  position for truck 4
	xTruck4Start = truck4Object.xPos;
	yTruck4Start = truck4Object.yPos;
	xTruck4End = truck4Object.xPos + 90;
	yTruck4End = truck4Object.yPos + 36;
	i=0;

	// this loop will draw truck 4, including the pixels, colors
	// 36 is the image height
	for (int y = yTruck4Start; y < yTruck4End; y++)
	{
			//90 is image width
			for (int x = xTruck4Start; x < xTruck4End; x++) 
			{	
				truck2->color = truck2Ptr[i]; 
				
				truck2->xPos = x;
				truck2->yPos = y;
	
				drawPlayer(truck2);
				i++;
				
			}
	}



	// waiting 
	wait(30000);

	// checking all the conditions for the trucks' position, to reset it to 0 when need be
	if(truck1Object.xPos>=1024)
		truck1Object.xPos = 0;
	truck1Object.xPos+=3;

	// checking all the conditions for the trucks' position, to reset it to 0 when need be
	if(truck2Object.xPos>=1024)
		truck2Object.xPos = 0;
	truck2Object.xPos+=3;

	// checking all the conditions for the trucks' position, to reset it to 0 when need be
	if(truck4Object.xPos<=0)
		truck4Object.xPos = 1024;
	truck4Object.xPos-=7;

	// checking all the conditions for the trucks' position, to reset it to 0 when need be
	if(truck5Object.xPos>=1024)
		truck5Object.xPos = 0;
	truck5Object.xPos+=5;
	
	// checking all the conditions for the trucks' position, to reset it to 0 when need be
	if(truck6Object.xPos>=1024)
		truck6Object.xPos = 0;
	truck6Object.xPos+=5;




}

/* This function will be implementing all cars in motion on the screen */
void displayingMovingCar1(){

	// intializing the variables
	Objects *car1;
	car1 = malloc(sizeof(car1));
	int i = 0;	

	short int *car1Ptr = (short int*) Car1.pixel_data;
	
	// Initilizing the positions, start and end  position for car 1
	int yCar1End, xCar1End, yCar1Start, xCar1Start;
	xCar1Start = car1Object.xPos;
	yCar1Start = car1Object.yPos;
	xCar1End =  car1Object.xPos+46;
	yCar1End = car1Object.yPos + 36;

	// this loop will draw car 1, including the pixels, colors
	for (int y = yCar1Start; y < yCar1End; y++)//86 is the image height
		{
			for (int x = xCar1Start; x < xCar1End; x++) //86 is image width
			{	
				car1->color = car1Ptr[i]; 
				
				car1->xPos = x;
				car1->yPos = y;
	
				drawPlayer(car1);
				i++;
				
			}
		}


	// Initilizing the positions, start and end  position for car 3
	int yCar3End, xCar3End, yCar3Start, xCar3Start;
	xCar3Start = car3Object.xPos;
	yCar3Start = car3Object.yPos;
	xCar3End =  car3Object.xPos+46;
	yCar3End = car3Object.yPos + 36;
	i=0;

	//86 is the image height 
	// this loop will draw car 3, including the pixels, colors
	for (int y = yCar3Start; y < yCar3End; y++)
		{
			//86 is image width
			for (int x = xCar3Start; x < xCar3End; x++) 
			{	
				car1->color = car1Ptr[i]; 
				
				car1->xPos = x;
				car1->yPos = y;
	
				drawPlayer(car1);
				i++;
				
			}
		}

	Objects *car2;
	car2 = malloc(sizeof(car2));

	short int *car2Ptr = (short int*) Car2.pixel_data;

	// Initilizing the positions, start and end  position for car 4
	int yCar4End, xCar4End, yCar4Start, xCar4Start;
	xCar4Start = car4Object.xPos;
	yCar4Start = car4Object.yPos;
	xCar4End =  car4Object.xPos+39;
	yCar4End = car4Object.yPos + 36;
	i=0;

	//36 is the image height
	// this loop will draw car4 1, including the pixels, colors
	for (int y = yCar4Start; y < yCar4End; y++)//36 is the image height
	{
			//39 is image width
			for (int x = xCar4Start; x < xCar4End; x++) 
			{	
				car2->color = car2Ptr[i]; 
				
				car2->xPos = x;
				car2->yPos = y;
	
				drawPlayer(car2);
				i++;
				
			}
	}

	// Initilizing the positions, start and end  position for car 5
	int yCar5End, xCar5End, yCar5Start, xCar5Start;
	xCar5Start = car5Object.xPos;
	yCar5Start = car5Object.yPos;
	xCar5End =  car5Object.xPos+39;
	yCar5End = car5Object.yPos + 36;
	i=0;

	//86 is the image height
	// this loop will draw car 5, including the pixels, colors
	for (int y = yCar5Start; y < yCar5End; y++)
		{
			for (int x = xCar5Start; x < xCar5End; x++)
			{	
				car2->color = car2Ptr[i]; 
				
				car2->xPos = x;
				car2->yPos = y;
	
				drawPlayer(car2);
				i++;
				
			}
		}

	// Initilizing the positions, start and end  position for car 9
	int yCar9End, xCar9End, yCar9Start, xCar9Start;
	xCar9Start = car9Object.xPos;
	yCar9Start = car9Object.yPos;
	xCar9End =  car9Object.xPos+39;
	yCar9End = car9Object.yPos + 36;
	i=0;

	//86 is the image height
	// this loop will draw car 9, including the pixels, colors
	for (int y = yCar9Start; y < yCar9End; y++)
		{
			for (int x = xCar9Start; x < xCar9End; x++) //39 is image width
			{	
				car2->color = car2Ptr[i]; 
				
				car2->xPos = x;
				car2->yPos = y;
	
				drawPlayer(car2);
				i++;
				
			}
		}

	// Initilizing the positions, start and end  position for car 10
	int yCar10End, xCar10End, yCar10Start, xCar10Start;
	xCar10Start = car10Object.xPos;
	yCar10Start = car10Object.yPos;
	xCar10End =  car10Object.xPos+39;
	yCar10End = car10Object.yPos + 36;
	i=0;

	//86 is the image height
	// this loop will draw car 10, including the pixels, colors
	for (int y = yCar10Start; y < yCar10End; y++)
		{
			for (int x = xCar10Start; x < xCar10End; x++) //86 is image width
			{	
				car2->color = car2Ptr[i]; 
				
				car2->xPos = x;
				car2->yPos = y;
	
				drawPlayer(car2);
				i++;
				
			}
		}

	// Initilizing the positions, start and end  position for car 11
	int yCar11End, xCar11End, yCar11Start, xCar11Start;
	xCar11Start = car11Object.xPos;
	yCar11Start = car11Object.yPos;
	xCar11End =  car11Object.xPos+39;
	yCar11End = car11Object.yPos + 36;
	i=0;

	//86 is the image height
	// this loop will draw car 11, including the pixels, colors
	for (int y = yCar11Start; y < yCar11End; y++)
		{
			for (int x = xCar11Start; x < xCar11End; x++) //86 is image width
			{	
				car2->color = car2Ptr[i]; 
				
				car2->xPos = x;
				car2->yPos = y;
	
				drawPlayer(car2);
				i++;
				
			}
		}

	

	Objects *car3;
	car3 = malloc(sizeof(car3));

	short int *car3Ptr = (short int*) Car3.pixel_data;

	// Initilizing the positions, start and end  position for car 6
	int yCar6End, xCar6End, yCar6Start, xCar6Start;
	xCar6Start = car6Object.xPos;
	yCar6Start = car6Object.yPos;
	xCar6End =  car6Object.xPos+46;
	yCar6End = car6Object.yPos + 36;
	i=0;

	//86 is the image height
	// this loop will draw car 6, including the pixels, colors
	for (int y = yCar6Start; y < yCar6End; y++)
		{
			for (int x = xCar6Start; x < xCar6End; x++) //86 is image width
			{	
				car3->color = car3Ptr[i]; 
				
				car3->xPos = x;
				car3->yPos = y;
	
				drawPlayer(car3);
				i++;
				
			}
		}

	// Initilizing the positions, start and end  position for car 7
	int yCar7End, xCar7End, yCar7Start, xCar7Start;
	xCar7Start = car7Object.xPos;
	yCar7Start = car7Object.yPos;
	xCar7End =  car7Object.xPos+46;
	yCar7End = car7Object.yPos + 36;
	i=0;

	//86 is the image height
	// this loop will draw car 7, including the pixels, colors
	for (int y = yCar7Start; y < yCar7End; y++)
		{
			for (int x = xCar7Start; x < xCar7End; x++) //86 is image width
			{	
				car3->color = car3Ptr[i]; 
				
				car3->xPos = x;
				car3->yPos = y;
	
				drawPlayer(car3);
				i++;
				
			}
		}

	// Initilizing the positions, start and end  position for car 8
	int yCar8End, xCar8End, yCar8Start, xCar8Start;
	xCar8Start = car8Object.xPos;
	yCar8Start = car8Object.yPos;
	xCar8End =  car8Object.xPos+46;
	yCar8End = car8Object.yPos + 36;
	i=0;

	//86 is the image height
	//this loop will draw car 8, including the pixels, colors
	for (int y = yCar8Start; y < yCar8End; y++)
		{
			for (int x = xCar8Start; x < xCar8End; x++) //86 is image width
			{	
				car3->color = car3Ptr[i]; 
				
				car3->xPos = x;
				car3->yPos = y;
	
				drawPlayer(car3);
				i++;
				
			}
		}


	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car6Object.xPos>=1024)
		car6Object.xPos = 0;
	car6Object.xPos+=2;

	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car7Object.xPos>=1024)
		car7Object.xPos = 0;
	car7Object.xPos+=2;

	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car8Object.xPos>=1024)
		car8Object.xPos = 0;
	car8Object.xPos+=2;

	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car4Object.xPos<=0)
		car4Object.xPos = 1024;
	car4Object.xPos-=3;

	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car5Object.xPos<=0)
		car5Object.xPos = 1024;
	car5Object.xPos-=3;

	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car9Object.xPos<=0)	
		car9Object.xPos = 1024;
	car9Object.xPos-=2;

	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car10Object.xPos<=0)	
		car10Object.xPos = 1024;
	car10Object.xPos-=2;

	// checking all the conditions for the car's position, to reset it to 0 when need be	
	if(car11Object.xPos<=0)	
		car11Object.xPos = 1024;
	car11Object.xPos-=2;

	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car1Object.xPos>=1024)
		car1Object.xPos = 0;
	car1Object.xPos+=2;

	// checking all the conditions for the car's position, to reset it to 0 when need be
	if(car3Object.xPos>=1020)
		car3Object.xPos = 0;
	car3Object.xPos+=2;

}
	
/* implementing pthread for reading the SNES controlled and button pressed */
int threadReadingSnes(){
	void *pressed;

	pthread_t SNES;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&SNES, &attr, readingSnes, "0");
	pthread_join(SNES, &pressed);


	return (int) pressed;
}

/* this function will read the SNES as the user presses the buttons*/
/* @Param: ID */

void *readingSnes(void* ID){
unsigned int *GPIOaddr = getGPIOPtr();				//To get the pointer address
	wait(1000);
	int pressed;
	do{
		while(1)
		{	
			pressed = Read_SNES(GPIOaddr);
			if(pressed > 0&& pressed<13)
			{
				goto newLoop;
			}
		}
		
	newLoop:
		wait(200000);		//sleeping every 0.2 seconds inorder to read every button press as one input 				
		if(pressed > 0)
			break;
		//printf("\n\nPress the button: \n");
	}while(pressed>0 && pressed<=12); 
	//exit the pthread	
	pthread_exit((void *) pressed);
}

/* Draw a pixel */
/* @Param: Pixel*/
void drawPixel(Pixel *pixel){
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}


/* Draw a player */
/* @Param: player*/
void drawPlayer(Player *player){
	long int location =(player->xPos +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (player->yPos+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = player->color;
}



