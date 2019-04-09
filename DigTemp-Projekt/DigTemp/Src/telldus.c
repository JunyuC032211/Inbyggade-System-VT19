/**
 ******************************************************************************
 @brief	Telldus file, complements main.c and
 @file	telldus.c
 @author Johan Hanssen
 @version 1.3
 @date	16-February-2018
 @brief	The code for interpreting the values sent from the wireless Telldus module.
 ******************************************************************************
 */
#include "telldus.h"
#include "gpio.h"
#include "stdbool.h"
#include "crc.h"
#include "display.h"
#include "string.h"
#include "setuartrtc.h"
#include "usart.h"
#include "rtc.h"
uint8_t precount, count32, crcCount = 0;
uint16_t Temperature, Humidity, SensorID, Channel = 0;
uint32_t telldus32, crc, checksum;

bool save32 = false;
bool waitForZero = false;

char displayString[10];
double temp;




/**
 *
 * @brief	telldus, with the value of ticks2 it processes the 1s and 0s of the input
 * 			and saves the result. When the uint32_t telldus32 is full it checks the
 * 			saved crc with the generated checksum. After that it sends the values of
 * 			Temprature and Humidity to the display.
 *
 * @param	uint16_t ticks2 , value of the period of the flank on PA15 port.
 *
 * @return void, but it sends temperature and humitidy to the sendDisplay() function.
*/
void telldus(uint16_t ticks2) {
	/*
	 * If any value has gone astray, reset to initial values
	 */
	if (precount > 20 || crcCount > 9 || count32 > 33) {
		crc = 0;
		precount = 0;
		count32 = 0;
		crcCount = 0;
		save32 = false;
		waitForZero = false;
	}

	if (crcCount < 8) {
		if (333 < ticks2 && ticks2 < 433) {
			if (save32) {
				int one = 1;

				if (count32 < 32) {
					telldus32 = telldus32 << 1;
					telldus32 += one;
					count32++;
				} else {
					crc = crc << 1;
					crc += one;
					crcCount++;
				}
			} else {
				precount++;
				if (precount > 5) {
					waitForZero = true;
				}
			}
		}
		if (1314 < ticks2 && ticks2 < 1414) {
			if (waitForZero) {
				save32 = true;
				precount = 0;
				waitForZero = false;
			}
			int zero = 0;
			if (count32 < 32) {
				telldus32 = telldus32 << 1;
				telldus32 += zero;
				count32++;
			} else {
				crc = crc << 1;
				crc += zero;
				crcCount++;
			}
		}
	} else {
		checksum = HAL_CRC_Calculate(&hcrc, &telldus32, 1);
		if (checksum == crc) {
			Temperature = (telldus32 >> 8) & 0x3FF;
			Humidity = telldus32 & 0x7F;
			SensorID = (telldus32 >> 27) & 0x1F;
			Channel = (telldus32 >> 24) & 0x7;
			temp = ((double) Temperature) / 10;
			sprintf(displayString, "Temp: %f", temp);
			sendDisplay(0, 0, 0xC0); //3rd row
			for (int i = 0; i < sizeof(displayString); i++) {
				sendDisplay(1, 0, displayString[i]);
			}
			memset(displayString, ' ', 10);
			sprintf(displayString, " Hum: %i %%", Humidity);
			sendDisplay(0, 0, 0xE0); //4th row
			for (int i = 0; i < sizeof(displayString); i++) {
				sendDisplay(1, 0, displayString[i]);
			}
			sendBluetooth(temp,Humidity);
			crc = 0;
			precount = 0;
			count32 = 0;
			crcCount = 0;
			save32 = false;
			waitForZero = false;
		} else {
			crc = 0;
			precount = 0;
			count32 = 0;
			crcCount = 0;
			save32 = false;
			waitForZero = false;
		}
	}
}

