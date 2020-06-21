#include "../HEADERS/termo.h"
#include "../../Libraries/Headers/delay.h"
#include <avr/io.h>
#define MISO (!(PINC & 0x80))

void MAX6675() {

  // define pin modes
//  pinMode(cs, OUTPUT); 0
//  pinMode(sclk, OUTPUT); 1
//  pinMode(miso, INPUT); 2
	DDRC = 0x07;
  CS_HIGH();
}

/**************************************************************************/
/*!
    @brief  Read the Celsius temperature
    @returns Temperature in C or NAN on failure!
*/
/**************************************************************************/
float readCelsius(void) {

  uint16_t v;

  CS_LOW();
  DELAY_us(10);
  v = spiread();
  v <<= 8;
  v |= spiread();
  CS_HIGH();
  DELAY_ms(10);
  SCK_LOW();
  CS_LOW();
  DELAY_ms(10);
  CS_HIGH();
  DELAY_ms(200);

  DELAY_us(10);
  if (v & 0x4) {
    return -100;

  }

  v >>= 3;

  return (v *0.25);
}

uint8_t spiread(void) {
  int i;
  uint8_t d = 0;

  for (i = 7; i >= 0; i--) {
    SCK_LOW();
    DELAY_us(10);
    if (!MISO) {
      // set the bit to 0 no matter what
      d |= (1 << i);
    }

    SCK_HIGH();
    DELAY_us(10);
  }

  return d;
}

void CS_LOW(){
	PORTC &= (0 << 0);
}
void CS_HIGH(){
	PORTC |= (1 << 0);
}
void SCK_LOW(){
	PORTC &= (0 << 1);
}
void SCK_HIGH(){
	PORTC |= (1 << 1);
}
