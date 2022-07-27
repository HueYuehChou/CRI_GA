#include "Transform_xyuvcd.h"

int xytouv(double x,double y,double uv_array[2]){

    uv_array[0]=4.0*x/(-2.0*x+12.0*y+3.0);
    uv_array[1]=6.0*y/(-2.0*x+12.0*y+3.0);

}

int uvtoxy(double u,double v,double xy_new[2]){

     xy_new[0]=9.0*u/(6.0*u-24.0*v+12.0);

     xy_new[1]=6.0*v/(6.0*u-24.0*v+12.0);


}
int uvtocd(double u,double v,double cd_array[2]){

     cd_array[0]=(4.0-u-10.0*v)/v;

     cd_array[1]=(1.708*v+0.404-1.481*u)/v;


}
int cdtouv_prime(double ck,double dk,double cr,double dr,double crki,double drki,double uv_prime_array[2]){

    double a=cr*(crki/ck);

    double b=dr*(drki/dk);

    double c=(16.518+1.481*a-b);

    uv_prime_array[0]=(10.872+0.404*a-(4.0*b))/c;

    uv_prime_array[1]=5.52/c;



}

