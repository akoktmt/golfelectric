/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpshandle.h"
#include <stdio.h>
#include "GPS_StateMachine.h"
#include "CAN_Handle.h"
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

uint16_t oldPos = 0;
uint16_t newPos = 0;
uint8_t RxBuffer[RxBuffer_SIZE];
uint8_t DataBuffer[DataBuffer_SIZE];

GPS myData;
uint8_t Signalready=0;
uint8_t IsValid=0;
GPS_State gpsstate;
ErrCounter ErrCnt;
uint8_t Data[8];
extern uint8_t Lat[4];
extern uint8_t Long[4];
extern uint8_t Can_RecFlag;
//GPS_State currentstate;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART2){
    oldPos = newPos; //keep track of the last position in the buffer
    if(oldPos + Size > DataBuffer_SIZE){ //if the buffer is full, parse it, then reset the buffer

        uint16_t datatocopy = DataBuffer_SIZE-oldPos;  // find out how much space is left in the main buffer
        memcpy ((uint8_t *)DataBuffer+oldPos, RxBuffer, datatocopy);  // copy data in that remaining space

        oldPos = 0;  // point to the start of the buffer
        memcpy ((uint8_t *)DataBuffer, (uint8_t *)RxBuffer+datatocopy, (Size-datatocopy));  // copy the remaining data
        newPos = (Size-datatocopy);  // update the position
    }
    else{
        memcpy((uint8_t *)DataBuffer+oldPos, RxBuffer, Size); //copy received data to the buffer
        newPos = Size+oldPos; //update buffer position

    }
    HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *)RxBuffer, RxBuffer_SIZE); //re-enable the DMA interrupt
    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT); //disable the half transfer interrupt
    Signalready=1;
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */
  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *)RxBuffer, RxBuffer_SIZE);
  __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
  CAN_Config_filtering(0,0x502);
  // int Serialcnt = 0;
   gpsstate=GPS_INIT;
   if(HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY|CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK){

	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
	   					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
	   					HAL_Delay(2000);
  	 HAL_CAN_ResetError(&hcan);
  	NVIC_SystemReset();
   }
    if(HAL_CAN_Start(&hcan)!=HAL_OK){
    	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
    		   					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
    		   					HAL_Delay(2000);
  	  HAL_CAN_ResetError(&hcan);
  	  NVIC_SystemReset();
   } else {
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,GPIO_PIN_RESET);
	   gpsstate=GPS_WAIT_SIGNAL;
   }
    memset(Data,0x55,8);
    memset(Lat,0,4);
    memset(Long,0,4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	     switch(gpsstate){
	     case GPS_WAIT_SIGNAL:
	    	 gps_wait_signal();
	    	 break;
	     case GPS_GETDATA:
	    	 gps_getdata();
	     	    	 break;
	     case GPS_CHECK_SIGNAL:
	    	 gps_check_signal();
	     	    	 break;
	     case GPS_SENDDATA:
	    	 gps_send_data();
	     	    	 break;
	     case GPS_SENDERRORDATA:
	    	 send_error_signal();
	    	     	 break;
	     case GPS_RECOVERY:
	    	 gps_recovery();
	     	    	 break;
	     case GPS_PROCESS:
	    	 gps_process();
	     	    	 break;
//	  if(CAN_HandleSendData(0x402,Data,8)==HAL_OK){
//	  		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_RESET);
//	  			gpsstate=GPS_GETDATA;
//	  		}
//	  if(Can_RecFlag==1){
//		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
//	  }
//	     case SEND_ERROR_SIGNAL:
//	     	     	 break;
	     HAL_Delay(10);
	     }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
