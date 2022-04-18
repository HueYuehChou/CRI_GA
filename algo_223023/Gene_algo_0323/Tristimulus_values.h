#ifndef _TRISTIMULUS_VALUES_H_
#define _TRISTIMULUS_VALUES_H_

double Spectrum2XYZ(int wavelength_interval,int data_length,int data_width,double CIE1931[data_length][data_width],double S[data_length],double tristimulus_temp[3]);
double Spectrum2XYZ_TCS(int wavelength_interval,int data_width ,int data_length,int TCS_width,double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double S[data_length],double Tristimulus_temp[3][TCS_width]);


#endif





