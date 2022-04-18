#include "Matrix_random.h"
#include<time.h>
#include <stdlib.h>


double genes_range(double gene_min,double gene_max)
{


     double diff=gene_max-gene_min;

     return (diff*rand()/RAND_MAX + gene_min); // feedback random values in interval between range.


}


double Matrix_randon(int chrosome,int data_width,int choice,double Population[chrosome][data_width]){

if(choice==0){

   double LED_wavelength_min=445, LED_wavelength_max=455; // Blue light LED wavelength range


for(int i=0;i<data_width;i++){
        for(int j=0;j<chrosome;j++){
                if(i==0)// Blue light LED wavelength
                Population[j][i] = genes_range(LED_wavelength_min,LED_wavelength_max);
                else if(i==1) // Right FWHM
                Population[j][i] = genes_range(6,11);
                else         //Left FWHM
                Population[j][i] = genes_range(8,16);
        }
    }
}
else
{
    double S_wavelength_min=520, S_wavelength_max=570;  // YAG short wavelength range

        for(int i=0;i<data_width;i++){
        for(int j=0;j<chrosome;j++){
               if(i==0) // YAG short wavelength
                Population[j][i] = genes_range(S_wavelength_min,S_wavelength_max);
                else  //FWHM
                Population[j][i] = genes_range(0.04,0.16);

}
}

}

}
double Matrix_randon_Long(int chrosome,int data_width,double S_Population[chrosome][data_width],double Population[chrosome][data_width]){



    for(int i=0;i<data_width;i++){
        for(int j=0;j<chrosome;j++){
                if(i==0){  // YAG long wavelength
                Population[j][i] =genes_range(S_Population[j][i]/(1-(0.0001)*S_Population[j][i]),S_Population[j][i]/(1-(0.0003102)*S_Population[j][i]));

                }
                else // FWHM
                Population[j][i] = genes_range(0.09,0.14);

}
    }



}


double Iso_therm_dis_rand(int Iso_threm_chrosome,double iso_therm_dis[Iso_threm_chrosome]){

    for(int i=0;i<Iso_threm_chrosome;i++)

    iso_therm_dis[i]=genes_range(-0.0005,0.0005);

}
