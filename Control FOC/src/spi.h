
#ifndef _SPI_DRIVER        // Блокируем повторное включение этого модуля
#define _SPI_DRIVER
#include "stdint.h"

//<<< Use Configuration Wizard in Context Menu >>>


//=========================================================================== SPI Configuration
// <e0> SPI Configuration
//--------------------------------------------------------------------------- SPI
#ifndef SPI_EN
 #define SPI_EN    1
#endif
// ===================
//   <o>        Сhoice of room SPI
//                      <1=> SPI1
//                      <2=> SPI2
//                      <3=> SPI3
#ifndef SPI_NUM
 #define SPI_NUM    2
#endif


// <h>Pin Configuration
// ===================
//
// <h>CS
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
//                      <8=> PORTH
//                      <9=> PORTI
#ifndef CS_PORT
 #define CS_PORT     5
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_CS
 #define PIN_CS     15
#endif

// </h>

// <h>SCK
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
//                      <8=> PORTH
//                      <9=> PORTI
#ifndef SCK_PORT
 #define SCK_PORT     9
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_SCK
 #define PIN_SCK     1
#endif

// </h>

// <h>MISO
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
//                      <8=> PORTH
//                      <9=> PORTI
#ifndef MISO_PORT
 #define MISO_PORT     9
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_MISO
 #define PIN_MISO     2
#endif

// </h>

// <h>MOSI
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
//                      <8=> PORTH
//                      <9=> PORTI
#ifndef MOSI_PORT
 #define MOSI_PORT     9
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_MOSI
 #define PIN_MOSI     3
#endif

// </h>

// </h>

// </e> End of SPI Configuration
#define __SPI_SETUP             1


//<<< end of configuration section >>>

// 
#if CS_PORT == 1
#define		GPIO_CS	 		GPIOA
#elif CS_PORT == 2
#define		GPIO_CS	 		GPIOB
#elif CS_PORT == 3
#define		GPIO_CS	 		GPIOC
#elif CS_PORT == 4
#define		GPIO_CS	 		GPIOD
#elif CS_PORT == 5
#define		GPIO_CS	 		GPIOE
#elif CS_PORT == 6
#define		GPIO_CS	 		GPIOF
#elif CS_PORT == 7
#define		GPIO_CS	 		GPIOG
#elif CS_PORT == 8
#define		GPIO_CS	 		GPIOH
#elif CS_PORT == 9
#define		GPIO_CS	 		GPIOI
#endif


#if SCK_PORT == 1
#define		GPIO_SCK	 		GPIOA
#elif SCK_PORT == 2
#define		GPIO_SCK	 		GPIOB
#elif SCK_PORT == 3
#define		GPIO_SCK	 		GPIOC
#elif SCK_PORT == 4
#define		GPIO_SCK	 		GPIOD
#elif SCK_PORT == 5
#define		GPIO_SCK	 		GPIOE
#elif SCK_PORT == 6
#define		GPIO_SCK	 		GPIOF
#elif SCK_PORT == 7
#define		GPIO_SCK	 		GPIOG
#elif SCK_PORT == 8
#define		GPIO_SCK	 		GPIOH
#elif SCK_PORT == 9
#define		GPIO_SCK	 		GPIOI
#endif


#if MOSI_PORT == 1
#define		GPIO_MOSI	 		GPIOA
#elif MOSI_PORT == 2
#define		GPIO_MOSI	 		GPIOB
#elif MOSI_PORT == 3
#define		GPIO_MOSI	 		GPIOC
#elif MOSI_PORT == 4
#define		GPIO_MOSI	 		GPIOD
#elif MOSI_PORT == 5
#define		GPIO_MOSI	 		GPIOE
#elif MOSI_PORT == 6
#define		GPIO_MOSI	 		GPIOF
#elif MOSI_PORT == 7
#define		GPIO_MOSI	 		GPIOG
#elif MOSI_PORT == 8
#define		GPIO_MOSI	 		GPIOH
#elif MOSI_PORT == 9
#define		GPIO_MOSI	 		GPIOI
#endif


#if MISO_PORT == 1
#define		GPIO_MISO	 		GPIOA
#elif MISO_PORT == 2
#define		GPIO_MISO	 		GPIOB
#elif MISO_PORT == 3
#define		GPIO_MISO	 		GPIOC
#elif MISO_PORT == 4
#define		GPIO_MISO	 		GPIOD
#elif MISO_PORT == 5
#define		GPIO_MISO	 		GPIOE
#elif MISO_PORT == 6
#define		GPIO_MISO	 		GPIOF
#elif MISO_PORT == 7
#define		GPIO_MISO	 		GPIOG
#elif MISO_PORT == 8
#define		GPIO_MISO	 		GPIOH
#elif MISO_PORT == 9
#define		GPIO_MISO	 		GPIOI
#endif

#if SPI_NUM == 1
#define		SPI	 					SPI1
#elif SPI_NUM == 2
#define		SPI	 					SPI2
#elif SPI_NUM == 3
#define		SPI	 					SPI3
#endif

#define  CHIP_SELECT_ON  		GPIO_SetBits(GPIO_CS, 1<< PIN_CS);
#define  CHIP_SELECT_OFF		GPIO_ResetBits(GPIO_CS, 1<< PIN_CS);


#define CMD_READ		0x8000
#define CMD_WRITE		0x0000

#define ADRESS_STATUS_REG1		(0 << 11)
#define ADRESS_STATUS_REG2		(1 << 11)
#define ADRESS_CONTROL_REG1		(2 << 11)
#define ADRESS_CONTROL_REG2		(3 << 11)

// For CONTROL_REG1
#define GateDriveCurrent_1700mA		0
#define GateDriveCurrent_700mA		1
#define GateDriveCurrent_250mA		2

#define NORMAL_MODE 				(0 << 2)
#define RESET_GATE_DRIVER 	(1 << 2)

#define PWM_INPUTS_6 	(0 << 3)
#define PWM_INPUTS_3 	(1 << 3)

#define CURRENTLIMIT				(0 << 4)
#define OC_LATCH_SHUT_DOWN 	(1 << 4)
#define REPORT_ONLY					(2 << 4)
#define OC_DISABLED					(3 << 4)

#define OC_ADJ_SET_60			(0 << 6)
#define OC_ADJ_SET_68			(1 << 6)
#define OC_ADJ_SET_76			(2 << 6)
#define OC_ADJ_SET_86			(3 << 6)
#define OC_ADJ_SET_97			(4 << 6)
#define OC_ADJ_SET_109		(5 << 6)
#define OC_ADJ_SET_123		(6 << 6)
#define OC_ADJ_SET_138		(7 << 6)
#define OC_ADJ_SET_155		(8 << 6)
#define OC_ADJ_SET_175		(9 << 6)
#define OC_ADJ_SET_197		(10 << 6)
#define OC_ADJ_SET_222		(11 << 6)
#define OC_ADJ_SET_250		(12 << 6)
#define OC_ADJ_SET_282		(13 << 6)
#define OC_ADJ_SET_317		(14 << 6)
#define OC_ADJ_SET_358		(15 << 6)
#define OC_ADJ_SET_403		(16 << 6)
#define OC_ADJ_SET_454		(17 << 6)
#define OC_ADJ_SET_511		(18 << 6)
#define OC_ADJ_SET_576		(19 << 6)
#define OC_ADJ_SET_648		(20 << 6)
#define OC_ADJ_SET_730		(21 << 6)
#define OC_ADJ_SET_822		(22 << 6)
#define OC_ADJ_SET_926		(23 << 6)
#define OC_ADJ_SET_1043		(24 << 6)
#define OC_ADJ_SET_1175		(25 << 6)
#define OC_ADJ_SET_1324		(26 << 6)
#define OC_ADJ_SET_1491		(27 << 6)
#define OC_ADJ_SET_1679		(28 << 6)
#define OC_ADJ_SET_1892		(29 << 6)
#define OC_ADJ_SET_2131		(30 << 6)
#define OC_ADJ_SET_2400		(31 << 6)

// For CONTROL_REG2
#define REPORT_BOTH_OT_AND_OC			0
#define REPORT_OT_ONLY						1
#define REPORT_OC_ONLY						2

#define GainOfShuntAmplifier_10V				(0 << 2)
#define GainOfShuntAmplifier_20V 				(1 << 2)
#define GainOfShuntAmplifier_40V				(2 << 2)
#define GainOfShuntAmplifier_80V				(3 << 2)

#define SHUNT_AMPLIFIER1_CONNECTS					(0 << 4)
#define SHUNT_AMPLIFIER1_DISCONNECTS			(1 << 4)

#define SHUNT_AMPLIFIER2_CONNECTS					(0 << 5)
#define SHUNT_AMPLIFIER2_DISCONNECTS			(1 << 5)

#define CYCLE_BY_CYCLE					(0 << 6)
#define OFF_TIME_CONTROL 				(1 << 6)


#define	TICK_DRV		20


typedef unsigned long long u64;

void InitSPI(void);
void delay_(volatile uint32_t nCount);
uint8_t DRV8301(void);

#endif

