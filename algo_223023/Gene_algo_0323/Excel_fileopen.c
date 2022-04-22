#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Excel_fileopen.h"
#define MAX_LINE_SIZE 3500




int CIE_Excelopen(int argc, const char * argv[],int init_value ,int interval,int data_length,int data_width,double CIE1931[data_length][data_width]) {


    double temp3[535][11];

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


            temp3[i][j]= atof(result);

            j++;


            result = strtok(NULL, ",");

        }

        i++;
    }
    int k=0;
   for(int i=init_value-296;i<data_length*interval+(init_value-296);i+=interval){
            CIE1931[i-(init_value-296)-(interval-1)*k][0]=temp3[i][0];
            CIE1931[i-(init_value-296)-(interval-1)*k][1]=temp3[i][5];
            CIE1931[i-(init_value-296)-(interval-1)*k][2]=temp3[i][6];
            CIE1931[i-(init_value-296)-(interval-1)*k][3]=temp3[i][7];
            k++;

    }


    fclose (fp);

}

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
        for(int j=0;j<TCS_width;j++){

            TCS[i-(init_value-379)-(interval-1)*k][j]=temp1[i][j+1];
        }


            k++;

    }


    fclose (fp1);

}
int Daylight_Excelopen(int argc, const char * argv[],int init_value ,int interval,int Daylght_length,int Daylght_width,double Daylight_SPD_10nm[Daylght_length][Daylght_width]) {



    double temp1[Daylght_length+1][Daylght_width];

    char file_name1[] = "DaylightCIECalculator.csv";
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

      for(int i=init_value-379;i<Daylght_length*interval+(init_value-379);i+=interval){
        for(int j=0;j<Daylght_width;j++){

            Daylight_SPD_10nm[i-(init_value-379)-(interval-1)*k][j]=temp1[i][j];
        }


            k++;

    }


    fclose (fp1);

}

