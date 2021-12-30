#include "utils.h"
#include <MK64F12.h>

int buttonPressed = 0;
long timer = 0;

//Initialize the ports to the SW3 button
void init_Button(void)   
{  
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; //Enable A Clock

	PORTA_PCR4 = 0x90100; //Button SW3

	GPIOA_PDDR |= (0 << 4); //SW3 connected to A4
	
	NVIC_EnableIRQ(PORTA_IRQn); //Enable interrupt handler for SW3
	} 

//Interrupt handler for when the button is pressed
void PORTA_IRQHandler(void){
	__disable_irq();
	PORTA_ISFR = PORT_ISFR_ISF(0x10);
	PORTA->PCR[24] = 1;
	buttonPressed = 1; //Interrupt occured, so button was pressed, and we can exit the timer loop
	__enable_irq();
}

//Count how long it takes for the player to react
void clickWait(){
		while (buttonPressed == 0) //Loop until button is pressed, triggering a interrupt and changing the value of buttonPressed
		{
			timer++;
		}
		buttonPressed = 0; //Reset pressed value before exiting
}


//Execution method Main
int main(void) {	
	//Init button and LEDs
	init_Button();
	LED_Initialize();

	//Set to white to begin, waiting to confirm p1 is ready, and delay for a bit to prevent rapid clicking
	LEDBlue_Toggle();
	LEDRed_Toggle();
	LEDGreen_Toggle();
	for (int i = 0; i < 2; i++)
	{
	delay();
	}
	buttonPressed = 0;	//Reset button press in case it was clicked before light turned green
	clickWait();

	//Red LED on, prepare to react
	LEDGreen_Toggle();
	LEDBlue_Toggle();
	for (int i = 0; i < 25; i++)
	{
		delay();
	}

	//Green LED on, p1 react now
	LEDRed_Toggle();		
	LEDGreen_Toggle();
	timer = 0;					//Save the number of times clickWait() executed
	buttonPressed = 0;	//Reset button press in case it was clicked before light turned green, and to prevent holding down the button/cheating
  clickWait();
	long p1T = timer;
	LEDGreen_Toggle();
	
	
	//Yellow light to indicate intermission/pass the board
	LEDRed_Toggle();
	LEDGreen_Toggle();
	for (int i = 0; i < 15; i++)
	{
	delay();
	}

	//Set to white again when done, waiting for p2 to confirm they are ready
	LEDBlue_Toggle();
	for (int i = 0; i < 2; i++)
	{
	delay();
	}
	buttonPressed = 0;	//Reset button press in case it was clicked before light turned green
	clickWait();
	
	//Blue LED on, prepare to react
	LEDRed_Toggle();
	LEDGreen_Toggle();
	for (int i = 0; i < 25; i++)
	{
		delay();
	}
	
	//Green LED on, p2 react now
	LEDBlue_Toggle();
	LEDGreen_Toggle();
	timer = 0;
	buttonPressed = 0;	//Reset button press in case it was clicked before light turned green, and to prevent holding down the button/cheating
  clickWait();				//Save the number of time clickWait() executed
	long p2T = timer;
	LEDGreen_Toggle();
	
	//Blink the winners color rapidly forever, and if its a tie alternate the two colors
	if (p1T > p2T)
	{
		//p1 had a greater time, so blink p2 as winner
			while(1)
			{
				LEDBlue_Toggle();
				delay();
			}
	}
	else if (p1T < p2T)
	{
		//p2 had a greater time, so blink p1 as winner
			while(1)
			{
				LEDRed_Toggle();
				delay();
			}
	}
	else if (p1T == p2T)
	{
		//same times, so alternate red and blue
			while(1)
			{
				LEDRed_Toggle();
				delay();
				LEDRed_Toggle();
				LEDBlue_Toggle();
				delay();
				LEDBlue_Toggle();
			}
	}
	while (1) //Extra while loop to run forever just incase
	{
	}
}
