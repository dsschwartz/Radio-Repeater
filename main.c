#include <msp430.h>
#include "serialiolib.h"

/**
 * blink.c
 */
int main(void) {

    UCSCTL1 = DCORSEL_5;

	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer

	__enable_interrupt();

	SD *sendDataPtr;
	sendDataPtr = allocRegister();
	sendDataPtr->data = 0;
	sendDataPtr->size = 0;
	int test = 0;

    /*
	sendDataPtr->data = 0x10000081;
	sendDataPtr->size = 32;

	serialSendData(BIT5, // data
	               BIT4, // clock
	               1000, sendDataPtr);
	*/

	test = serialReceiveData(BIT5, // data
	                      BIT4, // clock
	                      BIT3, // SLE
	                      sendDataPtr);
	if (sendDataPtr->size == 32) {
	    return 0;
	}
	for(;;); // End spin
}
