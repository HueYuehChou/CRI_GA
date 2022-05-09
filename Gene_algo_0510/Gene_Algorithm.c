#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include"CRI.h"
#include"Gene_Algorithm.h"
#include "Matrix_random.h"
#include "Transform_xyuvcd.h"


double Genes_Algorithm(int Lower_limit,int data_length,int data_width,int wavelength_interval,int TCS_width,double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double Daylight_SPD_1nm[data_length][4]) {
 srand(time(NULL));
double S_lambda_FWHM_m=0.0014, L_lambda_FWHM_m=-0.00042857,Constant_S_Lambda_FWHM=-0.666,Constant_L_Lambda_FWHM=0.37657055;


for(double  therm=0;therm<46;therm+=1.0){

    double Tc=2500+500.0*therm;



    int LED_genes=3,s_genes=2, L_genes=2,Survivors,Selection_percentage=40;
    int chrosome=100,Genes_number=8,Generation=100;
    double Tc_uv_Slope_const_array[5],Result[chrosome][9],LED_Population[chrosome][LED_genes],S_Population[chrosome][s_genes],L_Population[chrosome][L_genes],Iso_therm_dis[chrosome];

    Matrix_randon(chrosome,LED_genes,0,LED_Population);
    Matrix_randon(chrosome,s_genes,1,S_Population);

    Matrix_randon_Long(chrosome,L_genes,S_Population,L_Population);

    Iso_therm_dis_rand(chrosome,Iso_therm_dis);

    double S_LED[data_length],S_short[data_length],S_Long[data_length],CRI,CRI_array[chrosome],Genes[chrosome][8];

    Survivors=chrosome*Selection_percentage/100;
    /*for(int i=0;i<chrosome;i++){
        for(int j=0;j<3;j++)
              printf("%f\t",LED_Population[i][j]);
        printf("\n");
    }*/

for(int i=0;i<chrosome;i++){


   Genes[i][0]=LED_Population[i][0];
   Genes[i][1]=LED_Population[i][1];
   Genes[i][2]=LED_Population[i][2];
   Genes[i][3]=S_Population[i][0];
   Genes[i][4]=S_Population[i][1];
   Genes[i][5]=L_Population[i][0];
   Genes[i][6]=L_Population[i][1];
   Genes[i][7]=Iso_therm_dis[i];

}
double iter=0;
for(int j=0;j<Generation;j++){

        for(int i=0;i<chrosome;i++){

            CRI_array[i]=CRI_calculate(Tc,Tc_uv_Slope_const_array,Genes[i][0],Genes[i][1],Genes[i][2],Genes[i][3],Genes[i][4],Genes[i][5],Genes[i][6],Genes[i][7], TCS_width,Lower_limit, wavelength_interval, data_length, data_width, CIE1931, TCS,Daylight_SPD_1nm, CRI);

}

  Bubble_sort(chrosome,Genes_number,Genes,CRI_array);
  double temp=Genes[0][0],temp1=Genes[0][1],temp2=Genes[0][2],temp3=Genes[0][3],temp7=Genes[0][7];

for(int i=Survivors;i<chrosome;i++){

        Genes[i][0]=Cross_over(Genes[rand()%Survivors][0],Genes[rand()%Survivors][0],iter,1);

     if((Genes[i][0]<(445.0)) || (Genes[i][0]>(455.0))){
            Genes[i][0]=temp;
        }

        Genes[i][1]=Cross_over(Genes[rand()%Survivors][1],Genes[rand()%Survivors][1],iter,1);

      if((Genes[i][1]<(6.0)) || (Genes[i][1]>(11.0))){
            Genes[i][1]=temp1;
        }

        Genes[i][2]=Cross_over(Genes[rand()%Survivors][2],Genes[rand()%Survivors][2],iter,1);

     if((Genes[i][2]<(8.0)) || (Genes[i][2]>(16.0))){
            Genes[i][2]=temp2;
        }

        Genes[i][3]=Cross_over(Genes[rand()%Survivors][3],Genes[rand()%Survivors][3],iter,1);

      if((Genes[i][3]<(520.0)) || (Genes[i][3]>(570))){
            Genes[i][3]=temp3;
        }

        Genes[i][4]=Cross_over(Genes[rand()%Survivors][4],Genes[rand()%Survivors][4],iter,0.1);

           if((Genes[i][4]<S_lambda_FWHM_m*Genes[i][3]+Constant_S_Lambda_FWHM-0.03814) || (Genes[i][4]>S_lambda_FWHM_m*Genes[i][3]+Constant_S_Lambda_FWHM+0.03814)){
            Genes[i][4]=S_lambda_FWHM_m*Genes[i][3]+Constant_S_Lambda_FWHM;
        }
        Genes[i][5]=Cross_over(Genes[rand()%Survivors][5],Genes[rand()%Survivors][5],iter,1);

         if((Genes[i][5]<(Genes[i][3]/(1.0-(0.0001*Genes[i][3])))) || (Genes[i][5]>Genes[i][3]/(1.0-(0.0003102*Genes[i][3]))) || Genes[i][5]<570 || Genes[i][5]>660){
            Genes[i][5]=(Genes[i][3]/(1.0-(0.0002051*Genes[i][3])));
        }

        Genes[i][6]=Cross_over(Genes[rand()%Survivors][6],Genes[rand()%Survivors][6],iter,0.1);

       if((Genes[i][6]<L_lambda_FWHM_m*Genes[i][5]+Constant_L_Lambda_FWHM-0.01515) || (Genes[i][6]>L_lambda_FWHM_m*Genes[i][5]+Constant_L_Lambda_FWHM+0.01515)){
                Genes[i][6]=L_lambda_FWHM_m*Genes[i][5]+Constant_L_Lambda_FWHM;
       }


        Genes[i][7]=Cross_over(Genes[rand()%Survivors][7],Genes[rand()%Survivors][7],iter,0.001);
           if((Genes[i][7]<(-0.0054)) || (Genes[i][7]>(0.0054))){
            Genes[i][7]=temp7;
        }

        temp=Genes[i][0];
        temp1=Genes[i][1];
        temp2=Genes[i][2];
        temp3=Genes[i][3];
        //temp4=Genes[i][4];
        //temp5=Genes[i][5];
       // temp6=Genes[i][6];
        temp7=Genes[i][7];

}

iter+=1.0;

}
for(int i=0;i<chrosome;i++){
   for(int j=0;j<8;j++){
   Result[i][j]=Genes[i][j];
   }
   Result[i][8]=CRI_array[i];
}

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
double Cross_over(double Parent1,double Parent2,double iter,double Mutate){


    double    Mutation=Mutate*(2.0*rand()/RAND_MAX-1.0)*(1-(iter/15000.0));
    double    Son=((Parent1+Parent2)/2.0)+Mutation;

    return Son;

}
