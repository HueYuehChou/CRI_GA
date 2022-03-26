#include"Amplitude_Equation.h"
int Amp_LED(int data_length,int chrosome,int data_width,int LED_genes, double LED_Population[data_length][LED_genes],double CIE1931[data_length][data_width],double S_LED[data_length][chrosome]) // blue light S(lambda)
{
    double a,b,c;

          for(int i=0;i< chrosome;i++){
            for(int j=0;j<data_length;j++){


    a=2;
    b=exp((LED_Population[i][0]-CIE1931[j][0])/LED_Population[i][1]);
    c=exp((CIE1931[j][0]-LED_Population[i][0])/LED_Population[i][2]);

    S_LED[j][i]=a/(b+c);

            }
          }


}
int Amp_SL(int data_length,int chrosome,int data_width,int genes, double Population[data_length][genes],double CIE1931[data_length][data_width],double S_SL[data_length][chrosome])// Long & short wavelength S(lambda)
{


    double a,b;

     for(int i=0;i< chrosome;i++){
            for(int j=0;j<data_length;j++){


    a=(Population[i][0]/CIE1931[j][0])*(Population[i][0]/CIE1931[j][0]);



    b=-((CIE1931[j][0]-Population[i][0])*(CIE1931[j][0]-Population[i][0]))/((CIE1931[j][0]*Population[i][1])*(CIE1931[j][0]*Population[i][1]));


    S_SL[j][i]=a*exp(b);
            }

            }


}

float Apsl(float xc,float yc,float XB,float YB,float ZB,float XS,float YS,float ZS,float XL,float YL,float ZL,float *ASL_array[2])
{
    // Aps Apl



    double a,b,c,d,e,f;



    a=(XB-(xc*(XB+YB+ZB)))*(yc*(XL+YL+ZL)-YL);

    b=(YB-(yc*(XB+YB+ZB)))*(xc*(XL+YL+ZL)-YL);

    c=(xc*(XS+YS+ZS)-XS)*(yc*(XL+YL+ZL)-YL);

    d=(xc*(XL+YL+ZL)-XL)*(yc*(XS+YS+ZS)-YS);

    e=(YB-(yc*(XB+YB+ZB)))*(xc*(XS+YS+ZS)-XS);

    f=(XB-(xc*(XB+YB+ZB)))*(yc*(XS+YS+ZS)-YS);







     *ASL_array[0]=(a-b)/(c-d);
     *ASL_array[1]=(e-f)/(c-d);




}


