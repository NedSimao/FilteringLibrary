#ifndef FILTERS_H
#define FILTERS_H

/********************************************************************************************************
 *                              LOW PASS FILTER
********************************************************************************************************/
typedef struct {
    float coef[2];
    float v_out[2];
}LPFilter;

void LPFilter_Init(LPFilter *filter, float cutoffFreqHz, float sampleTimeS);
float LPFilter_Update(LPFilter *filter, float v_in);


/********************************************************************************************************
 *                              HIGH PASS FILTER
********************************************************************************************************/
typedef struct {
    float coef;
    float v_out[2];
    float v_in[2];
}HPFilter;

void HPFilter_Init(HPFilter *filter, float cutoffFreqHz, float sampleTimeS);
float HPFilter_Update(HPFilter *filter, float v_in);



/********************************************************************************************************
 *                              BAND PASS FILTER
********************************************************************************************************/

typedef struct {
    LPFilter lpf;
    HPFilter hpf;
    float out_in;
}PBFilter;



void PBFilter_Init(PBFilter *filter, float HPF_cutoffFreqHz, float LPF_cutoffFreqHz, float sampleTimeS);
float PBFilter_Update(PBFilter *filter, float v_in);

/********************************************************************************************************
 *                              NOTCH FILTER
********************************************************************************************************/




#endif FILTERS_H