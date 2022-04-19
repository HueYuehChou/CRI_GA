#include"Spectrum_Equation.h"

double Spectrum_LED(double LED_wavelength,double LED_FWHM_L,double LED_FWHM_R,double Lambda){

   /* printf("LED_wavelength=%f\n",LED_wavelength);
    printf("LED_FWHM_L=%f\n",LED_FWHM_L);
    printf("LED_FWHM_R=%f\n",LED_FWHM_R);
    printf("Lambda=%f\n",Lambda);*/

    double a=2.0;
    double b=exp((LED_wavelength-Lambda)/LED_FWHM_L);
    double c=exp((Lambda-LED_wavelength)/LED_FWHM_R);
    double f=a/(b+c) ;

    //printf("f=%f\n",f);





return f;


}
double Single_spec_phosphors(double SL_wavelength ,double SL_FWHM,double lambda){


    double a=(SL_wavelength/lambda)*(SL_wavelength/lambda);
    double b=pow((lambda-SL_wavelength)/(SL_FWHM*lambda),2);
    double c=-b;
    double d=exp(c);
    double z=a*d ;

    //printf("f=%f\n",z);

    return z;

}

