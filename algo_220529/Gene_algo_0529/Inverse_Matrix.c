#include<stdio.h>
#include<stdlib.h>

double matrix_inv(double* p, double* result)
{
	double **input,**Inverse,localVariable;
	double* temprow;
	int i,j,k,sizeOfMatrix=8;



	input = (double **)malloc(sizeOfMatrix*sizeof(double *));

	for(i=0;i<sizeOfMatrix;i++)
		input[i]=(double *)malloc(sizeOfMatrix*sizeof(double));
    temprow=(double*)malloc(sizeOfMatrix*sizeof(double));
	Inverse=(double **)malloc(sizeOfMatrix*sizeof(double *));

		for(i=0;i<sizeOfMatrix;i++){
        for(j=0;j<sizeOfMatrix;j++)
        {
            input[i][j]=*(p+sizeOfMatrix*i+j);
          //  printf("%f\t",input[i][j]);
        }
     //   printf("%\n");
	}


	for(i=0;i<sizeOfMatrix;i++)
	{

		Inverse[i]=(double *)malloc(sizeOfMatrix*sizeof(double));
	}



	for(i=0;i<sizeOfMatrix;i++)
	for(j=0;j<sizeOfMatrix;j++)
	if(i==j)
	Inverse[i][j]=1;
	else
	Inverse[i][j]=0;


	for(k=0;k<sizeOfMatrix;k++)
	{
        if(input[k][k]==0)
        {
            for(j=k+1; j<sizeOfMatrix; j++)
            {
                if(input[j][k]!=0)
                    break;
            }

            if(j==sizeOfMatrix)
            {
           //     printf("\nMATRIX IS NOT INVERSIBLE\n\n");
                return 0;
            }
            temprow=input[k];
            input[k]=input[j];
            input[j]=temprow;
            temprow=Inverse[k];
            Inverse[k]=Inverse[j];
            Inverse[j]=temprow;
        }
		localVariable=input[k][k];
		for(j=0;j<sizeOfMatrix;j++)
		{
			input[k][j]/=localVariable;
			Inverse[k][j]/=localVariable;

		}
		for(i=0;i<sizeOfMatrix;i++)
		{
			localVariable = input[i][k];
			for(j=0;j<sizeOfMatrix;j++)
			{
				if(i==k)
					break;
				input[i][j] -= input[k][j]*localVariable;
				Inverse[i][j] -= Inverse[k][j]*localVariable;
			}
		}
	}

	//printf("The inverse matrix is:\n");

	for(i=0;i<sizeOfMatrix;i++)
	{
		for(j=0;j<sizeOfMatrix;j++){
			//printf("%f	",Inverse[i][j]);
			*(result +sizeOfMatrix*i+j)=Inverse[i][j];
		}
	//	printf("\n");
	}
	return 0;
}
