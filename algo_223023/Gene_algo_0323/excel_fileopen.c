#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "excel_fileopen.h"




int CIE_Excelopen(int argc, const char * argv[],int interval,int CIE_1931_length,int CIE_1931_width,double temp[CIE_1931_length][CIE_1931_width]) {


    double temp1[535][11];

    char file_name[] = "all_1nm_data.csv";
    FILE *fp;
    fp = fopen(file_name, "r");

    if (!fp) {
        fprintf(stderr, "failed to open file for reading\n");
        return 1;
    }

    char line[MAX_LINE_SIZE];
    char *result = NULL;
    int i=0;

    while(fgets(line, MAX_LINE_SIZE, fp) != NULL) {

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
   for(int i=64;i<CIE_1931_length*interval+64;i+=interval){
            temp[i-64-(interval-1)*k][0]=temp1[i][0];
            temp[i-64-(interval-1)*k][1]=temp1[i][5];
            temp[i-64-(interval-1)*k][2]=temp1[i][6];
            temp[i-64-(interval-1)*k][3]=temp1[i][7];
            k++;

    }
    fclose (fp);

}
