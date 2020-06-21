
#include <avr/io.h>
/**************************************************************************/
/*!
    @brief  Class for communicating with thermocouple sensor
*/
/**************************************************************************/

  void MAX6675();

  float readCelsius(void);

  uint8_t spiread(void);

void CS_LOW();
void CS_HIGH();
void SCK_LOW();
void SCK_HIGH();
void PWR_OFF();
void PWR_ON();
