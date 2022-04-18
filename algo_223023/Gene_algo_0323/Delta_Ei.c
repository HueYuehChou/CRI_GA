#include "Delta_Ei.h"
#include <math.h>

double Delta_Ei(double Uki,double Vki,double Wki,double Uri,double Vri,double Wri){


double a=(Uki-Uri)*(Uki-Uri)+(Vki-Vri)*(Vki-Vri)+(Wki-Wri)*(Wki-Wri);

double Ei=sqrt(a);


return Ei;



}
