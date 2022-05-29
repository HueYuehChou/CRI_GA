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
#include "Differential.h"



double CRI_calculate(int Constrain_Flag[1],double Tc,double Tc_uv_Slope_const_array[5],double LED_wavelength,
                     double LED_FWHM_L,double LED_FWHM_R,double Short_wavelength,double Short_FWHM,double Long_wavelength,
                     double Long_FWHM, double uv_interval,int TCS_width,int lower_limit,int wavelength_interval,int data_length,int data_width,
                     double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double Daylight_SPD_1nm[data_length][4]){
    Constrain_Flag[0]=0;

if(LED_wavelength<=445.0 || LED_wavelength>=455.0 || LED_FWHM_L<=6.0 ||  LED_FWHM_L>=11.0 ||LED_FWHM_R <=8.0
   ||LED_FWHM_R>=16.0 || Short_wavelength<=520 ||Short_wavelength>=570
   || Short_FWHM<=0.0014*Short_wavelength-0.666-0.03814
  ||Short_FWHM>=0.0014*Short_wavelength-0.666+0.03814
  ||Long_wavelength<= Short_wavelength/(1.0-(0.0001*Short_wavelength))
  || Long_wavelength>=Short_wavelength/(1.0-(0.0003102*Short_wavelength))
   ||Long_FWHM<= -0.00042857*Long_wavelength+0.37657055-0.01515
   || Long_FWHM>= -0.00042857*Long_wavelength+0.37657055+0.01515||
   uv_interval <=-0.0054|| uv_interval>=0.0054)
{
//double CRI=0;
//return CRI ;
Constrain_Flag[0]=1;
}
//printf("CRI FLAG1=%d\n",Constrain_Flag[0]);
double CRI,S_illuminant[data_length],S_illuminant_diff[data_length],Tristimulus_temp_illuminant[3],Tristimulus_temp_illuminant_diff[3],Tristimulus_temp_LED[3],Tristimulus_temp_S[3],Tristimulus_temp_L[3];

double Illuminant_xy_array[2],S_TCS_UVW_array[3],S_ILLU_UVW_array[3],S_LED[data_length],S_short[data_length],S_Long[data_length];



for(int j=0;j<data_length;j++){

   S_LED[j]=Spectrum_LED(LED_wavelength,LED_FWHM_L,LED_FWHM_R,CIE1931[j][0]);

   S_short[j]=Single_spec_phosphors(Short_wavelength,Short_FWHM,CIE1931[j][0]);

   S_Long[j]=Single_spec_phosphors(Long_wavelength,Long_FWHM,CIE1931[j][0]);


  if(Tc<=5000.0){
   S_illuminant[j]=Illuminant_Planck_spectrum(Tc,CIE1931[j][0]);
   }
  else{
   S_illuminant[j]=Illuminant_Daylight_spectrum(Tc,Daylight_SPD_1nm[j][1],Daylight_SPD_1nm[j][2],Daylight_SPD_1nm[j][3]);

  }

   S_illuminant_diff[j]=Illuminant_spectrum_differential(Tc,CIE1931[j][0]);


         }


   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_illuminant,Tristimulus_temp_illuminant);

   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_illuminant_diff,Tristimulus_temp_illuminant_diff);

   XYZ2xy(Tristimulus_temp_illuminant,Illuminant_xy_array);

   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_LED,Tristimulus_temp_LED);

   double LED_xy_array[2],Short_xy_array[2],  Long_xy_array[2];
   XYZ2xy(Tristimulus_temp_LED,LED_xy_array);

   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_short,Tristimulus_temp_S);

   XYZ2xy(Tristimulus_temp_S,Short_xy_array);

   Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_Long,Tristimulus_temp_L);

   XYZ2xy(Tristimulus_temp_L,Long_xy_array);

    double Illuminant_uv_array[2],APSL_array[2],uv_new[2],xy_new[2],Slope_const_array[2];


   xytouv(Illuminant_xy_array[0],Illuminant_xy_array[1],Illuminant_uv_array);
   Tc_uv_Slope_const_array[0]=Tc;
   Tc_uv_Slope_const_array[1]=Illuminant_uv_array[0];
   Tc_uv_Slope_const_array[2]=Illuminant_uv_array[1];

   iso_therm_line(Illuminant_uv_array[0],Illuminant_uv_array[1],Tristimulus_temp_illuminant[0],Tristimulus_temp_illuminant[1],Tristimulus_temp_illuminant[2],Tristimulus_temp_illuminant_diff[0],Tristimulus_temp_illuminant_diff[1],Tristimulus_temp_illuminant_diff[2],uv_interval,uv_new,Slope_const_array);

   Tc_uv_Slope_const_array[3]=Slope_const_array[0];
   Tc_uv_Slope_const_array[4]=Slope_const_array[1];
   uvtoxy(uv_new[0],uv_new[1],xy_new);

  Bluerate_APSL(Tristimulus_temp_LED, Tristimulus_temp_S,Tristimulus_temp_L,xy_new,APSL_array);

    double  S_total_array[data_length],Tristimulus_array_ki_TCS[3][TCS_width],Tristimulus_array_ri_TCS[3][TCS_width],Tristimulus_temp_TCS_ki[3],Tristimulus_temp_TCS_ri[3];


    double  ki_xy_array[2],ki_uv_array[2],ri_xy_array[2],ri_uv_array[2],ki_cd_array[2],ri_cd_array[2];


    S_total(data_length,APSL_array,S_LED,S_short,S_Long,S_total_array);

    int YAG_S_Peak_index=round(Short_wavelength)-lower_limit;
    int YAG_L_Peak_index=round(Long_wavelength)-lower_limit;


    double S_total_1order_diff_array[YAG_L_Peak_index-YAG_S_Peak_index-1],S_total_2order_diff_array[YAG_L_Peak_index-YAG_S_Peak_index-2];

 for(int k=YAG_S_Peak_index;k<YAG_L_Peak_index;k++){

              S_total_1order_diff_array[k-YAG_S_Peak_index]=Differential(S_total_array[k+1],S_total_array[k],1);


    }

  for(int k=0;k<YAG_L_Peak_index-YAG_S_Peak_index-2;k++){

              S_total_2order_diff_array[k]= Differential(S_total_1order_diff_array[k+1],S_total_1order_diff_array[k],1);

              if(S_total_2order_diff_array[k]>0){
                //CRI=0;
                //return CRI;
                Constrain_Flag[0]=1;
              }
    }
    //printf("CRI FLAG2=%d\n",Constrain_Flag[0]);

    double Tristimulus_temp_S_total[3],S_total_xy_array[2],S_total_uv_array[2],S_total_cd_array[2],Illuminant_cd_array[2],uv_prime_ki[2],uv_prime_ri[2];

    Spectrum2XYZ(wavelength_interval,data_length,data_width,CIE1931,S_total_array,Tristimulus_temp_S_total);
    XYZ2xy(Tristimulus_temp_S_total,S_total_xy_array);
    xytouv(S_total_xy_array[0],S_total_xy_array[1],S_total_uv_array);
    uvtocd(S_total_uv_array[0],S_total_uv_array[1],S_total_cd_array);

    uvtocd(Illuminant_uv_array[0],Illuminant_uv_array[1],Illuminant_cd_array);

    Spectrum2XYZ_TCS(wavelength_interval,data_width ,data_length,TCS_width,CIE1931,TCS,S_total_array,Tristimulus_array_ki_TCS);

    Spectrum2XYZ_TCS(wavelength_interval,data_width ,data_length,TCS_width,CIE1931,TCS,S_illuminant,Tristimulus_array_ri_TCS);

    double Ri=0,uv_prime_S_total[2],uv_prime_Illuminant[2];

    cdtouv_prime(S_total_cd_array[0],S_total_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],S_total_cd_array[0],S_total_cd_array[1],uv_prime_S_total);
    cdtouv_prime(S_total_cd_array[0],S_total_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],uv_prime_Illuminant);

    for(int i=0;i<TCS_width;i++){

        Tristimulus_temp_TCS_ki[0]=Tristimulus_array_ki_TCS[0][i];
        Tristimulus_temp_TCS_ki[1]=Tristimulus_array_ki_TCS[1][i];
        Tristimulus_temp_TCS_ki[2]=Tristimulus_array_ki_TCS[2][i];

        Tristimulus_temp_TCS_ri[0]=Tristimulus_array_ri_TCS[0][i];
        Tristimulus_temp_TCS_ri[1]=Tristimulus_array_ri_TCS[1][i];
        Tristimulus_temp_TCS_ri[2]=Tristimulus_array_ri_TCS[2][i];

        XYZ2xy(Tristimulus_temp_TCS_ki,ki_xy_array);
        XYZ2xy(Tristimulus_temp_TCS_ri,ri_xy_array);


        xytouv(ki_xy_array[0],ki_xy_array[1],ki_uv_array);


        xytouv(ri_xy_array[0],ri_xy_array[1],ri_uv_array);

        uvtocd(ki_uv_array[0],ki_uv_array[1],ki_cd_array);
        uvtocd(ri_uv_array[0],ri_uv_array[1],ri_cd_array);


        cdtouv_prime(S_total_cd_array[0],S_total_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],ki_cd_array[0],ki_cd_array[1],uv_prime_ki);

        cdtouv_prime(S_total_cd_array[0],S_total_cd_array[1],Illuminant_cd_array[0],Illuminant_cd_array[1],ri_cd_array[0],ri_cd_array[1],uv_prime_ri);




        uv_i_toUVW(Tristimulus_temp_S_total[1],Tristimulus_temp_TCS_ki[1],uv_prime_S_total[0],uv_prime_S_total[1],uv_prime_ki[0],uv_prime_ki[1],S_TCS_UVW_array);

        uv_i_toUVW(Tristimulus_temp_illuminant[1],Tristimulus_temp_TCS_ri[1],uv_prime_Illuminant[0],uv_prime_Illuminant[1],uv_prime_ri[0],uv_prime_ri[1],S_ILLU_UVW_array);


        Ri+=100-4.6*Delta_Ei(S_TCS_UVW_array[0],S_TCS_UVW_array[1],S_TCS_UVW_array[2],S_ILLU_UVW_array[0],S_ILLU_UVW_array[1],S_ILLU_UVW_array[2]);




    }

    CRI=Ri/TCS_width;

    return CRI;
}

