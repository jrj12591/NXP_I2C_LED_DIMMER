
#**Library for the 
#NXP PCA9530 - 2 Bit I2C LED Dimmer
#NXP PCA9550 - 2 Bit I2C LED Dimmer
#NXP PCA9531 - 8 Bit I2C LED Dimmer
#NXP PCA9551 - 8 Bit I2C LED Dimmer
#NXP PCA9532 - 16 Bit I2C LED Dimmer
#NXP PCA9553 - 16 Bit I2C LED Dimmer
#NXP PCA9534 - 4 Bit I2C LED Dimmer
#NXP PCA9554 - 4 Bit I2C LED Dimmer**



###Use the Following Address:

#####PCA9530 & PCA9550
```
A1 	Address		Variable Name
-0	0x60		I2C_ADDRESS_1
-1	0x61		I2C_ADDRESS_2
```
#####PCA9531 & PCA9551
```
A2, A1, A0		Address		Variable Name
-0	0	0		0x60		I2C_ADDRESS_1
-0	0	1		0x61		I2C_ADDRESS_2
-0	1	0		0x62		I2C_ADDRESS_3
-0	1	1		0x63		I2C_ADDRESS_4
-1	0	0		0x64		I2C_ADDRESS_5
-1	0	1		0x65		I2C_ADDRESS_6
-1	1	0		0x66		I2C_ADDRESS_7
-1	1	1		0x67		I2C_ADDRESS_8
```
#####PCA9532 & PCA9552
```
A2, A1, A0		Address		Variable Name
-0	0	0		0x60		I2C_ADDRESS_1
-0	0	1		0x61		I2C_ADDRESS_2
-0	1	0		0x62		I2C_ADDRESS_3
-0	1	1		0x63		I2C_ADDRESS_4
-1	0	0		0x64		I2C_ADDRESS_5
-1	0	1		0x65		I2C_ADDRESS_6
-1	1	0		0x66		I2C_ADDRESS_7
-1	1	1		0x67		I2C_ADDRESS_8
```

#####PCA9533/01 & PCA9553/01
```
Address		Variable Name
-0x62		I2C_ADDRESS_3
```

#####PCA9533/02 & PCA9553/02
```
Address		Variable Name
-0x63		I2C_ADDRESS_4
```
These chips has two banks of configuration of for the pulse width modulation.
Each of the 8 Pins can be set to one of 4 settings, Off, ON Full, Pulse Width Modulation Configuration 1, Pulse Width Modulation Configuration 2





Commands
```
PCA9530 or PCA9530(Address)
PCA9531 or PCA9531(Address)
PCA9532 or PCA9532(Address)
PCA9533 or PCA9533(Address)
PCA9550 or PCA9550(Address)
PCA9551 or PCA9551(Address)
PCA9552 or PCA9552(Address)
PCA9553 or PCA9553(Address)

 .begin()
 
 .remotedigitalWrite(int pin, uint8_t  output)
			pin =	(PCA9530 or PCA9550) 0-1;
					(PCA9531 or PCA9551) 0-7;
					(PCA9532 or PCA9552) 0-15;
					(PCA9533 or PCA9553) 0-3;
					
			output =	LOW		- Off 
						HIGH	- ON 
						PWM0 	- Pulse Width Bank 1
						PWM1	- Pulse Width Bank 2
						
		Configure the Pulse Width Bank Configuration
	Configure the Frequency of Blinking
 .blinkperiod(float freq, int PSC)
			PSC =	0 for Pulse Width Configuration 1
					1 for Pulse Width Configuration 2
					
	Configure the Brightness of the LED
 .brightness(float duty_cycle, uint8_t PWM)
			duty_cycle = 0-100%
			PWM = 	PWM0 for Pulse Width Configuration 1
					PWM1 for Pulse Width Configuration 2
					
```					