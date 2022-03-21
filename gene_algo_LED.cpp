#include<graphics.h>
#include<math.h>
#include<time.h>
#include<iostream>


#include"excel_fileopen.h"
#include"Matrix_random.h"
#include"tristimulus_values.h"
#include"Amplitude_Equation.h"


using namespace std;
constexpr int n_chromosomes = 401;
constexpr int n_genes = 4;
float chromosome[401];

float CIE_1931[401][4];
float Tc_data[56][4];
int Tc_data_length=56;
int LED_genes=3       , S_genes=2 , L_genes=2, excel_lengh=4;
int n_iter=100;
float Rmse_SL[401];
float CIE_19x[401],CIE_19y[401],CIE_19z[401];
float SLED[401],Ss[401],SL[401];
float xled;
float yled;
float xs;
float ys;
float xl;
float yl;
float XLED,Xs,XL;
float YLED,Ys,YL;
float ZLED,Zs,ZL;
float LED_chromosome[3]  ;
float S_chromosome[2]    ;
float L_chromosome[2]    ;
float * temp1;
float * temp2;
float * ASL_memory;
float Rmse_LED[401];
float Rmse_S[401];
float Rmse_L[401];
int s,gen,k;
float AS[56];
float AL[56];
float Stotal[401][56];

char text[80];
float *tristimulus_memory;

int main()
{
    initwindow(getmaxwidth( ), getmaxheight( ));
	settextstyle(0,0,2);
    srand(time(NULL));
    temp1=CIE_excel_fileopen(CIE_1931);
    temp2=Tc_excel_fileopen(Tc_data);

   float *matrix  = Matrix_randon(LED_Population,LED_genes,0);
   float *matrix1 = Matrix_randon(S_Population,S_genes,1);
   float *matrix2 = Matrix_randon(L_Population,L_genes,2);
   for(i=0; i<n_chromosomes; i++){
            for(j=0;j<LED_genes;j++)
            LED_Population[i][j]=*(matrix + (i * LED_genes) + j); // LED chromosome-gene

            for(k=0;k<S_genes;k++)
            S_Population[i][k]=*(matrix1 + (i * S_genes) + k+i);  // YAG short wavelength chromosome-gene

            for(s=0;s<L_genes;s++)
            L_Population[i][s]=*(matrix2 + (i * L_genes) + s+i);  // YAG long wavelength chromosome-gene
    }

    for(i=0;i<n_chromosomes;i++){
            for(j=0;j<LED_genes;j++)
            chromosome[j]=LED_Population[i][j];
            SLED[i]=Amp_LED(chromosome,CIE_1931[i][0]);
            for(j=0;j<S_genes;j++)
            chromosome[j]=S_Population[i][j];
            Ss[i]=Amp_SL(chromosome,CIE_1931[i][0]);
            for(j=0;j<L_genes;j++)
            chromosome[j]=L_Population[i][j];
            SL[i]=Amp_SL(chromosome,CIE_1931[i][0]);
  }

   tristimulus_memory=tristimulus_value(CIE_1931,SLED);// LED tristimulus values & x y coordinate feedfack
    XLED=*(tristimulus_memory);
    YLED=*(tristimulus_memory+1);
    ZLED=*(tristimulus_memory+2);
    xled=*(tristimulus_memory+3);
    yled=*(tristimulus_memory+4);
    printf("xled=%f\n",xled);
    printf("yled=%f\n",yled);



   tristimulus_memory=tristimulus_value(CIE_1931,Ss);// YAG tristimulus values & x y coordinate feedfack
    Xs=*(tristimulus_memory);
    Ys=*(tristimulus_memory+1);
    Zs=*(tristimulus_memory+2);
    xs=*(tristimulus_memory+3);
    ys=*(tristimulus_memory+4);
    printf("xs=%f\n",xs);
    printf("ys=%f\n",ys);


   tristimulus_memory=tristimulus_value(CIE_1931,SL);// YAG tristimulus values & x y coordinate feedfack
    XL=*(tristimulus_memory);
    YL=*(tristimulus_memory+1);
    ZL=*(tristimulus_memory+2);
    xl=*(tristimulus_memory+3);
    yl=*(tristimulus_memory+4);
    printf("xl=%f\n",xl);
    printf("yl=%f\n",yl);

    printf("-------------------------------------------\n");
    for(i=0;i<Tc_data_length;i++){
    ASL_memory=Apsl(Tc_data[i][1],Tc_data[i][2],XLED,YLED,ZLED,Xs,Ys,Zs,XL,YL,ZL);
    AS[i]=*(ASL_memory);
    AL[i]=*(ASL_memory+1);


   }


    for(i=0;i<Tc_data_length;i++){
    if(i<46){
     printf("----------------------Tc=%d K---------------------\n",4000+100*i);
     printf("AS=%f\n",AS[i]);
     printf("AL=%f\n",AL[i]);
     for(j=0;j<n_chromosomes;j++)
     Stotal[j][i]=SLED[j]+Ss[j]*AS[i]+SL[j]*AL[i];
             }


    else if(i<49){
     printf("----------------------Tc=%d K---------------------\n",8500+500*(i-45));
     printf("AS=%f\n",AS[i]);
     printf("AL=%f\n",AL[i]);
     for(j=0;j<n_chromosomes;j++)
     Stotal[j][i]=SLED[j]+Ss[j]*AS[i]+SL[j]*AL[i];
    }
    else if(i<54){
     printf("----------------------Tc=%d K---------------------\n",10000+1000*(i-48));
     printf("AS=%f\n",AS[i]);
     printf("AL=%f\n",AL[i]);
     for(j=0;j<n_chromosomes;j++)
     Stotal[j][i]=SLED[j]+Ss[j]*AS[i]+SL[j]*AL[i];
     }
    else{
     printf("----------------------Tc=%d K---------------------\n",15000+5000*(i-53));
     printf("AS=%f\n",AS[i]);
     printf("AL=%f\n",AL[i]);
     for(j=0;j<n_chromosomes;j++)
     Stotal[j][i]=SLED[j]+Ss[j]*AS[i]+SL[j]*AL[i];
     }
    }


    for(i=0;i<1;i++){
      printf("----------------------------------------------------Stotal_%d K-------------------------------------------------------\n",4000+100*i);
       for(j=0;j<n_chromosomes;j++)
         std::cout << Stotal[j][i] << "            \t";
         std::cout << std::endl;

     }

    getch();
    return 0;

}

