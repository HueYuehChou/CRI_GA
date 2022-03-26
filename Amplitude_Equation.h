#ifndef _AMPLITUDE_EQUATION_H_
#define _AMPLITUDE_EQUATION_H_
int Amp_LED(int data_length,int chrosome,int data_width,int LED_genes, double LED_Population[data_length][LED_genes],double CIE1931[data_length][data_width],double S_LED[data_length][chrosome]);
int Amp_SL(int data_length,int chrosome,int data_width,int genes, double Population[data_length][genes],double CIE1931[data_length][data_width],double S_SL[data_length][chrosome]);


#endif
