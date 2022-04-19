#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include"Gene_Algorithm.h"
#include "Excel_fileopen.h"
#include "Linear_interpolation.h"

int data_length,data_width=4,TCS_width,wavelength_upper_limit,wavelength_lower_limit,wavelength_interval;

int main(int argc, const char * argv[]) {
    srand(time(NULL));

    printf("Key the input of wavelength upper limit(nm)\n");
    scanf("%d",&wavelength_upper_limit);
    printf("Key the input of wavelength lower limit(nm)\n");
    scanf("%d",&wavelength_lower_limit);
    printf("Key the input of wavelength interval(nm)\n");
    scanf("%d",&wavelength_interval);
    data_length=1+(wavelength_upper_limit-wavelength_lower_limit)/wavelength_interval;
    printf("data length=%d\n",data_length);
    printf("Key the number of TCS \n");
    scanf("%d",&TCS_width);
    printf("\n\n\n");
    if(wavelength_upper_limit>830||wavelength_lower_limit<360||wavelength_interval>11||data_length<0){
        printf("error\n");
        return 0;

    }

     double CIE1931[data_length][data_width],TCS[data_length][TCS_width],Daylight_SPD_10nm[41][4],Daylight_SPD_1nm[data_length][4];

    CIE_Excelopen(argc, argv,wavelength_lower_limit,wavelength_interval,data_length,data_width,CIE1931);
    TCS_Excelopen(argc, argv,wavelength_lower_limit,wavelength_interval,data_length,TCS_width,TCS);
    Daylight_Excelopen(argc, argv,wavelength_lower_limit,1,41,4,Daylight_SPD_10nm);



for(int j=0;j<40;j++){
        double k=0;
    for(int  i=0;i<11;i++){
    Daylight_SPD_1nm[10*j+i][0]=Daylight_SPD_10nm[j][0]+k;
    Daylight_SPD_1nm[10*j+i][1]=Linear_interpolation(k,Daylight_SPD_10nm[j][0],Daylight_SPD_10nm[j][1],Daylight_SPD_10nm[j+1][0],Daylight_SPD_10nm[j+1][1]);
    Daylight_SPD_1nm[10*j+i][2]=Linear_interpolation(k,Daylight_SPD_10nm[j][0],Daylight_SPD_10nm[j][2],Daylight_SPD_10nm[j+1][0],Daylight_SPD_10nm[j+1][2]);
    Daylight_SPD_1nm[10*j+i][3]=Linear_interpolation(k,Daylight_SPD_10nm[j][0],Daylight_SPD_10nm[j][3],Daylight_SPD_10nm[j+1][0],Daylight_SPD_10nm[j+1][3]);
k+=1.0;
    }
}
/*for(int i=0;i<data_length;i++){
        for(int j=0;j<TCS_width;j++){
                printf("%f\t",TCS[i][j]);
        }
        printf("\n");
    }*/


/*for(int i=0;i<data_length;i++){
    for(int j=0;j<4;j++){
        printf("%f\t",Daylight_SPD_1nm[i][j]);
    }
    printf("\n");
}*/



   /*printf("------------------------------------------------------------------------------------------------------------------\n");
   for(int j=0;j<iso_therm_number;j++)
   printf("CRI=%f\n\n",CRI[j]);
   printf("------------------------------------------------------------------------------------------------------------------\n");


*/



    Genes_Algorithm(data_length,data_width,wavelength_interval,TCS_width,CIE1931,TCS,Daylight_SPD_1nm);

    return 0;
}
