/**************************************************************************/
/*!
   @file     NXP_I2C_LED_DIMMERS.cpp
   @author   JASON JOHNSTON

    This library contains commands for the Following Chips:
	NXP PCA9530 - 2 Bit I2C LED DIMMER;
	NXP PCA9550 - 2 Bit I2C LED DIMMER; 
	NXP PCA9531 - 8 Bit I2C LED DIMMER;
	NXP PCA9551 - 8 Bit I2C LED DIMMER; 
	NXP PCA9532 - 16 Bit I2C LED DIMMER;
	NXP PCA9552 - 16 Bit I2C LED DIMMER;
	NXP PCA9533 - 4 Bit I2C LED DIMMER;,
	NXP PCA9553 - 4 Bit I2C LED DIMMER;.
	This is library is designed to allow for individual control of each pin.

    
	Please Note This driver is based on the driver for the ADS1015 created by Adafruit
	
    @section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#include "NXP_I2C_LED_DIMMERS.h"

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static uint8_t i2cread(void) {
  #if ARDUINO >= 100
  return Wire.read();
  #else
  return Wire.receive();
  #endif
}

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static void i2cwrite(uint8_t x) {
  #if ARDUINO >= 100
  Wire.write((uint8_t)x);
  #else
  Wire.send(x);
  #endif
}

/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
static void writeRegister(uint8_t i2cAddress, uint8_t reg, uint8_t value) {
  Wire.beginTransmission(i2cAddress);
  i2cwrite((uint8_t)reg);
  i2cwrite((uint8_t)value);
  Wire.endTransmission();
}
	
/**************************************************************************/
/*!
    @brief  Reads the 8-bits From the Data Registor*/
/**************************************************************************/

static uint8_t readRegister2(uint8_t i2cAddress, uint8_t reg) {
  Wire.beginTransmission(i2cAddress);
  i2cwrite((uint8_t)reg);
  Wire.endTransmission();
  Wire.requestFrom(i2cAddress, (uint8_t)1);
  return i2cread();
}

/**************************************************************************/

/*!
    @brief  Instantiates a new PCA9530 class w/appropriate properties
*/
/**************************************************************************/
PCA9530::PCA9530(uint8_t i2cAddress)
{ 
   m_i2cAddress = i2cAddress;
   chip_version = PCA9530_TYPE;
}
/**************************************************************************/

/*!
    @brief  Instantiates a new PCA9531 class w/appropriate properties
*/
/**************************************************************************/

PCA9531::PCA9531(uint8_t i2cAddress)
{ 
   m_i2cAddress = i2cAddress;
   chip_version = PCA9531_TYPE;
}
/**************************************************************************/

/*!
    @brief  Instantiates a new PCA9532 class w/appropriate properties
*/
/**************************************************************************/
PCA9532::PCA9532(uint8_t i2cAddress)
{ 
   m_i2cAddress = i2cAddress;
   chip_version = PCA9532_TYPE;
}
/**************************************************************************/

/*!
    @brief  Instantiates a new PCA9533 class w/appropriate properties
*/
/**************************************************************************/
PCA9533::PCA9533(uint8_t i2cAddress)
{ 
   m_i2cAddress = i2cAddress;
   chip_version = PCA9533_TYPE;
}
/**************************************************************************/

/*!
    @brief  Instantiates a new PCA9550 class w/appropriate properties
*/
/**************************************************************************/
PCA9550::PCA9550(uint8_t i2cAddress)
{ 
   m_i2cAddress = i2cAddress;
   chip_version = PCA9550_TYPE;
}
/**************************************************************************/

/*!
    @brief  Instantiates a new PCA9551 class w/appropriate properties
*/
/**************************************************************************/
PCA9551::PCA9551(uint8_t i2cAddress)
{ 
   m_i2cAddress = i2cAddress;
   chip_version = PCA9551_TYPE;
}
/**************************************************************************/

/*!
    @brief  Instantiates a new PCA9552 class w/appropriate properties
*/
/**************************************************************************/
PCA9552::PCA9552(uint8_t i2cAddress)
{ 
   m_i2cAddress = i2cAddress;
   chip_version = PCA9552_TYPE;
}
/**************************************************************************/

/*!
    @brief  Instantiates a new PCA9553 class w/appropriate properties
*/
/**************************************************************************/
PCA9553::PCA9553(uint8_t i2cAddress)
{ 
   m_i2cAddress = i2cAddress;
   chip_version = PCA9553_TYPE;
}





static void PCA9531_PCA9551_write(int pin, uint8_t output, uint8_t i2cAddress){
	uint8_t current_output_value;
	uint8_t output_status;
	uint8_t value;
	if (pin >7 | pin <0){
		 return;
	 }
	 
	 switch (pin){
		case 0: //If Pin 0 is selected
			current_output_value = readRegister2(i2cAddress, REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xFC;  //Clear Pin 0 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x01;				
			}
			else if (output == PMW0){
				value = output_status | 0x02;
			}	
			else if (output == PMW1){
				value = output_status | 0x03;	
			}	
			writeRegister(i2cAddress, REG_LS0, value);
			return;
		case 1: //If Pin 1 is Selected
			current_output_value = readRegister2(i2cAddress, REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xF3;  //Clear Pin 1 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x04;				
			}
			else if (output == PMW0){
				value = output_status | 0x08;
			}	
			else if (output == PMW1){
				value = output_status | 0x0C;	
			}
			writeRegister(i2cAddress, REG_LS0, value);
			return;
		case 2: //If Pin 2 is Selected
			current_output_value = readRegister2(i2cAddress, REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xCF;  //Clear Pin 2 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x10;				
			}
			else if (output == PMW0){
				value = output_status | 0x20;
			}	
			else if (output == PMW1){
				value = output_status | 0x30;	
			}
			writeRegister(i2cAddress,REG_LS0, value);
			return;
			
		case 3://If Pin 3 is Selected
			current_output_value = readRegister2(i2cAddress, REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0x3F;  //Clear Pin 3 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x40;				
			}
			else if (output == PMW0){
				value = output_status | 0x80;
			}	
			else if (output == PMW1){
				value = output_status | 0xC0;	
			}
			writeRegister(i2cAddress,REG_LS0, value);
			return;
		case 4:
		//If Pin 4 is selected
			current_output_value = readRegister2(i2cAddress, REG_LS1); //Read current staus of Pins 4-7
			output_status = current_output_value & 0xFC;  //Clear Pin 4 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x01;				
			}
			else if (output == PMW0){
				value = output_status | 0x02;
			}	
			else if (output == PMW1){
				value = output_status | 0x03;	
			}	
			writeRegister(i2cAddress, REG_LS1, value);
			return;
		case 5:
			//If Pin 5 is Selected
			current_output_value = readRegister2(i2cAddress,REG_LS1); //Read current staus of Pins 4-7
			output_status = current_output_value & 0xF3;  //Clear Pin 1 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x04;				
			}
			else if (output == PMW0){
				value = output_status | 0x08;
			}	
			else if (output == PMW1){
				value = output_status | 0x0C;	
			}
			writeRegister(i2cAddress, REG_LS1, value);
			return;
		case 6:
			current_output_value = readRegister2(i2cAddress,REG_LS1); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xCF;  //Clear Pin 2 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x10;				
			}
			else if (output == PMW0){
				value = output_status | 0x20;
			}	
			else if (output == PMW1){
				value = output_status | 0x30;	
			}
			writeRegister(i2cAddress, REG_LS1, value);
			return;
			
		case 7:
		//If Pin 7 is Selected
			current_output_value = readRegister2(i2cAddress, REG_LS1); //Read current staus of Pins 0-3
			output_status = current_output_value & 0x3F;  //Clear Pin 3 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x40;				
			}
			else if (output == PMW0){
				value = output_status | 0x80;
			}	
			else if (output == PMW1){
				value = output_status | 0xC0;	
			}
			writeRegister(i2cAddress, REG_LS1, value);
			return;
	}
}

static void PCA9530_PCA9550_write(int pin, uint8_t output, uint8_t i2cAddress){
	uint8_t current_output_value;
	uint8_t output_status;
	uint8_t value;
	if (pin >1 | pin <0){
		 return;
	 }
	
	switch (pin){
		case 0: //If Pin 0 is selected
			current_output_value = readRegister2(i2cAddress,REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xFC;  //Clear Pin 0 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x01;				
			}
			else if (output == PMW0){
				value = output_status | 0x02;
			}	
			else if (output == PMW1){
				value = output_status | 0x03;	
			}	
			writeRegister(i2cAddress, REG_LS0, value);
			return;
		case 1: //If Pin 1 is Selected
			current_output_value = readRegister2(i2cAddress,REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xF3;  //Clear Pin 1 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x04;				
			}
			else if (output == PMW0){
				value = output_status | 0x08;
			}	
			else if (output == PMW1){
				value = output_status | 0x0C;	
			}
			writeRegister(i2cAddress, REG_LS0, value);
			return;
	}
}

static void PCA9533_PCA9553_write(int pin, uint8_t output, uint8_t i2cAddress)
{
	uint8_t current_output_value;
	uint8_t output_status;
	uint8_t value;
	if (pin >4 | pin <0){
		 return;
	 }
	 
	 switch (pin){
		case 0: //If Pin 0 is selected
			current_output_value = readRegister2(i2cAddress,REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xFC;  //Clear Pin 0 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x01;				
			}
			else if (output == PMW0){
				value = output_status | 0x02;
			}	
			else if (output == PMW1){
				value = output_status | 0x03;	
			}	
			writeRegister(i2cAddress, REG_LS0, value);
			return;
		case 1: //If Pin 1 is Selected
			current_output_value = readRegister2(i2cAddress,REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xF3;  //Clear Pin 1 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x04;				
			}
			else if (output == PMW0){
				value = output_status | 0x08;
			}	
			else if (output == PMW1){
				value = output_status | 0x0C;	
			}
			writeRegister(i2cAddress, REG_LS0, value);
			return;
		case 2: //If Pin 2 is Selected
			current_output_value = readRegister2(i2cAddress,REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xCF;  //Clear Pin 2 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x10;				
			}
			else if (output == PMW0){
				value = output_status | 0x20;
			}	
			else if (output == PMW1){
				value = output_status | 0x30;	
			}
			writeRegister(i2cAddress,REG_LS0, value);
			return;
			
		case 3://If Pin 3 is Selected
			current_output_value = readRegister2(i2cAddress,REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0x3F;  //Clear Pin 3 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x40;				
			}
			else if (output == PMW0){
				value = output_status | 0x80;
			}	
			else if (output == PMW1){
				value = output_status | 0xC0;	
			}
			writeRegister(i2cAddress,REG_LS0, value);
			return;
	 }
}

static void PCA9532_PCA9552_write(int pin, uint8_t output, uint8_t i2cAddress){
	uint8_t current_output_value;
	uint8_t output_status;
	uint8_t value;
	
	if (pin >15 | pin <0){
		 return;
	 }
	 switch (pin){
		case 0: //If Pin 0 is selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xFC;  //Clear Pin 0 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x01;				
			}
			else if (output == PMW0){
				value = output_status | 0x02;
			}	
			else if (output == PMW1){
				value = output_status | 0x03;	
			}	
			writeRegister(i2cAddress, PCA_REG_LS0, value);
			return;
		case 1: //If Pin 1 is Selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xF3;  //Clear Pin 1 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x04;				
			}
			else if (output == PMW0){
				value = output_status | 0x08;
			}	
			else if (output == PMW1){
				value = output_status | 0x0C;	
			}
			writeRegister(i2cAddress, PCA_REG_LS0, value);
			return;
		case 2: //If Pin 2 is Selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xCF;  //Clear Pin 2 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x10;				
			}
			else if (output == PMW0){
				value = output_status | 0x20;
			}	
			else if (output == PMW1){
				value = output_status | 0x30;	
			}
			writeRegister(i2cAddress, PCA_REG_LS0, value);
			return;
			
		case 3://If Pin 3 is Selected
			current_output_value = readRegister2(i2cAddress, PCA_REG_LS0); //Read current staus of Pins 0-3
			output_status = current_output_value & 0x3F;  //Clear Pin 3 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x40;				
			}
			else if (output == PMW0){
				value = output_status | 0x80;
			}	
			else if (output == PMW1){
				value = output_status | 0xC0;	
			}
			writeRegister(i2cAddress, PCA_REG_LS0, value);
			return;
		case 4:
		//If Pin 4 is selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS1); //Read current staus of Pins 4-7
			output_status = current_output_value & 0xFC;  //Clear Pin 4 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x01;				
			}
			else if (output == PMW0){
				value = output_status | 0x02;
			}	
			else if (output == PMW1){
				value = output_status | 0x03;	
			}	
			writeRegister(i2cAddress, PCA_REG_LS1, value);
			return;
		case 5:
			//If Pin 5 is Selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS1); //Read current staus of Pins 4-7
			output_status = current_output_value & 0xF3;  //Clear Pin 1 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x04;				
			}
			else if (output == PMW0){
				value = output_status | 0x08;
			}	
			else if (output == PMW1){
				value = output_status | 0x0C;	
			}
			writeRegister(i2cAddress, PCA_REG_LS1, value);
			return;
		case 6:
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS1); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xCF;  //Clear Pin 2 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x10;				
			}
			else if (output == PMW0){
				value = output_status | 0x20;
			}	
			else if (output == PMW1){
				value = output_status | 0x30;	
			}
			writeRegister(i2cAddress, PCA_REG_LS1, value);
			return;
			
		case 7:
		//If Pin 7 is Selected
			current_output_value = readRegister2(i2cAddress, PCA_REG_LS1); //Read current staus of Pins 0-3
			output_status = current_output_value & 0x3F;  //Clear Pin 3 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x40;				
			}
			else if (output == PMW0){
				value = output_status | 0x80;
			}	
			else if (output == PMW1){
				value = output_status | 0xC0;	
			}
			writeRegister(i2cAddress, PCA_REG_LS1, value);
			return;
		case 8: //If Pin 0 is selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS2); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xFC;  //Clear Pin 0 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x01;				
			}
			else if (output == PMW0){
				value = output_status | 0x02;
			}	
			else if (output == PMW1){
				value = output_status | 0x03;	
			}	
			writeRegister(i2cAddress, PCA_REG_LS0, value);
			return;
		case 9: //If Pin 1 is Selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS2); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xF3;  //Clear Pin 1 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x04;				
			}
			else if (output == PMW0){
				value = output_status | 0x08;
			}	
			else if (output == PMW1){
				value = output_status | 0x0C;	
			}
			writeRegister(i2cAddress, PCA_REG_LS2, value);
			return;
		case 10: //If Pin 2 is Selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS2); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xCF;  //Clear Pin 2 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x10;				
			}
			else if (output == PMW0){
				value = output_status | 0x20;
			}	
			else if (output == PMW1){
				value = output_status | 0x30;	
			}
			writeRegister(i2cAddress, PCA_REG_LS2, value);
			return;
			
		case 11://If Pin 3 is Selected
			current_output_value = readRegister2(i2cAddress, PCA_REG_LS2); //Read current staus of Pins 0-3
			output_status = current_output_value & 0x3F;  //Clear Pin 3 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x40;				
			}
			else if (output == PMW0){
				value = output_status | 0x80;
			}	
			else if (output == PMW1){
				value = output_status | 0xC0;	
			}
			writeRegister(i2cAddress, PCA_REG_LS2, value);
			return;
		case 12:
		//If Pin 4 is selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS3); //Read current staus of Pins 4-7
			output_status = current_output_value & 0xFC;  //Clear Pin 4 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x01;				
			}
			else if (output == PMW0){
				value = output_status | 0x02;
			}	
			else if (output == PMW1){
				value = output_status | 0x03;	
			}	
			writeRegister(i2cAddress, PCA_REG_LS2, value);
			return;
		case 13:
			//If Pin 5 is Selected
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS3); //Read current staus of Pins 4-7
			output_status = current_output_value & 0xF3;  //Clear Pin 1 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x04;				
			}
			else if (output == PMW0){
				value = output_status | 0x08;
			}	
			else if (output == PMW1){
				value = output_status | 0x0C;	
			}
			writeRegister(i2cAddress, PCA_REG_LS2, value);
			return;
		case 14:
			current_output_value = readRegister2(i2cAddress,PCA_REG_LS3); //Read current staus of Pins 0-3
			output_status = current_output_value & 0xCF;  //Clear Pin 2 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x10;				
			}
			else if (output == PMW0){
				value = output_status | 0x20;
			}	
			else if (output == PMW1){
				value = output_status | 0x30;	
			}
			writeRegister(i2cAddress, PCA_REG_LS1, value);
			return;
			
		case 15:
		//If Pin 7 is Selected
			current_output_value = readRegister2(i2cAddress, PCA_REG_LS3); //Read current staus of Pins 0-3
			output_status = current_output_value & 0x3F;  //Clear Pin 3 of current status
			if (output == LOW){
				value = output_status;
			}
			else if (output == HIGH){
				value = output_status | 0x40;				
			}
			else if (output == PMW0){
				value = output_status | 0x80;
			}	
			else if (output == PMW1){
				value = output_status | 0xC0;	
			}
			writeRegister(i2cAddress, PCA_REG_LS3, value);
			return;
	}
}

/**************************************************************************/
/*!
    @brief  Sets up the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void PCA9531::begin() {
  Wire.begin();
  if (chip_version == PCA9530_TYPE || chip_version == PCA9550_TYPE)
  {
	writeRegister(m_i2cAddress, REG_LS0, 0x00);
  }
  else if (chip_version == PCA9531_TYPE || chip_version == PCA9551_TYPE)
  {
	 writeRegister(m_i2cAddress, REG_LS0, 0x00);
	 writeRegister(m_i2cAddress, REG_LS1, 0x00);
  }
  else if (chip_version == PCA9532_TYPE || chip_version == PCA9552_TYPE)
  {
	 writeRegister(m_i2cAddress, PCA_REG_LS0, 0x00);
	 writeRegister(m_i2cAddress, PCA_REG_LS1, 0x00);
	 writeRegister(m_i2cAddress, PCA_REG_LS2, 0x00);
	 writeRegister(m_i2cAddress, PCA_REG_LS3, 0x00);
  }
  else if (chip_version == PCA9533_TYPE || chip_version == PCA9553_TYPE)
  {
	  writeRegister(m_i2cAddress, REG_LS0, 0x00);
  }  
}
/**************************************************************************/
/*!
    @brief  Configures the PWM Signal
			Default is full on
*/
/**************************************************************************/
void PCA9531::blinkperiod(float freq, int PSC)
	{
	uint8_t value;
	uint8_t value2;
	uint8_t Bank_select;
	switch(chip_version){
		case PCA9530_TYPE:
			if (PSC == 0){
				Bank_select = REG_PSCO;			
			}
			else if (PSC == 1)
			{
				Bank_select = REG_PSC1;	
			}
			value = round(((float)152*freq)-1);
			value2 = readRegister2(m_i2cAddress, Bank_select);
			if (value != value2)
			{
				writeRegister(m_i2cAddress, Bank_select, value);
			}
			break;
		case PCA9550_TYPE:
			if (PSC == 0){
				Bank_select = REG_PSCO;			
			}
			else if (PSC == 1)
			{
				Bank_select = REG_PSC1;	
			}
			value = round(((float)44*freq)-1);
			value2 = readRegister2(m_i2cAddress, Bank_select);
			if (value != value2)
			{
				writeRegister(m_i2cAddress, Bank_select, value);
			}
			break;
		case PCA9531_TYPE:
			if (PSC == 0)
			{
				Bank_select = REG_PSCO;			
			}
			else if (PSC == 1)
			{
				Bank_select = REG_PSC1;	
			}
			value = round(((float)152*freq)-1);
			value2 = readRegister2(m_i2cAddress, Bank_select);
			if (value != value2)
			{
				writeRegister(m_i2cAddress, Bank_select, value);
			}
			break;
		case PCA9551_TYPE:
			if (PSC == 0)
			{
				Bank_select = REG_PSCO;			
			}
			else if (PSC == 1)
			{
				Bank_select = REG_PSC1;	
			}
			value = round(((float)38*freq)-1);
			value2 = readRegister2(m_i2cAddress, Bank_select);
			if (value != value2)
			{
				writeRegister(m_i2cAddress, Bank_select, value);
			}
			break;			
		case PCA9532_TYPE:
			if (PSC == 0)
			{
				Bank_select = PCA_REG_PSCO;			
			}
			else if (PSC == 1)
			{
				Bank_select = PCA_REG_PSC1;	
			}
			value = round(((float)152*freq)-1);
			value2 = readRegister2(m_i2cAddress, Bank_select);
			if (value != value2)
			{
				writeRegister(m_i2cAddress, Bank_select, value);
			}
			break;
		case PCA9552_TYPE:
			if (PSC == 0)
			{
				Bank_select = PCA_REG_PSCO;			
			}
			else if (PSC == 1)
			{
				Bank_select = PCA_REG_PSC1;	
			}
			value = round(((float)44*freq)-1);
			value2 = readRegister2(m_i2cAddress, Bank_select);
			if (value != value2)
			{
				writeRegister(m_i2cAddress, Bank_select, value);
			}	
			break;
		case PCA9533_TYPE:
			if (PSC == 0)
			{
				Bank_select = REG_PSCO;			
			}
			else if (PSC == 1)
			{
				Bank_select = REG_PSC1;	
			}
			value = round(((float)152*freq)-1);
			value2 = readRegister2(m_i2cAddress, Bank_select);
			if (value != value2)
			{
				writeRegister(m_i2cAddress, Bank_select, value);
			}
			break;
		case PCA9553_TYPE:
			if (PSC == 0)
			{
				Bank_select = PCA_REG_PSCO;			
			}
			else if (PSC ==1)
			{
				Bank_select = REG_PSC1;	
			}
			value = round(((float)44*freq)-1);
			value2 = readRegister2(m_i2cAddress, Bank_select);
			if (value != value2)
			{
				writeRegister(m_i2cAddress, Bank_select, value);
			}
			break;
	}
}
/**************************************************************************/
/*!
    @brief  Configures the Brightness Setting for the LEDS
			Default is full on
*/
/**************************************************************************/

 void PCA9531::brightness(float duty_cycle, uint8_t PMW){
	 uint8_t value;
	 uint8_t value2;
	 if (duty_cycle > 100){
		 duty_cycle = 100;
	 }
	 else if (duty_cycle < 0){
		 duty_cycle = 0;
	 }
	 
	 duty_cycle = duty_cycle/100;
	 
	 value = round(duty_cycle*256);
	 if (chip_version == PCA9532_TYPE || chip_version == PCA9552_TYPE)
	{
		if (PMW == PMW0)
			{
			PMW = PCA_REG_PWM0;
			}
		else if (PMW == PMW1)
			{
			PMW = PCA_REG_PWM1;
			}
		value2 = readRegister2(m_i2cAddress, PMW);
		if (value != value2)
		{
			writeRegister(m_i2cAddress, PMW, value);
		}
	}
	else 
	{
		value2 = readRegister2(m_i2cAddress, PMW);
		if (value != value2)
		{
			writeRegister(m_i2cAddress, PMW, value);
		}
	}
 }

 /**************************************************************************/
/*!
    @brief  Output
*/
/**************************************************************************/
 void PCA9531::remotedigitalWrite(int pin, uint8_t output){
	switch(chip_version){
		case PCA9530_TYPE:
			PCA9530_PCA9550_write(pin, output, m_i2cAddress);
			break;
		case PCA9550_TYPE:
			PCA9530_PCA9550_write(pin, output, m_i2cAddress);
			break;
		case PCA9531_TYPE:
			PCA9531_PCA9551_write(pin, output, m_i2cAddress);
			break;
		case PCA9551_TYPE:
			PCA9531_PCA9551_write(pin, output, m_i2cAddress);
			break;
		case PCA9532_TYPE:
			PCA9532_PCA9552_write(pin, output, m_i2cAddress);
			break;
		case PCA9552_TYPE:
			PCA9532_PCA9552_write(pin, output, m_i2cAddress);
			break;
		case PCA9533_TYPE:
			PCA9533_PCA9553_write(pin, output, m_i2cAddress);
			break;
		case PCA9553_TYPE:
			PCA9533_PCA9553_write(pin, output, m_i2cAddress);
			break;
	}
}



