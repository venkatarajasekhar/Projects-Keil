


#ifndef __Zettlex_H
#define __Zettlex_H

#include <stdint.h>

typedef	__packed struct
{
	unsigned char PV  :1;  // Position Valid flag.  Set to 1 when data is valid, otherwise set to 0
	unsigned char ZPD :1;  // Zero Point Default.  Set to 1 when the Zero Point is at Factory Default, otherwise set to 0.
	unsigned char BadFrame :1; // 1 - Bad, 0 - norm
	
}FlafsZettlex_t  __attribute__((bitband));


typedef __packed struct
{
	uint16_t Crc;
	uint32_t Position;
	FlafsZettlex_t  Flags;
}DataZettlex_t;


void ReceivedDataZettlex(uint8_t b);
void ProcessData(void);
void ZettlexInitUART(void);
uint16_t CRC16_BUYPASS(uint8_t *data, uint8_t len);
uint32_t GetZettlexPosition (void);


#endif
