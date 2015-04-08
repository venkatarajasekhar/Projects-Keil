//============================================================
//
// File Name    : 'Keys.h'
// Project      :  Универсальный контроллер
// Title        :
// Author       : Федорин А.К.
// Created      : 25/02/2014
// Revised      :
// Version      : 1
// Target MCU   : STM32F103VET6
// Compiler     : Keil 4.71.2.0
// Editor Tabs  : 2
//
// NOTE:
//============================================================
#ifndef __KEYS_H        // Блокируем повторное включение этого модуля
#define __KEYS_H

//<<< Use Configuration Wizard in Context Menu >>>

// <h>Pin Configuration
// ===================
//
// <h>Input1
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
#ifndef PORT_INPUT_1
 #define PORT_INPUT_1     1
#endif
#if PORT_INPUT_1 == 1
#define		GPIO_IN_1	 		GPIOA
#elif PORT_INPUT_1 == 2
#define		GPIO_IN_1	 		GPIOB
#elif PORT_INPUT_1 == 3
#define		GPIO_IN_1	 		GPIOC
#elif PORT_INPUT_1 == 4
#define		GPIO_IN_1	 		GPIOD
#elif PORT_INPUT_1 == 5
#define		GPIO_IN_1	 		GPIOE
#elif PORT_INPUT_1 == 6
#define		GPIO_IN_1	 		GPIOF
#elif PORT_INPUT_1 == 7
#define		GPIO_IN_1	 		GPIOG
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_INPUT_1
 #define PIN_INPUT_1     3
#endif

// </h>
// <h>Input2
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
#ifndef PORT_INPUT_2
 #define PORT_INPUT_2     1
#endif
#if PORT_INPUT_2 == 1
#define		GPIO_IN_2	 		GPIOA
#elif PORT_INPUT_2 == 2
#define		GPIO_IN_2	 		GPIOB
#elif PORT_INPUT_2 == 3
#define		GPIO_IN_2	 		GPIOC
#elif PORT_INPUT_2 == 4
#define		GPIO_IN_2	 		GPIOD
#elif PORT_INPUT_2 == 5
#define		GPIO_IN_2	 		GPIOE
#elif PORT_INPUT_2 == 6
#define		GPIO_IN_2	 		GPIOF
#elif PORT_INPUT_2 == 7
#define		GPIO_IN_2	 		GPIOG
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_INPUT_2
 #define PIN_INPUT_2     1
#endif

// </h>
// <h>Input3
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
#ifndef PORT_INPUT_3
 #define PORT_INPUT_3     1
#endif
#if PORT_INPUT_3 == 1
#define		GPIO_IN_3	 		GPIOA
#elif PORT_INPUT_3 == 2
#define		GPIO_IN_3	 		GPIOB
#elif PORT_INPUT_3 == 3
#define		GPIO_IN_3	 		GPIOC
#elif PORT_INPUT_3 == 4
#define		GPIO_IN_3	 		GPIOD
#elif PORT_INPUT_3 == 5
#define		GPIO_IN_3	 		GPIOE
#elif PORT_INPUT_3 == 6
#define		GPIO_IN_3	 		GPIOF
#elif PORT_INPUT_3 == 7
#define		GPIO_IN_3	 		GPIOG
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_INPUT_3
 #define PIN_INPUT_3     11
#endif

// </h>
// <h>Input4
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
#ifndef PORT_INPUT_4
 #define PORT_INPUT_4     2
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_INPUT_4
 #define PIN_INPUT_4     0
#endif
#if PORT_INPUT_4 == 1
#define		GPIO_IN_4	 		GPIOA
#elif PORT_INPUT_4 == 2
#define		GPIO_IN_4	 		GPIOB
#elif PORT_INPUT_4 == 3
#define		GPIO_IN_4	 		GPIOC
#elif PORT_INPUT_4 == 4
#define		GPIO_IN_4	 		GPIOD
#elif PORT_INPUT_4 == 5
#define		GPIO_IN_4	 		GPIOE
#elif PORT_INPUT_4 == 6
#define		GPIO_IN_4	 		GPIOF
#elif PORT_INPUT_4 == 7
#define		GPIO_IN_4	 		GPIOG
#endif


// </h>
// <h>Input5
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
#ifndef PORT_INPUT_5
 #define PORT_INPUT_5     1
#endif
#if PORT_INPUT_5 == 1
#define		GPIO_IN_5	 		GPIOA
#elif PORT_INPUT_5 == 2
#define		GPIO_IN_5	 		GPIOB
#elif PORT_INPUT_5 == 3
#define		GPIO_IN_5	 		GPIOC
#elif PORT_INPUT_5 == 4
#define		GPIO_IN_5	 		GPIOD
#elif PORT_INPUT_5 == 5
#define		GPIO_IN_5	 		GPIOE
#elif PORT_INPUT_5 == 6
#define		GPIO_IN_5	 		GPIOF
#elif PORT_INPUT_5 == 7
#define		GPIO_IN_5	 		GPIOG
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_INPUT_5
 #define PIN_INPUT_5     12
#endif

// </h>

// <h>Input6
// ===================
//   <o>        PORT To Use
//                      <1=> PORTA
//                      <2=> PORTB
//                      <3=> PORTC
//                      <4=> PORTD
//                      <5=> PORTE
//                      <6=> PORTF
//                      <7=> PORTG
#ifndef PORT_INPUT_6
 #define PORT_INPUT_6     4
#endif
#if PORT_INPUT_6 == 1
#define		GPIO_IN_6	 		GPIOA
#elif PORT_INPUT_6 == 2
#define		GPIO_IN_6	 		GPIOB
#elif PORT_INPUT_6 == 3
#define		GPIO_IN_6	 		GPIOC
#elif PORT_INPUT_6 == 4
#define		GPIO_IN_6	 		GPIOD
#elif PORT_INPUT_6 == 5
#define		GPIO_IN_6	 		GPIOE
#elif PORT_INPUT_6 == 6
#define		GPIO_IN_6	 		GPIOF
#elif PORT_INPUT_1 == 7
#define		GPIO_IN_6	 		GPIOG
#endif

//   <o>				Pin To Use <0-15>
#ifndef PIN_INPUT_6
 #define PIN_INPUT_6     13
#endif

// </h>

// </h>

//<<< end of configuration section >>>



// #define   NO_EVENT					((u8) 0x00)
// #define   KEY_PRESS				((u8) 0x20)
// #define   KEY_RELES				((u8) 0x40)
// #define   KEY_LONG_PRESS		((u8) 0x60)
// #define   KEY_BAD_KEY			((u8) 0x80)


#define		C_MAX_NUM_VALUES	((uint8_t)8)
#define  	C_NUM_KEYS				((uint8_t)2)

enum
{
	DRIVER_OCTV,//подтяжки
	DRIVER_FAULT,//
};


//============================================================
//	Секция прототипов функций 
//============================================================
unsigned char	HandlerKeys (void);
unsigned char	CheckKey (unsigned char  num_key );
void InitInput (void);

//============================================================
#endif


