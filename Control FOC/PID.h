


#ifndef __PID_H
#define __PID_H

#include <stdint.h>

typedef struct
{
	uint32_t Position;
  double dState;          // Last position input
  double iState;          // Integrator state
	double pMax, pMin;     	// Maximum and minimum allowable proportions state
  double iMax, iMin;     	// Maximum and minimum allowable integrator state
  double    iGain,        // integral gain
            pGain,        // proportional gain
            dGain;        // derivative gain
} SPid;


typedef enum
{
	OFF,
	ON,
} t_StatePid;

void SetPosition(uint32_t position);
void SetPIDdState(uint32_t position);
void SetPIDiState(uint32_t position);
void SetPIDiMax(uint32_t position);
void SetPIDiMin(uint32_t position);
void SetPIDiGain(uint32_t position);
void SetPIDpGain(uint32_t position);
void SetPIDdGain(uint32_t position);

void InitPID(void);
void ControlPID(void);
double UpdatePID(SPid * pid, double error, double position);
void SetStatePid(t_StatePid _State);


#endif