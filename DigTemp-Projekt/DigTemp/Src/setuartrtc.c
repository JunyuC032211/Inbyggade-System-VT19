/**
******************************************************************************
@brief	setUartRtc is initializing the clock to a value set by UART
@file	setuartrtc.c
@author Johan Hanssen
@version 1.0
@date	26-February-2018
@brief	The function setUartRtc is called before the while(1) loop in main
		to set up the clock to the users request set by UART communication.
******************************************************************************
*/
#include "setuartrtc.h"
#include "gpio.h"
#include "usart.h"
#include <string.h>
#include "stm32f3xx_hal.h"
#include "rtc.h"

RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

ITStatus UartReady = RESET;
  uint8_t Buffer[] = "Enter time as 112233 for 11h:22m:33s.\n \r";
  uint8_t Clock[6];
  uint8_t hour = 0;
  uint8_t min = 0;
  uint8_t sec = 0;
  char sendBlue[27];


  /*
   * @brief		setUartRtc takes the input 6digit value interrupted from the UARTbuffer
   * 			and sets the RTC to that value. ex 11h:22m:33s is entered as 112233.
   *
   * @param		void
   * @return	void
   */
void setUartRtc(){
	  if(HAL_UART_Transmit_IT(&huart3, Buffer, 42) != HAL_OK){Error_Handler();}
	  while(UartReady != SET){}
	  UartReady = RESET;

	  if(HAL_UART_Receive_IT(&huart3, Clock, 6) != HAL_OK){Error_Handler();}
	  while(UartReady != SET){	  }
	  UartReady=RESET;

	  if(HAL_UART_Transmit_IT(&huart3, Clock, 6) != HAL_OK){Error_Handler();  }
	  while(UartReady != SET){}
	  UartReady = RESET;

	 /* RTC Clock manipulation to be sent to the display */
	 hour = ((Clock[0] - 48) * 10) + (Clock[1] - 48);
	 min = ((Clock[2] - 48) * 10) + (Clock[3] - 48);
	 sec = ((Clock[4] - 48) * 10) + (Clock[5] - 48);

	 sTime.Hours = hour;
	 sTime.Minutes = min;
	 sTime.Seconds = sec;

	 HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	 HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void sendBluetooth(double temp, uint16_t Humidity){
	sprintf(sendBlue, "%02d:%02d:, Temp:%0.1f, Hum:%i\n", sTime.Hours,sTime.Minutes,temp,Humidity);
	  if(HAL_UART_Transmit(&huart2, (uint8_t *) sendBlue, sizeof(sendBlue),500) != HAL_OK){
		  Error_Handler();
	  }

	  //while(UartReady != SET){}
//	  UartReady = RESET;

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle){
	/* Set transmission flag: transfer complete */
	UartReady = SET;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle){
	/* Set transmission flag: transfer complete */
	UartReady = SET;
}
