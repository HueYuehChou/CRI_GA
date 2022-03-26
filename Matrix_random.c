#include "Matrix_random.h"
#include<time.h>
#include <stdlib.h>

double genes_range(double gene_min,double gene_max)
{


     double diff=gene_max-gene_min;

     return (diff*rand()/RAND_MAX + gene_min); // feedback random values in interval between range.


}


int Matrix_randon(int chrosome,int data_width,int choice,double Population[chrosome][data_width]){

int i,j;

if(choice==0){

   double LED_wavelength_min=430, LED_wavelength_max=460; // Blue light LED wavelength range
   double Halfwidth_LED_min=1;

for(int i=0;i<data_width;i++){
        for(int j=0;j<chrosome;j++){
                if(i==0)// Blue light LED wavelength
                Population[j][i] = genes_range(LED_wavelength_min,LED_wavelength_max);
                else if(i==1) // Right FWHM
                Population[j][i] = genes_range(Halfwidth_LED_min,LED_wavelength_max-LED_wavelength_min);
                else         //Left FWHM
                Population[j][i] = genes_range(Halfwidth_LED_min,LED_wavelength_max-LED_wavelength_min-Population[j][1]);
        }
    }
}
else if (choice==1)
{
    double S_wavelength_min=560, S_wavelength_max=639;  // YAG short wavelength range
    double Halfwidth_S_min=1;
        for(i=0;i<data_width;i++){
        for(j=0;j<chrosome;j++){
               if(i==0) // YAG short wavelength
                Population[j][i] = genes_range(S_wavelength_min,S_wavelength_max);
                else  //FWHM
                Population[j][i] = genes_range(Halfwidth_S_min,S_wavelength_max-S_wavelength_min);

}
}

}
else{
    double L_wavelength_min=640, L_wavelength_max=750;  // YAG long wavelength range
    double Halfwidth_L_min=1;
    for(i=0;i<data_width;i++){
        for(j=0;j<chrosome;j++){
                if(i==0)// YAG long wavelength
                Population[j][i] = genes_range(L_wavelength_min,L_wavelength_max);
                else // FWHM
                Population[j][i] = genes_range(Halfwidth_L_min,L_wavelength_max-L_wavelength_min);

}
    }
    }
}
