


#ifndef __CONFIG_H
#define __CONFIG_H

#include "FOC_type.h"
#include "UserInterfaceClass.h"

#define pADDRESS ((FOC_t*)( ADDRESS ))
extern const FOC_t* pFOC;


FOC_t* GetPointToFunctionFOC(void);
void SystemInitialize(void);
void Blinky(void);


#endif

