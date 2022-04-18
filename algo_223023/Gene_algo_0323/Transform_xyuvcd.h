#ifndef _XYTOUV_H
#define _XYTOUV_H

int xytouv(double x,double y,double uv_array[2]);
int uvtoxy(double u,double v,double xy_new[2]);
int uvtocd(double u,double v,double cd_array[2]);
int cdtouv_prime(double ck,double dk,double cr,double dr,double crki,double drki,double uv_prime_array[2]);


#endif
