#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"TCS_Excel_fileopen.h"
#define MAX_LINE_SIZE 3500



int TCS_Excelopen(int argc, const char * argv[],int init_value ,int interval,int data_length,int TCS_width,double TCS[data_length][TCS_width]) {



    double temp1[402][15];

    char file_name1[] = "TCS_1nm_data.csv";
    FILE *fp1;
    fp1 = fopen(file_name1, "r");

    if (!fp1) {
        fprintf(stderr, "failed to open file for reading\n");
        return 1;
    }

    char line[MAX_LINE_SIZE];
    char *result = NULL;
    int i=0;

    while(fgets(line, MAX_LINE_SIZE, fp1) != NULL) {

        result = strtok(line, ",");
        int j=0;

        while( result != NULL ) {


            temp1[i][j]= atof(result);

            j++;


            result = strtok(NULL, ",");

        }

        i++;
    }
    int k=0;
   for(int i=init_value-379;i<data_length*interval+(init_value-379);i+=interval){
            TCS[i-(init_value-379)-(interval-1)*k][0]=temp1[i][1];
            TCS[i-(init_value-379)-(interval-1)*k][1]=temp1[i][2];
            TCS[i-(init_value-379)-(interval-1)*k][2]=temp1[i][3];
            TCS[i-(init_value-379)-(interval-1)*k][3]=temp1[i][4];
            TCS[i-(init_value-379)-(interval-1)*k][4]=temp1[i][5];
            TCS[i-(init_value-379)-(interval-1)*k][5]=temp1[i][6];
            TCS[i-(init_value-379)-(interval-1)*k][6]=temp1[i][7];
            TCS[i-(init_value-379)-(interval-1)*k][7]=temp1[i][8];
            TCS[i-(init_value-379)-(interval-1)*k][8]=temp1[i][9];
            TCS[i-(init_value-379)-(interval-1)*k][9]=temp1[i][10];
            TCS[i-(init_value-379)-(interval-1)*k][10]=temp1[i][11];
            TCS[i-(init_value-379)-(interval-1)*k][11]=temp1[i][12];
            TCS[i-(init_value-379)-(interval-1)*k][12]=temp1[i][13];
            TCS[i-(init_value-379)-(interval-1)*k][13]=temp1[i][14];


            k++;

    }


    fclose (fp1);

}

