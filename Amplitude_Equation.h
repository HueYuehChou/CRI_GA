#include<math.h>
#include<time.h>
#include<iostream>
float ASL_array[2];




float Amp_LED(float params[], float lambda) // blue light S(lambda)
{
    float a,b,c;

    a=2;
    b=exp((params[0]-lambda)/params[1]);
    c=exp((lambda-params[0])/params[2]);
    float z;

            z=a/(b+c);
    return (z);
}
float Amp_SL(float params[] ,float lambda)// Long & short wavelength S(lambda)
{


    float a,b;
    float z;

    a=pow((params[0]/lambda),2);

    b=pow((lambda-params[0])/(lambda*params[1]),2);

    z=a*exp(-b);

    return(z);


}

float *Apsl(float xc,float yc,float XB,float YB,float ZB,float XS,float YS,float ZS,float XL,float YL,float ZL)
{
    // Aps Apl


    float a,b,c,d,e,f;



    a=(XB-(xc*(XB+YB+ZB)))*(yc*(XL+YL+ZL)-YL);

    b=(YB-(yc*(XB+YB+ZB)))*(xc*(XL+YL+ZL)-YL);

    c=(xc*(XS+YS+ZS)-XS)*(yc*(XL+YL+ZL)-YL);

    d=(xc*(XL+YL+ZL)-XL)*(yc*(XS+YS+ZS)-YS);

    e=(YB-(yc*(XB+YB+ZB)))*(xc*(XS+YS+ZS)-XS);

    f=(XB-(xc*(XB+YB+ZB)))*(yc*(XS+YS+ZS)-YS);





    float AS=(a-b)/(c-d);
    float AL=(e-f)/(c-d);


    ASL_array[0]=AS;
    ASL_array[1]=AL;
    //printf("AS=%f\n",ASL_array[0]);
    //printf("AL=%f\n",ASL_array[1]);

  return reinterpret_cast<float *>(ASL_array);


}


