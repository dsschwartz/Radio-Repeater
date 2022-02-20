/*
 * serialiolib.h
 *
 *  Created on: Nov 30, 2021
 *      Author: brycemccue
 */

#ifndef SERIALIOLIB_H_
#define SERIALIOLIB_H_

// Global for the clock state and cycles
char clkState;
unsigned int cycles;

// Structure for the data files
typedef struct serialData {
    unsigned long int data;
    unsigned int size;
} SD;

// Allocates memory for the output data structure
SD* allocRegister();

// Initialization functions for the pins and the clk timer
// Pins have to be in pin bus 1
void initPinsOutput(char pin);

// Enables the clock output and starts timer
void initClkOutput();

// Starts clock
void startTimer(int dataRate);

// Stops the clock
void stopTimer();

// Sends data over the data and clock pins at the datarate
int serialSendData(char dataPin, char clkPin, unsigned long dataRate, SD* data);

// Receives the incoming data
int serialReceiveData(char dataPin, char clkPin, char slePin, SD* data);

// Latches the outgoing data
void latchTransmit(char slePin);

// Resets the latch
void endLatch(char slePin);

// check for receiving latch returns 1 if the latched
int checkForLatch(char slePin);

// Init input pins
// Has to be in bus two
void initPinsInput(char pin);

// Enables chip
void enableChip(char cePin);

// Disables chip
void disableChip(char cePin);


#endif /* SERIALIOLIB_H_ */
