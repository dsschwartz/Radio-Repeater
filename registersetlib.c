/*
 * registersetlib.c
 *
 *  Created on: Feb 15, 2022
 *      Author: brycemccue
 */

#include <stdio.h>
#include <stdlib.h>
#include "serialiolib.h"
#include "registersetlib.h"

// takes the register and register length and arranges an output
// pointer for return
struct SD* arrangeforoutput( unsigned long out, unsigned char length) {
    // Arrange the pointers for output
    SD* output;

    // Set the return pointer to the struct pointer
    output->data = out;
    output->size = length;

    // return the pointer
    return output;
}

// Takes the settings for the 0 register and returns a pointer
// to be sent to the adf7021
struct SD* setregister0(  unsigned char muxout,
                                    unsigned char uartmode,
                                    unsigned char txrx,
                                    unsigned char integern,
                                    unsigned int fractionaln) {

    // Moves the values to the appropriate
    // places for the 0 register
    unsigned long out = muxout << 29 |
                        uartmode << 28 |
                        txrx << 27 |
                        integern << 19 |
                        fractionaln << 4 |
                        0x00;

    // Arrange data for pointer return
    return arrangeforoutput(out, 32);
}

struct SD* setregister1(  unsigned char vcoinductor,
                                    unsigned char vcoadjust,
                                    unsigned char vcobias,
                                    unsigned char rfdividebytwo,
                                    unsigned char vcoenable,
                                    unsigned char cpcurrent,
                                    unsigned char xtalbias,
                                    unsigned char xoscenable,
                                    unsigned char xtaldoubler,
                                    unsigned char clkoutdivide,
                                    unsigned char rcounter) {

    // Moves the values to the appropriate
    // places for the 1 register
    unsigned long out = vcoinductor << 25 |
                        vcoadjust << 23 |
                        vcobias << 19 |
                        rfdividebytwo << 18 |
                        vcoenable << 17 |
                        cpcurrent << 15 |
                        xtalbias << 13 |
                        xoscenable << 12 |
                        xtaldoubler << 11 |
                        clkoutdivide << 7 |
                        rcounter << 4 |
                        0x01;

    // Arrange data for pointer return
    // moves the 26 bit register so the msb is the msb
    // of the 32 bit long int
    return arrangeforoutput(out << 6, 25);
}

struct SD* setregister2(  unsigned char rcosinealpha,
                                    unsigned char txdatainvert,
                                    unsigned int txfrequencydeviation,
                                    unsigned char poweramplifier,
                                    unsigned char pabias,
                                    unsigned char paramp,
                                    unsigned char paenable,
                                    unsigned char modulationscheme) {

    // Moves the values to the appropriate
    // places for the 2 register
    unsigned long out = rcosinealpha << 30 |
                        txdatainvert << 28 |
                        txfrequencydeviation << 19 |
                        poweramplifier << 13 |
                        pabias << 11 |
                        paramp << 8 |
                        paenable << 7 |
                        modulationscheme << 4 |
                        0x02;

    // Arrange data for pointer return
    // moves the 31 bit register so the msb is the msb
    // of the 32 bit long int
    return arrangeforoutput(out << 1, 31);
}

struct SD* setregister3(  unsigned char agcclkdivide,
                                    unsigned char seqclkdivide,
                                    unsigned char cdrclkdivide,
                                    unsigned char demodclkdivide,
                                    unsigned char bbosclkdivide) {

    // Moves the values to the appropriate
    // places for the 3 register
    unsigned long out = agcclkdivide << 26 |
                        seqclkdivide << 18 |
                        cdrclkdivide << 10 |
                        demodclkdivide << 6 |
                        bbosclkdivide << 4 |
                        0x03;

    // Arrange data for pointer return
    return arrangeforoutput(out, 32);
}

struct SD* setregister4(  unsigned char ifbw,
                                    unsigned int postdemodbw,
                                    unsigned int discriminatorbw,
                                    unsigned char rxinvert,
                                    unsigned char dotproduct,
                                    unsigned char demodscheme) {

    // Moves the values to the appropriate
    // places for the 4 register
    unsigned long out = ifbw << 30 |
                        postdemodbw << 20 |
                        discriminatorbw << 10 |
                        rxinvert << 8 |
                        dotproduct << 7 |
                        demodscheme << 4 |
                        0x04;

    // Arrange data for pointer return
    return arrangeforoutput(out, 32);
}

struct SD* setregister5(  unsigned char irgainadjustupdown,
                                    unsigned char irgainadjustiq,
                                    unsigned char irgainadjustmag,
                                    unsigned char irphaseadjustdirection,
                                    unsigned char irphaseadjustmag,
                                    unsigned char iffilteradjust,
                                    unsigned int iffilterdivider,
                                    unsigned char ifcalcoarse) {

    // Moves the values to the appropriate
    // places for the 5 register
    unsigned long out = irgainadjustupdown << 31 |
                        irgainadjustiq << 30 |
                        irgainadjustmag << 25 |
                        irphaseadjustdirection << 24 |
                        irphaseadjustmag << 20 |
                        iffilteradjust << 14 |
                        iffilterdivider << 5 |
                        ifcalcoarse << 4 |
                        0x05;

    // Arrange data for pointer return
    return arrangeforoutput(out, 32);
}



