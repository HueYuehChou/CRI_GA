 #include"tristimulus_values.h"


double Spectrum2XYZ(int chrosome,int wavelength_interval,int data_length,int data_width,double CIE1931[data_length][data_width],double S[data_length][chrosome],double tristimulus_array[3][chrosome]){

 for(int j=0;j<chrosome;j++){

       for(int i=0;i<3;i++){
       tristimulus_array[i][j] =0;
       tristimulus_array[i][j] =0;
       tristimulus_array[i][j] =0;


       }
      }
       /* for(int i=0;i<data_length;i++){
        for(int j=0;j<1;j++){
            printf("%f\t",S[i][j]);
            printf("%f\t",CIE1931[i][1]);
            printf("%f\t",CIE1931[i][2]);
            printf("%f\t",CIE1931[i][3]);
        }
        printf("\n");


        }
        printf("----------------------------------------------------------------------------------------------------\n");*/

 for(int j=0;j<chrosome;j++){

       for(int i=0;i<data_length;i++){
       tristimulus_array[0][j] +=683*(S[i][j]*CIE1931[i][1]*wavelength_interval); // tristimulus value X Riemann Sum
       tristimulus_array[1][j] +=683*(S[i][j]*CIE1931[i][2]*wavelength_interval); // tristimulus value Y Riemann Sum
       tristimulus_array[2][j] +=683*(S[i][j]*CIE1931[i][3]*wavelength_interval); // tristimulus value Z Riemann Sum

       }
      }
 }

