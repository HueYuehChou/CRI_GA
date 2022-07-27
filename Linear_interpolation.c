#include <math.h>
#include "Linear_interpolation.h"

double Linear_interpolation(double interval,double x1,double y1,double x2,double y2){
double m=(y2-y1)/(x2-x1);
double constant= y2-m*x2;
double y3=m*(x1+interval)+constant;

return y3;




}
