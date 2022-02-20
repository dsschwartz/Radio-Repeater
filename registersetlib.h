/*
 * registersetlib.h
 *
 *  Created on: Feb 15, 2022
 *      Author: brycemccue
 */

#ifndef REGISTERSETLIB_H_
#define REGISTERSETLIB_H_

struct SD* arrangeforoutput( unsigned long out, unsigned char length);

struct SD* setregister0(unsigned char muxout,
                     unsigned char uartmode,
                     unsigned char txrx,
                     unsigned char integern,
                     unsigned int fractionaln);

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
                                    unsigned char rcounter);

struct SD* setregister2(  unsigned char rcosinealpha,
                                    unsigned char txdatainvert,
                                    unsigned int txfrequencydeviation,
                                    unsigned char poweramplifier,
                                    unsigned char pabias,
                                    unsigned char paramp,
                                    unsigned char paenable,
                                    unsigned char modulationscheme);

struct SD* setregister3(  unsigned char agcclkdivide,
                                    unsigned char seqclkdivide,
                                    unsigned char cdrclkdivide,
                                    unsigned char demodclkdivide,
                                    unsigned char bbosclkdivide);

struct SD* setregister4(  unsigned char ifbw,
                                    unsigned int postdemodbw,
                                    unsigned int discriminatorbw,
                                    unsigned char rxinvert,
                                    unsigned char dotproduct,
                                    unsigned char demodscheme);

struct SD* setregister5(  unsigned char irgainadjustupdown,
                                    unsigned char irgainadjustiq,
                                    unsigned char irgainadjustmag,
                                    unsigned char irphaseadjustdirection,
                                    unsigned char irphaseadjustmag,
                                    unsigned char iffilteradjust,
                                    unsigned int iffilterdivider,
                                    unsigned char ifcalcoarse);

#endif
