/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "usb.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Pingpong_function.h"
#include "clockinit.h" 
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/


/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
@brief Show_points, shows points after missed ball
@param1 uint8_t L_points points for left player
@param2 uint8_t R_points points for right player
@return void, no return value
*/
//void Show_points(uint8_t L_points, uint8_t R_points)
//{
//  uint8_t B_point = 0;
//  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//  if ( HAL_GPIO_ReadPin(L_BUTTON_GPIO_Port, L_BUTTON_Pin) == 0 &&  HAL_GPIO_ReadPin(LED1_GPIO_Port, LED1_Pin))
//    printf("send ball back");
//  else
//    if( B_point<4)
//      B_point++;
//  
//  uint8_t A_point = 0;
//  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
//  if ( HAL_GPIO_ReadPin(R_BUTTON_GPIO_Port, R_BUTTON_Pin) == 0 &&  HAL_GPIO_ReadPin(LED8_GPIO_Port, LED8_Pin))
//    printf("send ball back");
//  else
//    if( A_point<4)
//      A_point++;
//}
void Show_points(uint8_t L_points, uint8_t R_points)
{
  //L_points is the points that left player has 0b0000 where the least significant bit is LED1. 0x8ffa = 0b1000111111111010
  if(L_points == 1){ //0b0001
    // then light LED1
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
  }  
    if(L_points == 2){ //0b0010
    // then light LED2
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
  } 
  if(L_points == 3){ //0b0011
    // then light LED1,2,3
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
  } 
  if(L_points == 4){ //0b0100
    // then light LED1,2,3,4
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
  } 
  // R_points is the points for right players has 0b0000 where the most significant bit is LED5
  if(R_points == 1){ //0b0001
    // then light LED8
      HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
  }  
    if(R_points == 2){ //0b0010
    // then light LED8,7
      HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
  } 
  if(R_points == 3){ //0b0011
    // then light LED8,7,6
      HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
  } 
  if(R_points == 4){ //0b0100
    // then light LED8,7,6,5
      HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
  } 
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  
/*  int Lednr;
 for (Lednr=1; Lednr<= 8; Lednr++) {
   HAL_Delay(500); //Delay 500 ms
// printf("Lednr ar %d \n",Lednr);
 } */
  /* USER CODE END 1 */
  
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
 
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  /* USER CODE BEGIN 2 */
  
/* printf("Test av funktion Led_on");
 int Led;
 for (Led=1; Led<= 9; Led++) {
 Led_on(Led);
 HAL_Delay(500); // Delay 500 ms
 }*/
  /* USER CODE END 2 */

  /* Infinite loop */

 
//int j=0;
// while (1)
// {
//  
//
// while ( HAL_GPIO_ReadPin(L_BUTTON_GPIO_Port, L_BUTTON_Pin) != 0 );
//// Wait until L is pushed
//
// Led_on(j++); // Turn on led j
//
// while ( HAL_GPIO_ReadPin(L_BUTTON_GPIO_Port, L_BUTTON_Pin) == 0 );
//// Wait until L is released
//
// if (j==5) j=0; // Start from beginning again
//
//
//
// }
int j=0;
 while (1)
 {
 if ( L_hit() == true ) // Wait for left button hit
 {
 j++; // next led to the right
 Led_on(j); // Light on
 HAL_Delay(100); // 100 ms
 while ( L_hit() == true ); // Wait for button release
 HAL_Delay(100); // 100 ms
 if (j>8) j=9; // Start again from right
 }

 if ( R_hit() == true ) // Wait for right button hit
 {
 j--; // next led to the left
 Led_on(j); // Light on
 HAL_Delay(100); // 100 ms
 while ( R_hit() == true ); // Wait for button lelease
 HAL_Delay(100); // 100 ms
 if (j<1) j=0; // Start again from left
 }

 } // end while 
 
 
  /* USER CODE END 3 */
}




/* USER CODE BEGIN 4 */

 /* void Led_on(uint8_t Lednr)
 {
 printf("Lednr ?r %d \n",Lednr);
 return;
 } */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
