 #include"Tristimulus_values.h"


double Spectrum2XYZ(int wavelength_interval,int data_length,int data_width,double CIE1931[data_length][data_width],double S[data_length],double Tristimulus_temp[3]){

 Tristimulus_temp[0]=0;
 Tristimulus_temp[1]=0;
 Tristimulus_temp[2]=0;

 //printf("--------------------------------CIE1931-----------------------------------------------------------------\n");

    for(int i=0;i<data_length;i++){
       Tristimulus_temp[0] +=683*(S[i]*CIE1931[i][1]*wavelength_interval); // tristimulus value X Riemann Sum
       Tristimulus_temp[1] +=683*(S[i]*CIE1931[i][2]*wavelength_interval); // tristimulus value Y Riemann Sum
       Tristimulus_temp[2] +=683*(S[i]*CIE1931[i][3]*wavelength_interval); // tristimulus value Z Riemann Sum
       /*printf("%.8f\t",CIE1931[i][0]);
       printf("%.8f\t",CIE1931[i][1]);
        printf("%.8f\t",CIE1931[i][2]);
         printf("%.8f\t",CIE1931[i][3]);
         printf("\n");*/

       }
}






 double Spectrum2XYZ_TCS(int wavelength_interval,int data_width ,int data_length,int TCS_width,double CIE1931[data_length][data_width],double TCS[data_length][TCS_width],double S[data_length],double Tristimulus_temp[3][TCS_width]){
   for (int i=0;i<TCS_width;i++){
       Tristimulus_temp[0][i]=0;
       Tristimulus_temp[1][i]=0;
       Tristimulus_temp[2][i]=0;
   }
 //printf("--------------------------------CIE1931-----------------------------------------------------------------\n");


for (int j=0;j<TCS_width;j++){
    for(int i=0;i<data_length;i++){
       Tristimulus_temp[0][j] +=683*(S[i]*CIE1931[i][1]*TCS[i][j]*wavelength_interval); // tristimulus value X Riemann Sum
       Tristimulus_temp[1][j]+=683*(S[i]*CIE1931[i][2]*TCS[i][j]*wavelength_interval); // tristimulus value Y Riemann Sum
       Tristimulus_temp[2][j]+=683*(S[i]*CIE1931[i][3]*TCS[i][j]*wavelength_interval); // tristimulus value Z Riemann Sum
       /*  printf("%.8f\t",CIE1931[i][1]);
        printf("%.8f\t",CIE1931[i][2]);
         printf("%.8f\t",CIE1931[i][3]);
         printf("\n");*/

       }

 }
 }
