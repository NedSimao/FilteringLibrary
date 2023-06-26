#include "./src/Filters.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define PLOT_POINTS     100
#define SAMPLE_TIME_S   0.01
#define CUTOFFFREQ_HZ   5

LPFilter RCFilter;

int main(){

// Initializing file pointer.
FILE * p_file;

float processData=0.0;
float signalRawData=0.0;

p_file = fopen("ProcessData_0.txt", "w");
// If p_file is a null pointer, the file opening failed.
if (p_file == NULL) {
    printf("File does not exist!");
    return 0;
}


//During the initialization execute the INIT API
LPFilter_Init(&RCFilter, CUTOFFFREQ_HZ, SAMPLE_TIME_S);

//During the acquisition of data, process the signal 
printf("angle; RAW DATA; FILTERED DATA\n");
fputs("angle;RAW DATA;FILTERED DATA\n",p_file);

for (uint8_t N=0; N<PLOT_POINTS; N+=3){
    //generate a sample from the signal
    signalRawData = 50*sin(N*3.141/180);

    //process the signal 
    processData=LPFilter_Update(&RCFilter, signalRawData);

    //present the data in csv format
    printf("%d;%f;%f\n", N, signalRawData, processData);
    // Writting name into the file.
    fprintf(p_file, "%d;%f;%f\n", N, signalRawData, processData);

}
  // Close opened file.
  fclose(p_file);

  return 0;
}