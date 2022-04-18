#include"Bluerate_APSL.h"
int Bluerate_APSL(double Tristimulus_temp_LED[3],double Tristimulus_temp_S[3],double Tristimulus_temp_L[3],double Illuminant_xy_array[2],double APSL_array[2])
{
    // Aps Apl




    double XYZ_LED,XYZ_PS,XYZ_PL,d,e,f,g,h,k;

    double xc,yc;

    XYZ_LED=Tristimulus_temp_LED[0]+Tristimulus_temp_LED[1]+Tristimulus_temp_LED[2];//X+Y+Z
    XYZ_PS=Tristimulus_temp_S[0]+Tristimulus_temp_S[1]+Tristimulus_temp_S[2];//X+Y+Z
    XYZ_PL=Tristimulus_temp_L[0]+Tristimulus_temp_L[1]+Tristimulus_temp_L[2];//X+Y+Z

    xc=Illuminant_xy_array[0];
    yc=Illuminant_xy_array[1];



    d=(Tristimulus_temp_LED[0]-(xc*XYZ_LED))*(yc*XYZ_PL-Tristimulus_temp_L[1]);

    e=(Tristimulus_temp_LED[1]-(yc*XYZ_LED))*(xc*(XYZ_PL)-Tristimulus_temp_L[1]);

    f=(xc*(XYZ_PS)-Tristimulus_temp_S[0])*(yc*(XYZ_PL)-Tristimulus_temp_L[1]);

    g=(xc*(XYZ_PL)-Tristimulus_temp_L[0])*(yc*(XYZ_PS)-Tristimulus_temp_S[1]);

    h=(Tristimulus_temp_LED[1]-(yc*(XYZ_LED)))*(xc*(XYZ_PS)-Tristimulus_temp_S[0]);

    k=(Tristimulus_temp_LED[0]-(xc*(XYZ_LED)))*(yc*(XYZ_PS)-Tristimulus_temp_S[1]);


    APSL_array[0]=(d-e)/(f-g);
    APSL_array[1]=(h-k)/(f-g);





}
