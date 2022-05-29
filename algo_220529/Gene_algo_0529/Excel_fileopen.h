#ifndef _EXCEL_FILEOPEN_H_
#define _EXCEL_FILEOPEN_H_


//宣告函數原型
int TCS_Excelopen(int argc, const char * argv[],int init_value ,int interval,int data_length,int TCS_width,double TCS[data_length][TCS_width]);
int CIE_Excelopen(int argc, const char * argv[],int init_value,int interval,int data_length,int data_width,double CIE1931[data_length][data_width]);
int Daylight_Excelopen(int argc, const char * argv[],int init_value ,int interval,int Daylght_length,int Daylght_width,double Daylight_SPD_10nm[Daylght_length][Daylght_width]);


#endif
