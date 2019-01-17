/*
 * LED.h
 *
 * Created: 20-03-2015 15:18:27
 *  Author: s113570
 */ 


#ifndef LED_H_
#define LED_H_
#include "asf.h"
//#include "Board.h"
#include "main.h"

#define LED_SCALE_MAX_VALUE 10000
#define LED_SCALE_FACTOR (LED_SCALE_MAX_VALUE/256)


#define LED_RED		0xFF0000
#define LED_GREEN	0x00FF00
#define LED_BLUE	0x0000FF
#define LED_YELLOW	0xFFFF00
#define LED_PURPLE	0xFF00FF
#define LED_CYAN	0x00FFFF
#define LED_WHITE	0xFFFFFF
#define LED_OFF		0x000000

void LED_Init(void);

void LED_Set_Color(uint32_t Hex_Color_Code);
void LED_Set_Color_RGB(uint32_t Red, uint32_t Green, uint32_t Blue);

#endif /* LED_H_ */