#ifndef _ILLUMINANT_SPECTRUM_H
#define _ILLUMINANT_SPECTRUM_H


double Illuminant_Planck_spectrum(double Tc,double lambda);
double  Illuminant_Daylight_spectrum(double Tc,double S0,double S1,double S2);
double Illuminant_spectrum_differential(double Tc,double lambda);
#endif
