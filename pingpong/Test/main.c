/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  @brief Pingpong test program
  @file main.c
  @author Junyu Chen
  @version 1.1
  @date 24-Januari-2019
  @brief Testing state machine for program Pingpong
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

/* Define states for state machine*/
  typedef enum
  { Start,
    MoveRight,
    MoveLeft,
    ShowPoints,
    GameOver
   } states;
  states State, NextState;

 
  
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
   bool ButtonPressed; // To remember that button is pressed

   uint32_t Varv, Speed; // Ball speed
   uint8_t Led; // LED nr

   State= Start; // Initiate State to Start
   NextState= Start;

   Speed= 500000; // Number of loops
   
   uint8_t LeftPoints = 0;
   uint8_t RightPoints = 0;
   
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
 
  /* USER CODE END 2 */

 /* Infinite loop */
 while (1)
 {
     State = NextState;

     switch (State) // State machine
     {
       case Start:
       Led_on(0); // Turn off all LEDs

       if ( L_hit() == true ) // L serve
       {
       Led = 1;
       NextState= MoveRight;
       
       while ( L_hit() == true ); // wait until button is released
       }
       
       else if ( R_hit() == true ) // R serve
       {
         
       Led = 8;
       NextState= MoveLeft;
       while ( R_hit() == true ); // wait until button is released
       }
       else
       NextState = Start; // Stay in Start state
     break;
       
     case MoveRight:
     {
       Led_on(Led);
       Varv = Speed;

       while( Varv != 0 )
       {
       if ( R_hit() ) ButtonPressed = true; // R hit
       Varv--;
       }

       if ( ButtonPressed ) // R pressed
       {
       if ( Led == 8 ) // and LED8 activa
       {
       NextState=MoveLeft; // return ball
       Led=7;
       }
       else 
       
       {LeftPoints = LeftPoints  + 1; 
          NextState = ShowPoints;} // hit to early
       }
       else
       {
       if ( Led == 9 ) // no hit or to late
       {LeftPoints = LeftPoints  + 1; 
          NextState = ShowPoints;}
          else NextState = MoveRight; // ball continues to move right
       }
       if ( !ButtonPressed ) Led++; // prepare to turn next LED on
       ButtonPressed=false;
     }
     break;

     case MoveLeft:
     {
       Led_on(Led);
       Varv = Speed;

       while(Varv != 0)
       {
       if ( L_hit() ) ButtonPressed = true; // L hit
       Varv--;
       }

       if ( ButtonPressed ) // L pressed
       {
       if ( Led == 1 ) // and LED1 active
       {
       NextState=MoveRight; // return ball
       Led=2;
       }
       else
      {RightPoints = RightPoints  + 1; 
          NextState = ShowPoints;} // hit to early
       }
       else
       {
       if ( Led == 0 ) // no hit or to late
       {RightPoints = RightPoints  + 1; 
          NextState = ShowPoints;}
          else NextState = MoveLeft; // ball continues to move left
       }
       if ( !ButtonPressed ) Led--; // prepare to turn next LED on
       ButtonPressed=false;

     }
     break;
     case ShowPoints:

      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
      HAL_Delay(1000);
      
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
      
      
      
      
      
      Show_points(LeftPoints, RightPoints);
      HAL_Delay(1000);
      
      if(LeftPoints == 4 | RightPoints == 4) // 1111, 4 pts
      {
        NextState= GameOver;
        break;
      }
      NextState= Start;
      break;
      
      case GameOver:
        {
          LeftPoints = 0;
          RightPoints = 0;
          NextState= Start;
        }
      break;
 
 default:
 break;
 }

 }



  /* USER CODE END 3 */
}




/* USER CODE BEGIN 4 */

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
