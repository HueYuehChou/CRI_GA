#include "uv_i_toUVW.h"

#include <math.h>
double uv_i_toUVW(double Yrk,double Yrk_i,double u,double v,double u_rki,double v_rki,double UVW_array[3]){

double Y=100.0;
double Yi=(Yrk_i/Yrk)*Y;

double a=1.0/3.0;

double b= pow(Yi,a);


UVW_array[2]=25*b-17;
UVW_array[0]=13*UVW_array[2]*(u-u_rki);
UVW_array[1]=13*UVW_array[2]*(v-v_rki);






}
