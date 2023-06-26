
#include "Filters.h"


/********************************************************************************************************
 *                              LOW PASS FILTER
********************************************************************************************************/

void LPFilter_Init(LPFilter *filter, float cutoffFreqHz, float sampleTimeS){
float RC=0.0f;
RC=1.0f/(6.28f*cutoffFreqHz);
filter->coef[0]=sampleTimeS/(sampleTimeS+RC);
filter->coef[1]=RC/(sampleTimeS+RC);

filter->v_out[0]=0.0f;
filter->v_out[1]=0.0f;

}


float LPFilter_Update(LPFilter *filter, float v_in){

filter->v_out[1]=filter->v_out[0];
filter->v_out[0]=(filter->coef[0]*v_in) + (filter->coef[1]*filter->v_out[1]);

return (filter->v_out[0]);

}


/********************************************************************************************************
 *                              HIGH PASS FILTER
********************************************************************************************************/
void HPFilter_Init(HPFilter *filter, float cutoffFreqHz, float sampleTimeS){
float RC=0.0f;
RC=1.0f/(6.28f*cutoffFreqHz);

filter->coef=RC/(sampleTimeS+RC);

filter->v_in[0]=0.0f;
filter->v_in[1]=0.0f;

filter->v_out[0]=0.0f;
filter->v_out[1]=0.0f;

}


float HPFilter_Update(HPFilter *filter, float v_in){
filter->v_in[0]=v_in;
filter->v_in[1]=filter->v_in[0];

filter->v_out[1]=filter->v_out[0];

filter->v_out[0]=filter->coef * (filter->v_in[0] - filter->v_in[1]+filter->v_out[1]);

return (filter->v_out[0]);
}

/********************************************************************************************************
 *                              BAND PASS FILTER
********************************************************************************************************/


void PBFilter_Init(PBFilter *filter, float HPF_cutoffFreqHz, float LPF_cutoffFreqHz, float sampleTimeS){
LPFilter_Init(&filter->lpf, LPF_cutoffFreqHz, sampleTimeS);
HPFilter_Init(&filter->lpf, HPF_cutoffFreqHz, sampleTimeS);
filter->out_in=0.0f;

}

float PBFilter_Update(PBFilter *filter, float v_in){
filter->out_in=HPFilter_Update(&filter->hpf, v_in);

filter->out_in=(&filter->lpf, filter->out_in);

return (filter->out_in);
}