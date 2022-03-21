#include<math.h>

float tristimulus_array[3];
float xyz_array[5];

constexpr int CIE1931_length=401;
constexpr int CIE1931_width=4;
constexpr int CIE_calculation_range=401;
int upper_limit=780;
int lower_limit=380;




float *tristimulus_value(float CIE1931[CIE1931_length][CIE1931_width],float S[CIE1931_width]){




    int n=CIE_calculation_range;//401 intervals
    float h=(upper_limit+1-lower_limit)/n;//the width of interval
    printf("---------------------\n");


       std::fill_n(tristimulus_array, 3, 0);

       for(i=0;i<CIE_calculation_range;i++){
       tristimulus_array[0] += (683*S[i]*CIE1931[i][1]*h); // tristimulus value X Riemann Sum
       tristimulus_array[1] += (683*S[i]*CIE1931[i][2]*h); // tristimulus value Y Riemann Sum
       tristimulus_array[2] += (683*S[i]*CIE1931[i][3]*h); // tristimulus value Z Riemann Sum
       }


       float X=tristimulus_array[0];
       float Y=tristimulus_array[1];
       float Z=tristimulus_array[2];

       float x=X/(X+Y+Z); //x-coordinate
       float y=Y/(X+Y+Z); //y-coordinate
       printf("X=%f\n",X);
       printf("Y=%f\n",Y);
       printf("Z=%f\n",Z);


       xyz_array[0]=X;
       xyz_array[1]=Y;
       xyz_array[2]=Z;
       xyz_array[3]=x;
       xyz_array[4]=y;



return reinterpret_cast<float *>(xyz_array);



}





