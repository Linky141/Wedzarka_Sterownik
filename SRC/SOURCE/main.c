/*
 * main.c
 *
 *  Created on: 17 gru 2019
 *      Author: Tomasz Bielas
 *
 *
 *
 */

/* IMPLEMENTATIONS */
#include <avr\io.h>
#include <stdbool.h>
#include "../../Libraries/Headers/delay.h"
#include "../../Libraries/Headers/lcd.h"
#include "../HEADERS/termo.h"

/* DEFINITHIONS */
#define BTN_PLUS (!(PINB & 0x1))
#define BTN_MINUS (!(PINB & 0x2))
#define BTN_OK (!(PINB & 0x4))
#define LCD_REFRESH_TIME 20000
#define BUTTON_PRESS_DELAY 50
#define MAXIMUM_TEMPERATURE 200
#define MINIMUM_TEMPERATURE 0

/* DECLARATIONS FUNCTIONS */
void Initialization();

void MainLoop();

void ALARM();

void ALARM2();

void Lamp(bool mode);

void beep(uint16_t time, uint16_t delay);

/* DECLARATIONS VARIABLES*/
uint16_t minTemp = 0;
uint16_t maxTemp = 0;
uint16_t actTemp = 0;
uint16_t thermoD0 = 4;
uint16_t thermoCS = 5;
uint16_t thermoCLK = 6;
bool overTempLock = false;
bool mute = false;
uint8_t histereze = 0;
uint16_t lcdRefreshClock = 0;

/* MAIN PROGRAM */
int main() {

	Initialization();
	MainLoop();

	return 0;
}

/* FUNCTIONS */
void Initialization() {

	MAX6675();
	/*Connect RS->PB0, RW->PB1, EN->PB2 and data bus to PORTB.4 to PORTB.7*/
	LCD_SetUp(PA_0, PA_1, PA_2, P_NC, P_NC, P_NC, P_NC, PA_3, PA_4, PA_5, PA_6);
	LCD_Init(2, 8);

	DDRB = 0x00;
	DDRD = 0xff;
	PORTB = 0xff;
	PORTD = 0xff;

	Lamp(true);
	beep(600, 200);
	beep(600, 300);
	beep(600, 200);
	Lamp(false);


	while (true) {
		if (lcdRefreshClock >= LCD_REFRESH_TIME) {
			LCD_Clear();
			LCD_XYPrintf(0, 0, "Min temp");
			LCD_XYPrintf(0, 1, ": %d", minTemp);
			lcdRefreshClock = 0;
		}
		if (BTN_PLUS && minTemp < MAXIMUM_TEMPERATURE) {
			minTemp++;
			DELAY_ms(BUTTON_PRESS_DELAY);
		}
		if (BTN_MINUS && minTemp > MINIMUM_TEMPERATURE) {
			minTemp--;
			DELAY_ms(BUTTON_PRESS_DELAY);
		}
		if (BTN_OK)
			break;
		lcdRefreshClock++;
	}
	LCD_Clear();
	LCD_XYPrintf(0, 0, "OK");
	beep(3000, 100);
	DELAY_ms(200);
	maxTemp = minTemp;

	while (!BTN_OK) {
		if (lcdRefreshClock >= LCD_REFRESH_TIME) {
			LCD_Clear();
			LCD_XYPrintf(0, 0, "Max temp");
			LCD_XYPrintf(0, 1, ": %d", maxTemp);
			lcdRefreshClock = 0;
		}
		if (BTN_PLUS && maxTemp < MAXIMUM_TEMPERATURE) {
			maxTemp++;
			DELAY_ms(BUTTON_PRESS_DELAY);
		}
		if (BTN_MINUS && maxTemp > MINIMUM_TEMPERATURE && maxTemp > minTemp) {
			maxTemp--;
			DELAY_ms(BUTTON_PRESS_DELAY);
		}
		lcdRefreshClock++;
	}

	LCD_Clear();
	LCD_XYPrintf(0, 0, "OK");
	beep(3000, 100);
	DELAY_ms(200);

	while (!BTN_OK) {
		if (lcdRefreshClock >= LCD_REFRESH_TIME) {
			LCD_Clear();
			LCD_XYPrintf(0, 0, "histerez");
			LCD_XYPrintf(0, 1, "e: %d", histereze);
			lcdRefreshClock = 0;
		}
		if (BTN_PLUS) {
			histereze++;
			DELAY_ms(BUTTON_PRESS_DELAY * 3);
		}
		if (BTN_MINUS && histereze > 0) {
			histereze--;
			DELAY_ms(BUTTON_PRESS_DELAY * 3);
		}
		lcdRefreshClock++;
	}


	LCD_Clear();
	LCD_XYPrintf(0, 0, "OK");
	beep(3000, 100);
	DELAY_ms(200);
	LCD_Clear();
	LCD_XYPrintf(0, 0, "Max:%d", maxTemp);
	LCD_XYPrintf(0, 1, "Min:%d", minTemp);
	DELAY_ms(1000);
	return;
}

void MainLoop() {
	LCD_Clear();
	lcdRefreshClock = 0;
	overTempLock = false;
	while (true) {
		if (lcdRefreshClock >= 1) {
			LCD_Clear();
			if (actTemp != -100)
				LCD_XYPrintf(0, 0, "TEMP:%d", actTemp);
			else {
				LCD_XYPrintf(0, 0, "TEMP:ERR");
				Lamp(true);
			}
			LCD_XYPrintf(0, 1, " %d/%d", minTemp, maxTemp);
			lcdRefreshClock = 0;
			//beep(200, 600);
		} else
			lcdRefreshClock++;
		actTemp = readCelsius();

		if ((actTemp > (maxTemp + histereze) || actTemp < (minTemp - histereze))
				&& overTempLock == false) {
			overTempLock = true;
			mute = false;
		}

		if (overTempLock == true) {
			Lamp(true);
			if (!mute){
			if(actTemp > (maxTemp + histereze + 20) || actTemp < (minTemp - histereze - 20)) ALARM2();
			else ALARM();
			}
			if (BTN_OK)
				mute = true;
		}

		if (actTemp < maxTemp && actTemp > minTemp) {
			overTempLock = false;
			mute = true;
			Lamp(false);
		}
	}
}

void ALARM() {
	beep(500, 200);
	beep(500, 400);

}

void ALARM2() {
	beep(500, 100);
	beep(500, 50);
	beep(500, 150);

}

void Lamp(bool mode) {
	if (!mode)
		PORTD |= (1 << 1);
	else
		PORTD &= (0 << 1);
}

void beep(uint16_t time, uint16_t delay) {
	for (int clk = 0; clk < time; clk++) {
		PORTD &= (0 << 0);
		DELAY_us(delay);
		PORTD |= (1 << 0);
		DELAY_us(delay);
	}
	PORTD |= (1 << 0);
}
