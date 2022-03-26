#ifndef _TRISTIMULUS_VALUES_H_
#define _TRISTIMULUS_VALUES_H_

double Spectrum2XYZ(int chrosome,int wavelength_interval,int data_length,int data_width,double CIE1931[data_length][data_width],double S[data_length][chrosome],double tristimulus_array[3][chrosome]);


#endif





