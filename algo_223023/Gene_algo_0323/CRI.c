#include "CRI.h"
 #include"Tristimulus_values.h"
#include "XYZ2xy.h"
#include "Illuminant_spectrum.h"
#include "Iso_therm_line.h"
#include "S_total.h"
#include "Bluerate_APSL.h"
#include "Transform_xyuvcd.h"
#include "uv_i_toUVW.h"
#include "Delta_Ei.h"
#include<time.h>
#include <stdlib.h>
#include"Spectrum_Equation.h"



double CRI_calculate(double Tc,double Tc_uv_Slope_const_array[5],double LED_wavelength,double LED_FWHM_L,double LED_FWHM_R,double Short_wavelength,double Short_FWHM,double Long_wavelength,double Long_FWHM, double uv_interval,int TCS_width,int wavelength_interval,int data_length,int data_width,double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double Daylight_SPD_1nm[data_length][4],double CRI){

double S_illuminant[data_length],S_illuminant_diff[data_length],Tristimulus_temp_illuminant[3],Tristimulus_temp_illuminant_diff[3],Tristimulus_temp_LED[3],Tristimulus_temp_S[3],Tristimulus_temp_L[3];

double Illuminant_xy_array[2],S_TCS_UVW_array[3],S_ILLU_UVW_array[3],S_LED[data_length],S_short[data_length],S_Long[data_length];


/* for(int i=0;i<data_length;i++){

        printf("%f\n",S_short[i]);

   }*/
for(int j=0;j<data_length;j++){

   S_LED[j]=Spectrum_LED(LED_wavelength,LED_FWHM_L,LED_FWHM_R,CIE1931[j][0]);

   S_short[j]=Single_spec_phosphors(Short_wavelength,Short_FWHM,CIE1931[j][0]);

   S_Long[j]=Single_spec_phosphors(Long_wavelength,Long_FWHM,CIE1931[j][0]);

  // if(Tc<=5000.0){
   S_illuminant[j]=Illuminant_Planck_spectrum(Tc,CIE1931[j][0]);
 //  }
  // else{
 //  S_illuminant[j]=Illuminant_Daylight_spectrum(Tc,Daylight_SPD_1nm[j][1],Daylight_SPD_1nm[j][2],Daylight_SPD_1nm[j][3]);

//   }

   S_illuminant_diff[j]=Illuminant_spectrum_differential(Tc,CIE1931[j][0]);


         }
         for(int i=0;i<data_length;i++){
        for(int j=0;j<TCS_width;j++){
                printf("%f\t",TCS[i][j]);
        }
        printf("\n");
    }

printf("-------------------------------------------Sillu---------------------------------------------\n\n");
  for(int k=0;k<data_length;k++){

        printf("%.8f\n",S_illuminant[k]);

   }
   /*printf("------------------------------------------SS---------------------------------------------------\n\n");
       for(int k=0;k<data_length;k++){

        printf("%.8f\n",S_short[k]);

   }
   printf("------------------------------------------SL---------------------------------------------------\n\n");
       for(int k=0;k<data_length;k++){

        printf("%.8f\n",S_Long[k]);

   }
   printf("---------------------------------------------------------------------------------------------\n\n");*/




   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_illuminant,Tristimulus_temp_illuminant);
printf("\n");
   printf("Xillu  = %.8f\n",Tristimulus_temp_illuminant[0]);
   printf("Yillu  = %.8f\n",Tristimulus_temp_illuminant[1]);
   printf("Zillu  = %.8f\n\n",Tristimulus_temp_illuminant[2]);
   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_illuminant_diff,Tristimulus_temp_illuminant_diff);
 printf("X_diff_illu  = %.8f\n",Tristimulus_temp_illuminant_diff[0]);
   printf("Y_diff_illu  = %.8f\n",Tristimulus_temp_illuminant_diff[1]);
   printf("Z_diff_illu  = %.8f\n\n",Tristimulus_temp_illuminant_diff[2]);


   XYZ2xy(Tristimulus_temp_illuminant,Illuminant_xy_array);
  /* printf("xillu = %.8f\n",Illuminant_xy_array[0]);
   printf("yillu = %.8f\n\n",Illuminant_xy_array[1]);

   printf("---------------------------------------------------------------------------------------------\n\n");*/


   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_LED,Tristimulus_temp_LED);
  /* printf("Xled  = %.8f\n",Tristimulus_temp_LED[0]);
   printf("Yled  = %.8f\n",Tristimulus_temp_LED[1]);
   printf("Zled  = %.8f\n\n",Tristimulus_temp_LED[2]);*/

   double LED_xy_array[2],Short_xy_array[2],  Long_xy_array[2];
   XYZ2xy(Tristimulus_temp_LED,LED_xy_array);
  /* printf("yled = %.8f\n",LED_xy_array[0]);
   printf("xled = %.8f\n\n",LED_xy_array[1]);
   printf("---------------------------------------------------------------------------------------------\n\n");*/



   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_short,Tristimulus_temp_S);

  /* printf("Xs  = %.8f\n",Tristimulus_temp_S[0]);
   printf("Ys  = %.8f\n",Tristimulus_temp_S[1]);
   printf("Zs  = %.8f\n\n",Tristimulus_temp_S[2]);*/

   XYZ2xy(Tristimulus_temp_S,Short_xy_array);
/* printf("ys  = %.8f\n",Short_xy_array[0]);
   printf("xs  = %.8f\n\n",Short_xy_array[1]);
   printf("---------------------------------------------------------------------------------------------\n\n");*/

   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_Long,Tristimulus_temp_L);

  /* printf("Xl  = %.8f\n",Tristimulus_temp_L[0]);
   printf("Yl  = %.8f\n",Tristimulus_temp_L[1]);
   printf("Zl  = %.8f\n\n",Tristimulus_temp_L[2]);*/

   XYZ2xy(Tristimulus_temp_L,Long_xy_array);
  /* printf("yl  = %.8f\n",Long_xy_array[0]);
   printf("xl  = %.8f\n\n",Long_xy_array[1]);
    printf("---------------------------------------------------------------------------------------------\n\n");*/





    double Illuminant_uv_array[2],APSL_array[2],uv_new[2],xy_new[2],Slope_const_array[2];


   xytouv(Illuminant_xy_array[0],Illuminant_xy_array[1],Illuminant_uv_array);
   Tc_uv_Slope_const_array[0]=Tc;
   Tc_uv_Slope_const_array[1]=Illuminant_uv_array[0];
   Tc_uv_Slope_const_array[2]=Illuminant_uv_array[1];
 //  printf("u_Illuminant_uv_array= %.8f\t",Illuminant_uv_array[0]);
  // printf("v_Illuminant_uv_array = %.8f\n\n",Illuminant_uv_array[1]);


   iso_therm_line(Illuminant_uv_array[0],Illuminant_uv_array[1],Tristimulus_temp_illuminant[0],Tristimulus_temp_illuminant[1],Tristimulus_temp_illuminant[2],Tristimulus_temp_illuminant_diff[0],Tristimulus_temp_illuminant_diff[1],Tristimulus_temp_illuminant_diff[2],uv_interval,uv_new,Slope_const_array);

   Tc_uv_Slope_const_array[3]=Slope_const_array[0];
   Tc_uv_Slope_const_array[4]=Slope_const_array[1];

  // printf("u_new= %.8f\t",uv_new[0]);
  // printf("v_new = %.8f\n\n",uv_new[1]);
   uvtoxy(uv_new[0],uv_new[1],xy_new);


   // printf("x = %.8f\t",xy_new[0]);
   // printf("y = %.8f\n\n",xy_new[1];

   Bluerate_APSL(Tristimulus_temp_LED, Tristimulus_temp_S,Tristimulus_temp_L,xy_new,APSL_array);

   printf("APS=%.12f\n",APSL_array[0]);



 printf("APL=%.12f\n\n",APSL_array[1]);
    //  printf("---------------------------------------------------------------------------------------------\n\n");



    double  S_total_array[data_length],Tristimulus_array_ki_TCS[3][TCS_width],Tristimulus_array_ri_TCS[3][TCS_width],Tristimulus_temp_TCS_ki[3],Tristimulus_temp_TCS_ri[3];


    double  ki_xy_array[2],ki_uv_array[2],ri_xy_array[2],ri_uv_array[2],ki_cd_array[2],ri_cd_array[2];


    S_total(data_length,APSL_array,S_LED,S_short,S_Long,S_total_array);
   /* for(int k=0;k<data_length;k++){
            printf("%.8f\n",S_total_array[k]);


    }*/

    double Tristimulus_temp_S_total[3],S_total_xy_array[2],S_total_uv_array[2],S_total_cd_array[2],Illuminant_cd_array[2],uv_prime_ki[2],uv_prime_ri[2];


   // printf("------------------------------------S_total-----------------------------------------\n\n");

    Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_total_array,Tristimulus_temp_S_total);
    XYZ2xy(Tristimulus_temp_S_total,S_total_xy_array);
    xytouv(S_total_xy_array[0],S_total_xy_array[1],S_total_uv_array);
    uvtocd(S_total_uv_array[0],S_total_uv_array[1],S_total_cd_array);
   /* printf("u = %f\t",S_total_uv_array[0]);
   printf("v = %f\n\n",S_total_uv_array[1]);*/

 printf("S_total_X=%f\t",Tristimulus_temp_S_total[0]);
    printf("S_total_Y=%f\t",Tristimulus_temp_S_total[1]);
    printf("S_total_Z=%f\n\n",Tristimulus_temp_S_total[2]);
    printf("S_total_x=%f\t",S_total_xy_array[0]);
    printf("S_total_y=%f\n\n",S_total_xy_array[1]);
    printf("S_total_u=%f\t",S_total_uv_array[0]);
    printf("S_total_v=%f\n\n",S_total_uv_array[1]);
    printf("S_total_c=%f\t",S_total_cd_array[0]);
    printf("S_total_d=%f\n\n",S_total_cd_array[1]);

   // printf("------------------------------------Illuminant-----------------------------------------\n\n");




    uvtocd(Illuminant_uv_array[0],Illuminant_uv_array[1],Illuminant_cd_array);

 printf("Illuminant_X=%f\t",Tristimulus_temp_illuminant[0]);
    printf("IlluminantY=%f\t",Tristimulus_temp_illuminant[1]);
    printf("IlluminantZ=%f\n\n",Tristimulus_temp_illuminant[2]);
    printf("Illuminantl_x=%f\t",xy_new[0]);
    printf("Illuminant_y=%f\n\n",xy_new[1]);
    printf("Illuminant_u=%f\t",uv_new[0]);
    printf("Illuminant_v=%f\n\n",uv_new[1]);
    printf("Illuminant_c=%f\t",Illuminant_cd_array[0]);
    printf("Illuminant_d=%f\n\n",Illuminant_cd_array[1]);





    Spectrum2XYZ_TCS(wavelength_interval,data_width ,data_length,TCS_width,CIE1931,TCS,S_total_array,Tristimulus_array_ki_TCS);

    Spectrum2XYZ_TCS(wavelength_interval,data_width ,data_length,TCS_width,CIE1931,TCS,S_illuminant,Tristimulus_array_ri_TCS);

    double Ri=0,uv_prime_S_total[2],uv_prime_Illuminant[2];

    cdtouv_prime(S_total_cd_array[0],S_total_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],S_total_cd_array[0],S_total_cd_array[1],uv_prime_S_total);
    cdtouv_prime(S_total_cd_array[0],S_total_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],uv_prime_Illuminant);


    printf("S_total_cd_array=%.8f\n\n",S_total_cd_array[0]);
    printf("S_total_cd_array=%.8f\n\n",S_total_cd_array[1]);
    printf("Illuminant_cd_array=%.8f\n\n",Illuminant_cd_array[0]);
    printf("Illuminant_cd_array=%.8f\n\n",Illuminant_cd_array[1]);



    printf("u_prime_S_total=%.8f\n\n",uv_prime_S_total[0]);
    printf("v_prime_S_total=%.8f\n\n",uv_prime_S_total[1]);
    printf("u_prime_Illuminant=%.8f\n\n",uv_prime_Illuminant[0]);
    printf("v_prime_Illuminant=%.8f\n\n",uv_prime_Illuminant[1]);


    for(int i=0;i<TCS_width;i++){

     printf("------------------------------------i=%d-----------------------------------------\n\n",i+1);


    printf("TCS_ki_X=%.8f\t",Tristimulus_array_ki_TCS[0][i]);
        printf("TCS_ki_Y=%.8f\t",Tristimulus_array_ki_TCS[1][i]);
        printf("TCS_ki_Z=%.8f\n\n",Tristimulus_array_ki_TCS[2][i]);
        Tristimulus_temp_TCS_ki[0]=Tristimulus_array_ki_TCS[0][i];
        Tristimulus_temp_TCS_ki[1]=Tristimulus_array_ki_TCS[1][i];
        Tristimulus_temp_TCS_ki[2]=Tristimulus_array_ki_TCS[2][i];

      printf("TCS_ri_X=%.8f\t",Tristimulus_array_ri_TCS[0][i]);
        printf("TCS_ri_Y=%.8f\t",Tristimulus_array_ri_TCS[1][i]);
        printf("TCS_ri_Z=.8%f\n\n",Tristimulus_array_ri_TCS[2][i]);
        Tristimulus_temp_TCS_ri[0]=Tristimulus_array_ri_TCS[0][i];
        Tristimulus_temp_TCS_ri[1]=Tristimulus_array_ri_TCS[1][i];
        Tristimulus_temp_TCS_ri[2]=Tristimulus_array_ri_TCS[2][i];

        XYZ2xy(Tristimulus_temp_TCS_ki,ki_xy_array);
       printf("TCS_ki_x=.8%f\t",ki_xy_array[0]);
        printf("TCS_ki_y=%.8f\n\n",ki_xy_array[1]);
        XYZ2xy(Tristimulus_temp_TCS_ri,ri_xy_array);
       printf("TCS_ri_x=%.8f\t",ri_xy_array[0]);
        printf("TCS_ri_y=%.8f\n\n",ri_xy_array[1]);

        xytouv(ki_xy_array[0],ki_xy_array[1],ki_uv_array);
       /* printf("TCS_ki_u=%.8f\t",ki_uv_array[0]);
        printf("TCS_ki_v=%.8f\n\n",ki_uv_array[1]);*/


        xytouv(ri_xy_array[0],ri_xy_array[1],ri_uv_array);
      printf("TCS_ri_u=%.8f\t",ri_uv_array[0]);
        printf("TCS_ri_v=%.8f\n\n",ri_uv_array[1]);

        uvtocd(ki_uv_array[0],ki_uv_array[1],ki_cd_array);
        uvtocd(ri_uv_array[0],ri_uv_array[1],ri_cd_array);
    printf("TCS_ki_c=%.8f\t",ki_cd_array[0]);
        printf("TCS_ki_d=%.8f\n\n",ki_cd_array[1]);
        printf("TCS_ri_c=%.8f\t",ri_cd_array[0]);
        printf("TCS_ri_d=%.8f\n\n",ri_cd_array[1]);

        cdtouv_prime(S_total_cd_array[0],S_total_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],ki_cd_array[0],ki_cd_array[1],uv_prime_ki);
       printf("u_prime_ki=%.8f\t",uv_prime_ki[0]);
        printf("v_prime_ki=%.8f\n\n",uv_prime_ki[1]);
        cdtouv_prime(S_total_cd_array[0],S_total_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],ri_cd_array[0],ri_cd_array[1],uv_prime_ri);
      printf("u_prime_ri=%.8f\t",uv_prime_ri[0]);
        printf("v_prime_ri=%.8f\n\n",uv_prime_ri[1]);



        uv_i_toUVW(Tristimulus_temp_S_total[1],Tristimulus_temp_TCS_ki[1],uv_prime_S_total[0],uv_prime_S_total[1],uv_prime_ki[0],uv_prime_ki[1],S_TCS_UVW_array);
        printf("U*_S_TCS=%.8f\t",S_TCS_UVW_array[0]);
        printf("V*_S_TCS=%.8f\t",S_TCS_UVW_array[1]);
        printf("W*_S_TCS=%.8f\n\n",S_TCS_UVW_array[2]);
        uv_i_toUVW(Tristimulus_temp_illuminant[1],Tristimulus_temp_TCS_ri[1],uv_prime_Illuminant[0],uv_prime_Illuminant[1],uv_prime_ri[0],uv_prime_ri[1],S_ILLU_UVW_array);
       printf("U*_ILLU_TCS=%.8f\t",S_ILLU_UVW_array[0]);
        printf("V*_ILLU_TCS=%.8f\t",S_ILLU_UVW_array[1]);
        printf("W*_ILLU_TCS=%.8f\n\n",S_ILLU_UVW_array[2]);

        Ri+=100-4.6*Delta_Ei(S_TCS_UVW_array[0],S_TCS_UVW_array[1],S_TCS_UVW_array[2],S_ILLU_UVW_array[0],S_ILLU_UVW_array[1],S_ILLU_UVW_array[2]);
      printf("Ri=%.8f\n\n",Delta_Ei(S_TCS_UVW_array[0],S_TCS_UVW_array[1],S_TCS_UVW_array[2],S_ILLU_UVW_array[0],S_ILLU_UVW_array[1],S_ILLU_UVW_array[2]));




    }
    CRI=Ri/TCS_width;
   /* printf("CRI=%f\n\n", CRI);
    printf("-----------------------------------------------------------------------------------\n\n");*/

    return CRI;












}

