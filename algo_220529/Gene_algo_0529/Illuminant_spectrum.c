#include "illuminant_spectrum.h"
#include <math.h>

double  Illuminant_Planck_spectrum(double Tc,double lambda){


    double c1= 3.74183e-16;
    double c2= 1.4388e-2;
    double Illuminant_spec;
    double a,b,c;




       a=lambda*1e-9*lambda*1e-9*lambda*1e-9*lambda*1e-9*lambda*1e-9;
       b=lambda*Tc*1e-9;
       c=exp(c2/b);
       // printf("a=%f\n",a);
        // printf("b=%f\n",b);

      // printf("c=%f\n",c);

        Illuminant_spec=(c1/a)/(c-1);

       //printf("illu=%f\n",Illuminant_spec);

        return Illuminant_spec;







}
double  Illuminant_Daylight_spectrum(double Tc,double S0,double S1,double S2){
    double xD;
    if(Tc<=7000){
    xD=(-4.0507E9)/(Tc*Tc*Tc)+(2.9678E6)/(Tc*Tc)+(0.09911E3)/(Tc)+0.244063;
    }
    else{
    xD=(-2.0064E9)/(Tc*Tc*Tc)+(1.9018E6)/(Tc*Tc)+(0.24748E3)/(Tc)+0.23704;
    }
  //  printf("xD=%f\n",xD);
    double yD=-3*xD*xD+2.873*xD-0.275;
 //    printf("yD=%f\n",yD);
    double M1=(-1.3515-1.7703*xD+5.9114*yD)/(0.0241+0.2562*xD-0.7341*yD);
 //    printf("M1=%f\n",M1);
    double M2=(0.03-31.4424*xD+30.0717*yD)/(0.0241+0.2562*xD-0.7341*yD);
  //   printf("M2=%f\n",M2);
    double S_Daylight=S0+M1*S1+M2*S2;


    return S_Daylight;
}

double  Illuminant_spectrum_differential(double Tc,double lambda){


    double c1= 3.7417449e-16;
    double c2= 1.4388e-2;
    double Illuminant_spec_diff;
    double a,b,c,d,e,f,g;


     // printf("lambda=%f\n",lambda);

       a=lambda*1e-9*lambda*1e-9*lambda*1e-9*lambda*1e-9*lambda*1e-9*lambda*1e-9;
       b=(c1*c2)/(Tc*Tc);
       c=lambda*Tc*1e-9;
       d=b/a;
       e=d*exp(c2/c);
       f=(exp(c2/c)-1)*(exp(c2/c)-1);

       // printf("a=%f\n",a);
        //printf("b=%f\n",b);
        //  printf("g=%f\n",g);
       // printf("d=%f\n",d);
        // printf("e=%f\n",e);
        //  printf("f=%f\n",f);

        Illuminant_spec_diff=(e/f);

       //printf("illu_diff=%f\n",Illuminant_spec_diff);

        return Illuminant_spec_diff;







}
