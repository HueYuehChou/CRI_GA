#ifndef _CRI_H_
#define _CRI_H_

double CRI_calculate(int Constrain_Flag[1],double Tc,double Tc_uv_Slope_const_array[5],double LED_wavelength,double LED_FWHM_L,double LED_FWHM_R,double Short_wavelength,double Short_FWHM,double Long_wavelength,double Long_FWHM, double uv_interval,int TCS_width,int lower_limit,int wavelength_interval,int data_length,int data_width,double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double Daylight_SPD_1nm[data_length][4]);

#endif
