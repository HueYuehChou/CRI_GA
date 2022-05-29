#ifndef _matrix_random_H_
#define _matrix_random_H_

double genes_range(double gene_min,double gene_max);
double Matrix_randon(int chrosome,int data_width,int choice,double Population[chrosome][data_width]);
double Iso_therm_dis_rand(int Iso_threm_chrosome,double iso_therm_dis[Iso_threm_chrosome]);

double Matrix_randon_Long(int chrosome,int data_width,double S_Population[chrosome][data_width],double Population[chrosome][data_width]);
#endif



