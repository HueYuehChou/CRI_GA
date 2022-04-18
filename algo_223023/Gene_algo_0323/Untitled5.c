#include "xytouv.h"

int xytouv(double x,double y,double uv_array[2]){

    uv_array[0]=4*x/(-2*x+12y+3);
    uv_array[1]=6*y/(-2*x+12y+3);

}
