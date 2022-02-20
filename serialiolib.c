/*
 * serialiolib.c
 *
 *  Created on: Nov 30, 2021
 *      Author: brycemccue
 */

#include <stdlib.h>
#include <msp430.h>
#include "serialiolib.h"

// Allocates memory for the output data structure
// returns pointer to said memory
SD* allocRegister() {
    return (SD *) malloc(48);
}

// Init function for the data pins
// Pins have to be in pin bus 1
void initPinsOutput(char pin) {
    P1SEL &= (~(pin)); // selects the pins as gpio
    P1DIR |= (pin); // sets them to output
    P1OUT &= 0x0; // Zero output register
}

// Init function for the clock
void initClkOutput(int dataRate) {
    // Init Globals
    clkState = 0;
    cycles = 0;

    // init vars
    //int rate = dataRate;

    //Timer1_A3 Configuration
    TA0CCR0 = dataRate; //set counter
    TA0CCTL0 = CCIE; //Enable interrupt for CCR0.
    TA0CTL = TASSEL_2 + ID_0 + MC_1; //Select SMCLK, SMCLK/1, Up Mode
}

// Starts the timer
void startTimer(int dataRate) {
    //TA0CCR0 = rate;
}

// Stops the timer
void stopTimer() {
    TA0CCTL0 = ~CCIE;
}

//Timer ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A_ISR(void)
{
    clkState = ~clkState; // Change clock state
    if(clkState == 0) cycles++; //Increment cycles
}

// Sends data over Serial connection
int serialSendData(char dataPin, char clkPin, unsigned long dataRate, SD* data) {
    // init the pins
    initPinsOutput(dataPin);
    initPinsOutput(clkPin);

    // init the Timer
    initClkOutput(dataRate);

    // Loops
    while(1) {
        switch(clkState) {
            case 0 : // When the clock is low
                P1OUT &= ~clkPin; // Set clock low
                switch(data->data & (0x80000000 >> cycles)) { // figure out what bit to send
                    case 0 : P1OUT &= ~dataPin; break;// sending a 0
                    default : P1OUT |= dataPin; // sending a 1
                }
            break;
            default : P1OUT |= clkPin; // when the clock is high and set clock high
        }
        while((P1OUT & clkPin) == clkState) { // wait for clock state to change
            switch(data->size - cycles) {
                case 0 :
                    stopTimer(); // Stops the clock
                    return 1; // ends the function
                default: break;
            }
        }
    }
}

// Init input pins
// Has to be in bus two
void initPinsInput(char pin) {
    P2SEL &= (~(pin)); // selects the pins as gpio
    P2DIR &= ~(pin); // sets them to input
    P2REN |= pin; // enables pull up/down resistor
    P2OUT &= ~pin; // makes it a pull down
}

// Receives the incoming data
int serialReceiveData(char dataPin, char clkPin, char slePin, SD* data) {
    //Init Input Pins
    initPinsInput(dataPin);
    initPinsInput(clkPin);
    initPinsInput(slePin);

    // Init Variables
    cycles = 0;
    data->data = 0x0;
    data->size = 0x0;

    // Main loop
    while(1) {
                if(checkForLatch(slePin) == 1) { // checks if data is done sending
                    data->size = cycles;
                    return 1;
                }
                if ((P2IN & clkPin) == clkPin) { // check if the clock is one
                    switch(P2IN & dataPin) {
                        case 0: break; // Data var is zero'ed. if the sent bit is a zero, do nothing
                        default: data->data |= (0x80000000 >> (cycles)); // Set the data bit to corresponding 1
                    }
                    cycles++; // Increment the clock cycles
                    while((P2IN & clkPin) == clkPin);
                }
    }

}

// Latches the outgoing data
void latchTransmit(char slePin) {
    // init the pins
    initPinsOutput(slePin);

    // Turns on the sle pin
    P1OUT |= slePin;
}

// resets the latch
void endLatch(char slePin) {
    // Turns on the sle pin
    P1OUT &= ~slePin;
}


// check for receiving latch returns 1 if the latched
int checkForLatch(char slePin) {
    switch(P2IN & slePin) {
        case 0: return 0; // If the pin is not on it is zero
        default: return 1; // If the pin is on it is some non-zero value
    }
}

// Enables chip
void enableChip(char cePin) {
    // Init Pins
    initPinsOutput(cePin);

    // Enable chip (enabled when low)
    P1OUT &= ~cePin;
}

// Disables chip
void disableChip(char cePin) {
    // Init Pins
    initPinsOutput(cePin);

    // disable chip (disabled when low)
    P1OUT |= cePin;
}


