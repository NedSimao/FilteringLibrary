
#include "Filters.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.14f

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

/********************************************************************************************************
 *                              NOTCH FILTER
********************************************************************************************************/


void NOTCHFilter_Init(NOTCHFilter *filter, float centerFreqHz, float notchWidthHz, float sampleTimeS){
//filter frequency to angular (rad/s)
float w0_rps=2.0f * PI *centerFreqHz;
float ww_rps=2.0f * PI *notchWidthHz;

//pre warp center frequency
float w0_pw_rps=(2.0f/sampleTimeS) * tanf(0.5 * w0_rps * sampleTimeS);

//computing filter coefficients

filter->alpha=4.0f + w0_rps*w0_pw_rps*sampleTimeS*sampleTimeS;
filter->beta=2.0f*ww_rps*sampleTimeS;

//clearing input and output  buffers

for (uint8_t n=0; n<3; n++){
    filter->vin[n]=0;
    filter->vout[n]=0;
}

}

float NOTCHFilter_Update(NOTCHFilter *filter, float vin){
    //shifting samples
    filter->vin[2]=filter->vin[1];
    filter->vin[1]=filter->vin[0];

    filter->vout[2]=filter->vout[1];
    filter->vout[1]=filter->vout[0];

    filter->vin[0]=vin;

    //compute new output
    filter->vout[0]=(filter->alpha*filter->vin[0] + 2.0f *(filter->alpha -8.0f)*filter->vin[1] + filter->alpha*filter->vin[2]
    -(2.0f*(filter->alpha-8.0f)*filter->vout[1]+(filter->alpha-filter->beta)*filter->vout[2]))/(filter->alpha+filter->beta);


    return (filter->vout[0]);


}

