#include <math.h>
#include "Differential.h"
#include "CRI.h"
#include "Inverse_Matrix.h"
#include <malloc.h>

double  LM_Algorithm(double Array1[9],double Tc,double Tc_uv_Slope_const_array[5],
                     int TCS_width,int Lower_limit, int wavelength_interval, int data_length, int data_width,
                     double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],
                     double Daylight_SPD_1nm[data_length][4])
{

    int num =8,flag;

    double Target_Diff=0;

    double *Jacobian=(double *)malloc(num*sizeof(double));

    double *Hessian =(double *)malloc(num*num*sizeof(double));
    double *Delta=(double *)malloc(num*sizeof(double));
    double Lambda;
    double * Inverse=(double *)malloc(num*num*sizeof(double));
    int LM_Iter=200;
    int Constrain_Flag[1];
    double Best[9]={0};
    double Useful_Best[9]={0};
    double Lambda_coef=0.001;
    double Target_last;
    double Target;
    double Temp[9]={0};
    double Residuals_vector[8]={0};
    double Array_diff[8]={0};
    double Delta_Lambda_B=8e-5,Delta_L_FWHM_B=1e-3
                    ,Delta_R_FWHM_B=1e-4,Delta_Lambda_S=1e-4
                    ,Delta_FWHM_S=5e-5,Delta_Lambda_L=1e-6,Delta_FWHM_L=1e-5
                    ,Delta_Dv=1e-3;
    double Variance_Delta[8]={Delta_Lambda_B,Delta_L_FWHM_B
                    ,Delta_R_FWHM_B,Delta_Lambda_S
                    ,Delta_FWHM_S,Delta_Lambda_L,Delta_FWHM_L
                    ,Delta_Dv};

    double CRI_partial;
    double Lambda_coe_temp=1.0;
  /*double Array1[9]={448.104942	,10.99930879	,15.9993838	,524.5564836,
  	0.106431948	,614.8677103	,0.128193772	,0.005332607,	93.03494687





  };
*/

    for(int i=0;i<num+1;i++){
         Best[i]=Array1[i];
         Useful_Best[i]=Array1[i];
         printf("%f\t",Array1[i]);
    }
    printf("\n");

   Target_last=100.0-Array1[num];
    Target=100.0-Array1[num];
   // printf("CRI=%.12f\n",Array1[8]);

for (int  z= 0;z<LM_Iter;z++){

   for(int i= 0; i< num+1;i++){
                 Temp[i]=Array1[i];
         //         printf("%f\t",Array1[i]);
                  if(i>0)
                  Array_diff[i-1]=Temp[i-1];

    }
    for(int i=0;i<num;i++){

          Array_diff[i]=Array1[i]+Variance_Delta[i]*Array1[i];
          CRI_partial=CRI_calculate(Constrain_Flag,Tc,Tc_uv_Slope_const_array, Array_diff[0], Array_diff[1], Array_diff[2],
                                    Array_diff[3],Array_diff[4],Array_diff[5],Array_diff[6],Array_diff[7], TCS_width,Lower_limit,
                                    wavelength_interval, data_length, data_width, CIE1931, TCS,Daylight_SPD_1nm);

         *(Jacobian+i)=((100.0-CRI_partial)-(100.0-Array1[8]))/(Variance_Delta[i]*Array1[i]);
         Residuals_vector[i]=(100.0-CRI_partial)-(100.0-Array1[8]);
       //   printf("CRI_partial=%.12f\n",CRI_partial);
     //    printf("Jacobian=%f\n",*(Jacobian+i));

       for(int j=0; j<num;j++){

            Array_diff[j]=Array1[j];

}

            }

    double *I=(double *)malloc(num*num*sizeof(double));
    double *S=(double *)malloc(num*num*sizeof(double));

  for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){

                *(Hessian+num*i+j) =*(Jacobian+i) * *(Jacobian+j);
          //      printf("%f\t",*(Hessian+num*i+j));
        }
     //   printf("\t");
    }
 //Lambda=Lambda_coef * abs(*(Jacobian+7)) ;
 Lambda=Lambda_coef;
 //printf("Lambda=%f\n",Lambda);
     for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
                  if(i==j){
                *(S+num*i+j)=*(Hessian+num*i+j) + Lambda;
                  }
                  else
                  {
                      *(S+num*i+j)=*(Hessian+num*i+j) ;
                  }
 //               printf("%.8f\t",*(S+num*i+j));
        }
   //     printf("\n");
     }

    matrix_inv(S, Inverse);
/*for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){

  //              printf("%f\t",*(Inverse+num*i+j));
        }
        printf("\n");
     }
      printf("\n");*/

    /*  double test[8][8]={0};
      for(int k=0;k<num;k++){
      for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){

                test[k][i]+=*(S+num*k+j) * *(Inverse+num*j+i) ;

        }
      }
     }
     for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
                printf("%f\t",test[i][j]);
        }
        printf("\n");
     }*/

     //  printf("\n");
  for(int j=0;j<num;j++){

            for(int i=0; i<num;i++){

   *(Delta+j) += (-1.0)**(Inverse+num*j+i) * *(Jacobian+i);
   //printf("%f\t",*(Inverse+num*j+i) );
   //printf("%f\t",*(Jacobian+i));

            }
          //  printf("\n");

         Array1[j]=Array1[j] +*(Delta+j)*Residuals_vector[j];

        //  printf("Delta=%.12f\n",*(Delta+j)*Residuals_vector[j]);
          //  printf("\n");

    }
Array1[num]=CRI_calculate(Constrain_Flag,Tc
,Tc_uv_Slope_const_array,Array1[0],Array1[1]
,Array1[2],Array1[3],Array1[4],Array1[5],Array1[6]
,Array1[7], TCS_width,Lower_limit, wavelength_interval
, data_length, data_width, CIE1931, TCS,Daylight_SPD_1nm);

Target= 100.0-Array1[num];
printf("LM_CRI = %.12f\t",Array1[8]);
printf("%d\n",Constrain_Flag[0]);

if(Constrain_Flag[0]==0 && Useful_Best[8]<Array1[num]){
        for(int l=0;l<num+1;l++){
            Useful_Best[l]=Array1[l];
        }
}

if(Array1[num]!=0.0 && Target_last>Target){

    Lambda_coef=Lambda_coef/6;
    if(Array1[num]>Best[num]){
      for(int i=0;i<num+1;i++)
            Best[i]=Array1[i];
    }
    else{
             for(int i=0;i<num+1;i++)
            Array1[i]=Best[i];
    }
 }

else
{
        Lambda_coef=Lambda_coef*1.2;

        for(int i=0;i<num+1;i++){

            Array1[i]=Best[i];
        }
}

Target_Diff=Target-Target_last;
Target_last=Target;
    }

       for(int j=0; j<9;j++){

                    printf("%.12f\t",Useful_Best[j]);
            }
            printf("\n");

return 0;

}


