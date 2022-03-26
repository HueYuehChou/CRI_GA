#include"XYZ2xy.h"

int XYZ2xy(int data_width,int data_length,int chrosome,double tristimulus_array_LED[3][chrosome],double xy_array[2][chrosome] ){



    for(int i=0;i<chrosome;i++){

            xy_array[0][i]=tristimulus_array_LED[0][i]/(tristimulus_array_LED[0][i]+tristimulus_array_LED[1][i]+tristimulus_array_LED[2][i]);
            xy_array[1][i]=tristimulus_array_LED[1][i]/(tristimulus_array_LED[0][i]+tristimulus_array_LED[1][i]+tristimulus_array_LED[2][i]);


    }





}
