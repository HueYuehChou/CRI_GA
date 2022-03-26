#include <stdio.h>
#include <stdlib.h>
#include<math.h>
/*
#include "Amplitude_Equation.h"
#include "excel_fileopen.h"
#include "Matrix_random.h"
#include "tristimulus_values.h"
#include "XYZ2xy.h"
#include <process.h>
*/

int wavelength_upper_limit;
int wavelength_lower_limit;
int wavelength_interval;
int data_length;
int data_width=4;
int LED_genes=3;
int s_genes=2;
int L_genes=2;
int chrosome=1;




int main(int argc, const char * argv[]) {
    srand(time(NULL));



    printf("Please input wavelength upper limit(nm)\n");
    scanf("%d",&wavelength_upper_limit);
    printf("Please input wavelength lower limit(nm)\n");
    scanf("%d",&wavelength_lower_limit);
    printf("Please input wavelength interval(nm)\n");
    scanf("%d",&wavelength_interval);
    data_length=1+(wavelength_upper_limit-wavelength_lower_limit)/wavelength_interval;
    printf("data length=%d\n",data_length);
    if(wavelength_upper_limit>840||wavelength_lower_limit<290||wavelength_interval>11||data_length<0){
        printf("error\n");
        return 0;
    }

    double CIE1931[data_length][data_width];
    CIE_Excelopen(argc, argv,wavelength_interval,data_length,data_width,CIE1931);

    double LED_Population[chrosome][LED_genes];
    double s_Population[chrosome][s_genes];
    double L_Population[chrosome][L_genes];

    Matrix_randon(chrosome,LED_genes,0,LED_Population);
    Matrix_randon(chrosome,s_genes,1,s_Population);
    Matrix_randon(chrosome,L_genes,2,L_Population);


    double S_LED[data_length][chrosome];
    double tristimulus_array_LED[3][chrosome];
    Amp_LED(data_length,chrosome,data_width,LED_genes,LED_Population,CIE1931,S_LED);
    Spectrum2XYZ(chrosome,wavelength_interval,data_length,data_width,CIE1931,S_LED,tristimulus_array_LED);

    double S_short[data_length][chrosome];
    double tristimulus_array_s[3][chrosome];
    Amp_SL(data_length,chrosome,data_width,s_genes,s_Population,CIE1931,S_short);
    Spectrum2XYZ(chrosome,wavelength_interval,data_length,data_width,CIE1931,S_short,tristimulus_array_s);

    double S_Long[data_length][chrosome];
    double tristimulus_array_L[3][chrosome];
    Amp_SL(data_length,chrosome,data_width,L_genes,L_Population,CIE1931,S_Long);
    Spectrum2XYZ(chrosome,wavelength_interval,data_length,data_width,CIE1931,S_Long,tristimulus_array_L);

    double LED_xy_array[2][chrosome];
    XYZ2xy(data_width,data_length,chrosome,tristimulus_array_LED,LED_xy_array);
    double short_xy_array[2][chrosome];
    XYZ2xy(data_width,data_length,chrosome,tristimulus_array_s,short_xy_array);
    double Long_xy_array[2][chrosome];
    XYZ2xy(data_width,data_length,chrosome,tristimulus_array_L,Long_xy_array);






   printf("-------------------------------------------------------------------------------------------------------------\n");
    for(int j=0;j<chrosome;j++){

            printf("Lambda_LED= %f\t\t",LED_Population[j][0]);

            printf("Lambda_s  = %f\t\t",s_Population[j][0]);

            printf("Lambda_L  = %f\n",L_Population[j][0]);

            printf("FWHM-Left = %f\n",LED_Population[j][1]);

            printf("FWHM-R    = %f\t\t",LED_Population[j][2]);

            printf("FWHM-s    = %f\t\t",s_Population[j][1]);

            printf("FWHM-L    = %f\n\n",L_Population[j][1]);

            printf("Xled  = %f\t\t",tristimulus_array_LED[0][j]);

            printf("Xs    = %f\t\t",tristimulus_array_s[0][j]);

            printf("Xl    = %f\n",tristimulus_array_L[0][j]);

            printf("Yled  = %f\t\t",tristimulus_array_LED[1][j]);

            printf("Ys    = %f\t\t",tristimulus_array_s[1][j]);

            printf("Yl    = %f\n",tristimulus_array_L[1][j]);

            printf("Zled  = %f\t\t",tristimulus_array_LED[2][j]);

            printf("Zs    = %f\t\t",tristimulus_array_s[2][j]);

            printf("Zl    = %f\n\n",tristimulus_array_L[2][j]);

            printf("xled  = %f\t\t",LED_xy_array[0][j]);

            printf("xs    = %f\t\t",short_xy_array[0][j]);

            printf("xl    = %f\n",Long_xy_array[0][j]);

            printf("yled  = %f\t\t",LED_xy_array[1][j]);

            printf("ys    = %f\t\t",short_xy_array[1][j]);

            printf("yl    = %f\n",Long_xy_array[1][j]);

            printf("\n\n");
            printf("-------------------------------------------------------------------------------------------------------------\n");
        }



    system("pause");
    return 0;
}
