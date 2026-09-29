/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "COM_Task.h"
#include "osDefinitions.h"
#include "scpi_Task.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for COMTask */
osThreadId_t COMTaskHandle;
const osThreadAttr_t COMTask_attributes = {
  .name = "COMTask",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};
/* Definitions for ParserTask */
osThreadId_t ParserTaskHandle;
const osThreadAttr_t ParserTask_attributes = {
  .name = "ParserTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 350 * 4
};
/* Definitions for COMRxQueue */
osMessageQueueId_t COMRxQueueHandle;
const osMessageQueueAttr_t COMRxQueue_attributes = {
  .name = "COMRxQueue"
};
/* Definitions for COMEventQueue */
osMessageQueueId_t COMEventQueueHandle;
const osMessageQueueAttr_t COMEventQueue_attributes = {
  .name = "COMEventQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartCOMTask(void *argument);
void StartParserTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void) {}

__weak unsigned long getRunTimeCounterValue(void) { return 0; }
/* USER CODE END 1 */

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName) {
  /* Run time stack overflow checking is performed if
  configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
  called if a stack overflow is detected. */
}

/* USER CODE END 4 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of COMRxQueue */
  COMRxQueueHandle = osMessageQueueNew (16, sizeof(COMEvent_t), &COMRxQueue_attributes);

  /* creation of COMEventQueue */
  COMEventQueueHandle = osMessageQueueNew (16, sizeof(COMEvent_t), &COMEventQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of COMTask */
  COMTaskHandle = osThreadNew(StartCOMTask, NULL, &COMTask_attributes);

  /* creation of ParserTask */
  ParserTaskHandle = osThreadNew(StartParserTask, NULL, &ParserTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartCOMTask */
/**
 * @brief  Function implementing the COMTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartCOMTask */
void StartCOMTask(void *argument)
{
  /* USER CODE BEGIN StartCOMTask */
  COMTaskInit();

  /* Infinite loop */
  for (;;) {
    COMTaskLoop();
  }
  /* USER CODE END StartCOMTask */
}

/* USER CODE BEGIN Header_StartParserTask */
/**
 * @brief Function implementing the ParserTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartParserTask */
void StartParserTask(void *argument)
{
  /* USER CODE BEGIN StartParserTask */
  ParserTaskInit();
  /* Infinite loop */
  for (;;) {
    ParserTaskLoop();
  }
  /* USER CODE END StartParserTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

