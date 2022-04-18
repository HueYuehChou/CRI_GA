#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include"CRI.h"
#include"Gene_Algorithm.h"
#include "Matrix_random.h"
#include "Transform_xyuvcd.h"


double Genes_Algorithm(int data_length,int data_width,int wavelength_interval,int TCS_width,double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double Daylight_SPD_1nm[data_length][4]) {
for(double  therm=0;therm<1.0;therm+=1.0){

        double Tc=4000+100.0*therm;

    srand(time(NULL));

    int LED_genes=3,s_genes=2, L_genes=2;
    int chrosome=1,Genes_number=8;
    double Tc_uv_Slope_const_array[5],Result[chrosome][9];

    double LED_Population[chrosome][LED_genes],S_Population[chrosome][s_genes],L_Population[chrosome][L_genes],Iso_therm_dis[chrosome];

    Matrix_randon(chrosome,LED_genes,0,LED_Population);
    Matrix_randon(chrosome,s_genes,1,S_Population);

    Matrix_randon_Long(chrosome,L_genes,S_Population,L_Population);

    Iso_therm_dis_rand(chrosome,Iso_therm_dis);

    double S_LED[data_length],S_short[data_length],S_Long[data_length];
    double CRI,CRI_array[chrosome],Genes[chrosome][8];


for(int i=0;i<chrosome;i++){


   //printf("------------------------------------------------------------------------------------------------------------------\n");






  /* printf("Wavelength_LED = %f\t",LED_Population[i][0]);
   printf("FWHM_L  = %f\t",LED_Population[i][1]);
   printf("FWHM_R  = %f\n\n",LED_Population[i][2]);


   printf("Wavelength_s   = %f\t",S_Population[i][0]);
   printf("FWHM_s  = %f\n\n",S_Population[i][1]);


   printf("Wavelength_L   = %f\t",L_Population[i][0]);
   printf("FWHM_L  = %f\n\n",L_Population[i][1]);

   printf("Iso_threm_dis  = %f\n\n",Iso_therm_dis[j]);*/


   Genes[i][0]=LED_Population[i][0];
   Genes[i][1]=LED_Population[i][1];
   Genes[i][2]=LED_Population[i][2];
   Genes[i][3]=S_Population[i][0];
   Genes[i][4]=S_Population[i][1];
   Genes[i][5]=L_Population[i][0];
   Genes[i][6]=L_Population[i][1];
   Genes[i][7]=Iso_therm_dis[i];

   //Genes[j][7]=0;

   CRI_array[i]=CRI_calculate(Tc,Tc_uv_Slope_const_array,Genes[i][0],Genes[i][1],Genes[i][2],Genes[i][3],Genes[i][4],Genes[i][5],Genes[i][6],Genes[i][7], TCS_width, wavelength_interval, data_length, data_width, CIE1931, TCS,Daylight_SPD_1nm, CRI);
}
  Bubble_sort(chrosome,Genes_number,Genes,CRI_array);



  /* printf("Wavelength_LED = %f\t",Genes[0][0]);
   printf("FWHM_L  = %f\t",Genes[0][1]);
   printf("FWHM_R  = %f\n\n",Genes[0][2]);


   printf("Wavelength_s   = %f\t",Genes[0][3]);
   printf("FWHM_s  = %f\n\n",Genes[0][4]);


   printf("Wavelength_L   = %f\t",Genes[0][5]);
   printf("FWHM_L  = %f\n\n",Genes[0][6]);
   printf("Iso_threm_dis  = %f\n\n",Genes[0][7]);
   printf("Best CRI= %f\n\n",CRI_array[0]);*/
for(int i=0;i<chrosome;i++){
   for(int k=0;k<8;k++){
   Result[i][k]=Genes[i][k];
   }
   Result[i][8]=CRI_array[i];
}

  /* printf("Wavelength_LED = %f\t",Best_result[i][0]);
   printf("FWHM_L  = %f\t",Best_result[i][1]);
   printf("FWHM_R  = %f\n\n",Best_result[i][2]);


   printf("Wavelength_s   = %f\t",Best_result[i][3]);
   printf("FWHM_s  = %f\n\n",Best_result[i][4]);



   printf("Wavelength_L   = %f\t",Best_result[i][5]);
   printf("FWHM_L  = %f\n\n",Best_result[i][6]);

   printf("Iso_threm_dis  = %f\n\n",Best_result[i][7]);

   printf("Best CRI= %f\n\n",Best_result[i][8]);*/





   // printf("------------------------------------------------------------------------------------------------------------------\n");


   printf("Tc = %f\n\n",Tc_uv_Slope_const_array[0]);
   printf("Original_u  = %.12f\n\n",Tc_uv_Slope_const_array[1]);
   printf("Original_v  = %.12f\n\n",Tc_uv_Slope_const_array[2]);
   printf("Slope_iostherm  = %.12f\n\n",Tc_uv_Slope_const_array[3]);
   printf("Constant = %.12f\n\n",Tc_uv_Slope_const_array[4]);

   printf("Final Wavelength_LED = %f\t",Result[0][0]);
   printf("Final FWHM_L  = %.12f\t",Result[0][1]);
   printf("Final FWHM_R  = %.12f\n\n",Result[0][2]);

   printf("Final Wavelength_s   = %.12f\t",Result[0][3]);
   printf("Final FWHM_s  = %.12f\n\n",Result[0][4]);


   printf("Final Wavelength_L   = %.12f\t",Result[0][5]);
   printf("Final FWHM_L  = %.12f\n\n",Result[0][6]);

   printf("Final Iso_threm_dis  = %.12f\n\n",Result[0][7]);

   printf("Final Best CRI= %.12f\n\n",Result[0][8]);
   printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

  /* Tc_uv_array[2]=-1.018945*(Tc_uv_array[1]+Best_result[0][7])+0.538557;
   printf("u_new  = %.12f\n\n",Tc_uv_array[1]+Best_result[0][7]);
   printf("v_new  = %.12f\n\n",Tc_uv_array[2]);*/


  // double xy_new[2];

/*   uvtoxy(Tc_uv_array[1]+Best_result[0][7],Tc_uv_array[2],xy_new);
    printf("x_new  = %.12f\n\n",xy_new[0]);
   printf("y_new  = %.12f\n\n",xy_new[1]);*/
}
}

double Bubble_sort(int length,int width,double Array[length][width],double Target_array[length]){

  double temp;

  for(int v=0;v<length;v++){

    for(int k=0;k<length-1;k++){

       if(Target_array[k]<Target_array[k+1]){

        for(int u=0;u<width;u++){

            temp=Array[k][u];
            Array[k][u]=Array[k+1][u];
            Array[k+1][u]=temp;
        }
        temp=Target_array[k];
        Target_array[k]=Target_array[k+1];
        Target_array[k+1]=temp;
    }
  }
}



}
