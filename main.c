#include "./src/Filters.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
      BE SURE TO MATCH THE NYQUIST STANDARDS fc<Fs/2
*/
      
#define PLOT_POINTS     100
#define SAMPLE_TIME_S   0.001
#define CUTOFFFREQ_HZ   50
#define sine_freq       40
#define sine_freq_1     500
#define HFC 50
#define LFC 100

LPFilter RCFilter;
HPFilter HRCFilter;
PBFilter PBF;

int main(){

float samp_rate = 2000; // sampling rate
float samp_time = 1/samp_rate; // sampling time
float pi = 3.14159;
    
// Initializing file pointer.
FILE * p_file;

float processData=0.0;
float signalRawData=0.0;

double theta_0 = 0; // theta for first sine wave

double theta_1 = 0; // theta for second sine wave

p_file = fopen("ProcessData_0.txt", "w");
// If p_file is a null pointer, the file opening failed.
if (p_file == NULL) {
    printf("File does not exist!");
    return 0;
}


//During the initialization execute the INIT API
LPFilter_Init(&RCFilter, CUTOFFFREQ_HZ, SAMPLE_TIME_S);
//HPFilter_Init(&HRCFilter, CUTOFFFREQ_HZ, SAMPLE_TIME_S);


//During the acquisition of data, process the signal 
printf("angle; RAW DATA; FILTERED DATA\n");
fputs("angle;RAW DATA;FILTERED DATA\n",p_file);

for (uint8_t N=0; N<PLOT_POINTS; N++){
    //computing angles
    theta_0     = 2*pi*sine_freq*N*samp_time;//*(pi/180);
    theta_1     = 2*pi*sine_freq_1*N*samp_time;//*(pi/180);

    //generate a sample from the signal
    //signalRawData = 50*sin(theta_0); //simple signal
    signalRawData = 50*sin(theta_0) + 50*sin(theta_1); //mixed signal


    //process the signal 
  processData=LPFilter_Update(&RCFilter, signalRawData);
  //processData=HPFilter_Update(&HRCFilter, signalRawData);

    //present the data in csv format
    printf("%d;%f;%f\n", N, signalRawData, processData);
    // Writting name into the file.
    fprintf(p_file, "%d;%f;%f\n", N, signalRawData, processData);

}
  // Close opened file.
  fclose(p_file);

  return 0;
}





