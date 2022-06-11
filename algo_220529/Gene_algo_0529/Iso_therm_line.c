#include "Iso_therm_line.h"



double iso_therm_line(double u,double v,double X,double Y,double Z
                      ,double X_diff,double Y_diff,double Z_diff,double interval,
                      double uv_new[2],double Slope_const_array[2]){

    double m;

    double constant;


    double a=(X*Y_diff-X_diff*Y)+3*(Y_diff*Z-Y*Z_diff);
    //printf("a=%f\n",a);


    double b=2*(X_diff*Z-X*Z_diff)+10*(X_diff*Y-X*Y_diff);

    //printf("b=%f\n",b);

    m=-1.0/(a/b);

 // printf("m=%.12f\n\n",m);


    constant =v-(m*u);

    Slope_const_array[0]=m;
    Slope_const_array[1]=constant;

 // printf("const=%.12f\n\n",constant);

    v=m*(u+interval)+constant;
    uv_new[0]=u+interval;
    uv_new[1]=v;



}
