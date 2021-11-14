/*
 * Anay Bhutoria 30066860
 * Suvrat Kumra  30089629
*/

//This program returns the button pressed on the SNES controller, program will work until START button is pressed.

#include<wiringPi.h>
#include<unistd.h>
#include "initGPIO.h"
#include<stdio.h>
	
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

/*
 * This function is used to print the button that has been pressed
 */
void Print_Message(int pressed){
	if(pressed == 1){ //displaying outputs depending on the button pressed, if start is pressed then exit
		printf("\nYou Pressed button B...");
	}else if(pressed == 2){
		printf("\nYou Pressed button Y...");
	}else if(pressed == 3){
		printf("\nYou Pressed button Select...");
	}else if (pressed == 4){
		printf("\nYou Pressed button Start, exiting the program\n");
	}else if(pressed == 5){
		printf("\nYou Pressed button Joy-pad UP...");
	}else if(pressed == 6){
		printf("\nYou Pressed button Joy-pad DOWN...");
	}else if(pressed == 7){
		printf("\nYou Pressed button Joy-pad LEFT...");
	}else if(pressed == 8){
		printf("\nYou Pressed button Joy-pad RIGHT...");
	}else if(pressed == 9){
		printf("\nYou Pressed button A...");
	}else if(pressed == 10){
		printf("\nYou Pressed button X...");
	}else if(pressed == 11){
		printf("\nYou Pressed button Left...");
	}else{
		printf("\nYou Pressed button Right...");
	}
}

/*This is the main function where the program runs
 */
int use(){
	unsigned int *GPIOaddr = getGPIOPtr();				//To get the pointer address

	printf("\nCreated By: ANAY BHUTORIA AND SUVRAT KUMRA"); 

	//printf("\nPress a button...\n");
	int pressed;
	do{
		while(1){	
			pressed = Read_SNES(GPIOaddr);
			if(pressed > 0){		//4 for the start button on SNES remote	
				break;
			}
		}		
		wait(200000);		//sleeping every 0.2 seconds inorder to read every button press as one input 				
		Print_Message(pressed); // print which button was pressed
		if(pressed > 0)
			break;
		printf("\n\nPress the button: \n");
	}while(pressed!=4);
	return pressed;
}
