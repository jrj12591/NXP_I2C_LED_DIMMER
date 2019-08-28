/**************************************************************************/
/*!
   @file     NXP_I2C_LED_DIMMERS.h
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

#ifndef NXP_I2C_LED_DIMMERS_h
#define NXP_I2C_LED_DIMMERS_h



#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>
/*=========================================================================
    I2C ADDRESS/BITS
-----------------------------------------------------------------------*/
	const uint8_t I2C_ADDRESS_1 = 0x60;
	const uint8_t I2C_ADDRESS_2 = 0x61;
	const uint8_t I2C_ADDRESS_3 = 0x62;
	const uint8_t I2C_ADDRESS_4 = 0x63;
	const uint8_t I2C_ADDRESS_5 = 0x64;
	const uint8_t I2C_ADDRESS_6 = 0x65;
	const uint8_t I2C_ADDRESS_7 = 0x66;
	const uint8_t I2C_ADDRESS_8 = 0x67;
/*=========================================================================*/




/*=========================================================================
    CONFIG REGISTER
    -----------------------------------------------------------------------*/
	const uint8_t REG_INPUT_0 	= 0x00;	// 
    const uint8_t REG_PSCO 		= 0x01;	// 
	const uint8_t REG_PWM0 		= 0x02;	// 
	const uint8_t REG_PSC1 		= 0x03;	// 
	const uint8_t REG_PWM1 		= 0x04;	// 
	const uint8_t REG_LS0 		= 0x05;	//
	const uint8_t REG_LS1 		= 0x06;	// 
	
	const uint8_t PCA_REG_INPUT_0 	= 0x00;	//
	const uint8_t PCA_REG_INPUT_1	= 0x01;
    const uint8_t PCA_REG_PSCO 		= 0x02;	// 
	const uint8_t PCA_REG_PWM0 		= 0x03;	// 
	const uint8_t PCA_REG_PSC1 		= 0x04;	// 
	const uint8_t PCA_REG_PWM1 		= 0x05;	// 
	const uint8_t PCA_REG_LS0 		= 0x06;	//
	const uint8_t PCA_REG_LS1 		= 0x07;
	const uint8_t PCA_REG_LS2		= 0x08;
	const uint8_t PCA_REG_LS3		= 0x09;
/*=========================================================================*/
/*=========================================================================
   OPTIONS CONSTANTS
    -----------------------------------------------------------------------*/
	const uint8_t PMW0 = 0x02;
	const uint8_t PMW1 = 0x03;


	const uint8_t PCA9530_TYPE = 0x00;
	const uint8_t PCA9550_TYPE = 0x01;
	const uint8_t PCA9531_TYPE = 0x02;
	const uint8_t PCA9551_TYPE = 0x03;
	const uint8_t PCA9532_TYPE = 0x04;
	const uint8_t PCA9552_TYPE = 0x05;
	const uint8_t PCA9533_TYPE = 0x06;
	const uint8_t PCA9553_TYPE = 0x07;
/*=========================================================================*/



class PCA9531 //8Bit
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
   uint8_t chip_version;
	
 public:
  PCA9531(uint8_t i2cAddress = I2C_ADDRESS_1);
  void begin(void);
  void remotedigitalWrite(int pin, uint8_t  output);
  void blinkperiod(float freq, int PSC);
  void brightness(float duty_cycle, uint8_t PWM);
 private:
 
};

class PCA9551: public PCA9531 //8 Bit
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
   uint8_t chip_version;
 public:
 PCA9551(uint8_t i2cAddress = I2C_ADDRESS_1);
 private:
 
};

class PCA9530: public PCA9531 //2 Bit
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
    uint8_t chip_version;
 public:
 PCA9530(uint8_t i2cAddress = I2C_ADDRESS_1);
 private:
 
};

class PCA9550: public PCA9531   //2 Bit
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
   uint8_t chip_version;
 public:
 PCA9550(uint8_t i2cAddress = I2C_ADDRESS_1);
 private:
 
};

class PCA9553: public PCA9531 //4 Bit
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
   uint8_t chip_version;
 public:
 PCA9553(uint8_t i2cAddress = I2C_ADDRESS_1);
 private:
 
};

class PCA9533: public PCA9531 //4 Bit
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
   uint8_t chip_version;
 public:
 PCA9533(uint8_t i2cAddress = I2C_ADDRESS_1);
 private:
};

class PCA9532: public PCA9531 //16 Bit
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
   uint8_t chip_version;
 public:
 PCA9532(uint8_t i2cAddress = I2C_ADDRESS_1);
 private:
};

class PCA9552: public PCA9531 //16 Bit
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
   uint8_t chip_version;
 public:
 PCA9552(uint8_t i2cAddress = I2C_ADDRESS_1);
 private:
};

#endif












