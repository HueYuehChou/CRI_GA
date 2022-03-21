#include<math.h>
constexpr int matrix_length=401;
constexpr int matrix_width=3;

float LED_wavelength_min=430, LED_wavelength_max=460; // 藍光LED波長範圍

float S_wavelength_min=520, S_wavelength_max=540;  // YAG短波長範圍

float L_wavelength_min=520, L_wavelength_max=620;  // YAG長波長範圍

float LED_Population[matrix_length][matrix_width];
float S_Population[matrix_length][matrix_width];
float L_Population[matrix_length][matrix_width];

float Halfwidth_LED_min=20;
float Halfwidth_S_min=10;
float Halfwidth_L_min=50;

int i,j;



float genes_range(float gene_min,float gene_max)
{

     float diff=gene_max-gene_min;

     return (diff*rand()/RAND_MAX + gene_min); // 回傳範圍內的亂數


}


float *Matrix_randon(float Population[matrix_length][matrix_width],int width,int choice){

if(choice==0){

for(int i=0;i<width;i++){
        for(int j=0;j<matrix_length;j++){
                if(i==0)// blue light 波長
                Population[j][i] = genes_range(LED_wavelength_min,LED_wavelength_max);
                else if(i==1) // 左半高寬
                Population[j][i] = genes_range(Halfwidth_LED_min,LED_Population[j][0]-LED_wavelength_min);
                else         //右半高寬
                Population[j][i] = genes_range(Halfwidth_LED_min,LED_wavelength_max-LED_Population[j][0]);
        }
    }
    return reinterpret_cast<float *>(Population);
}
else if (choice==1)
{
        for(i=0;i<width;i++){
        for(j=0;j<matrix_length;j++){
               if(i==0) // 短波長
                Population[j][i] = genes_range(S_wavelength_min,S_wavelength_max);
                else  //短波長半高寬
                Population[j][i] = genes_range(Halfwidth_S_min,S_Population[j][0]-S_wavelength_min);

}
}
return reinterpret_cast<float *>(Population);
}
else{
    for(i=0;i<width;i++){
        for(j=0;j<matrix_length;j++){
                if(i==0)// 長波長
                Population[j][i] = genes_range(L_wavelength_min,L_wavelength_max);
                else // 短波長半高寬
                Population[j][i] = genes_range(Halfwidth_L_min,L_Population[j][0]-L_wavelength_min);

}
    }
    }
    return reinterpret_cast<float *>(Population);
}

