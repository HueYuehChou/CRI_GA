#include"S_total.h"
int S_total(int data_length ,double APSL_array[2],double S_LED[data_length], double  S_short[data_length], double S_Long[data_length],double S_total_array[data_length] ){

for(int k=0;k<data_length;k++){



              S_total_array[k]=S_LED[k]+APSL_array[0]*S_short[k]+APSL_array[1]*S_Long[k];

              //printf("%f\n",S_total_array[k]);


 }



}

