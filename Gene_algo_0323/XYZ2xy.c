#include"XYZ2xy.h"

int XYZ2xy(double tristimulus_array[3],double xy_array[2]){




            xy_array[0]=tristimulus_array[0]/(tristimulus_array[0]+tristimulus_array[1]+tristimulus_array[2]);
            xy_array[1]=tristimulus_array[1]/(tristimulus_array[0]+tristimulus_array[1]+tristimulus_array[2]);




}
