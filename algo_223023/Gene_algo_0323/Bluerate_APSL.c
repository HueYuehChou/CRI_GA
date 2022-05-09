#include"Bluerate_APSL.h"
#include <stdlib.h>
#include<math.h>
int Bluerate_APSL(double Tristimulus_LED[3],double Tristimulus_S[3],double Tristimulus_L[3],double Illuminant_xy_array[2],double APSL_array[2])
{
    // Aps Apl

    double xc,yc,XB,YB,ZB,XS,YS,ZS,XL,YL,ZL;
    xc=Illuminant_xy_array[0];
    yc=Illuminant_xy_array[1];
    XB=Tristimulus_LED[0];
    YB=Tristimulus_LED[1];
    ZB=Tristimulus_LED[2];
    XS=Tristimulus_S[0];
    YS=Tristimulus_S[1];
    ZS=Tristimulus_S[2];
    XL=Tristimulus_L[0];
    YL=Tristimulus_L[1];
    ZL=Tristimulus_L[2];

    double I,J,r,Alfa,Beta,TB,TS,TL,Lower;
    I=(YL*xc-XL*yc);
    J=(XL*YB-YL*XB);
    r=(YS*XL-YL*XS);
    Alfa=(xc*YS-yc*XS);
    Beta=(XS*YB-YS*XB);
    TB=XB+YB+ZB;
    TS=XS+YS+ZS;
    TL=XL+YL+ZL;
    Lower=r*(Alfa*TL-r-I*TS);






    APSL_array[0]=(r*(TB*I+J)+TL*(I*Beta-Alfa*J))/Lower;
    APSL_array[1]=(-r*(Alfa*TB+Beta)-TS*(I*Beta-Alfa*J))/Lower;





}

