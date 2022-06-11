#ifndef _LM_ALGORITHM_H_
#define _LM_ALGORITHM_H_
double LM_Algorithm(double Array1[9],double Tc,double Tc_uv_Slope_const_array[5],int TCS_width,int Lower_limit, int wavelength_interval, int data_length, int data_width,double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double Daylight_SPD_1nm[data_length][4]);

#endif
