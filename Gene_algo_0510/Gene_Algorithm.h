#ifndef _GENE_ALGORITHM_H_
#define _GENE_ALGORITHM_H_


double Gene_Algorithm(int Lower_limit,int data_length,int data_width,int TCS_width,double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double Daylight_SPD_1nm[data_length][4]);
double Bubble_sort(int length,int width,double Array[length][width],double CRI_array[length]);
double Cross_over(double Parent1,double parent2,double iter,double Mutate);


#endif
