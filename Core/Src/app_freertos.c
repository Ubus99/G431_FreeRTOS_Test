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
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
  char payload[256];
} COMMessage_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define COM_RX_COMPLETE (1 << 0)
#define COM_TX_COMPLETE (1 << 1)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for COMTask */
osThreadId_t         COMTaskHandle;
const osThreadAttr_t COMTask_attributes = {
    .name       = "COMTask",
    .priority   = (osPriority_t)osPriorityAboveNormal,
    .stack_size = 128 * 4};
/* Definitions for COMRxQueue */
osMessageQueueId_t         COMRxQueueHandle;
const osMessageQueueAttr_t COMRxQueue_attributes = {.name = "COMRxQueue"};
/* Definitions for COMTxQueue */
osMessageQueueId_t         COMTxQueueHandle;
const osMessageQueueAttr_t COMTxQueue_attributes = {.name = "COMTxQueue"};
/* Definitions for COM_Events */
osEventFlagsId_t         COM_EventsHandle;
const osEventFlagsAttr_t COM_Events_attributes = {.name = "COM_Events"};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartCOMTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

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
  COMRxQueueHandle =
      osMessageQueueNew(16, sizeof(COMMessage_t), &COMRxQueue_attributes);

  /* creation of COMTxQueue */
  COMTxQueueHandle =
      osMessageQueueNew(16, sizeof(COMMessage_t), &COMTxQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of COMTask */
  COMTaskHandle = osThreadNew(StartCOMTask, NULL, &COMTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of COM_Events */
  COM_EventsHandle = osEventFlagsNew(&COM_Events_attributes);

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
void StartCOMTask(void *argument) {
  /* USER CODE BEGIN StartCOMTask */
  /* Infinite loop */
  for (;;) {
    uint32_t flags = osEventFlagsWait(
        COM_EventsHandle,
        COM_RX_COMPLETE | COM_TX_COMPLETE,
        osFlagsWaitAny,
        osWaitForever);

    if (flags & COM_RX_COMPLETE) {
      COMMessage_t rxMsg;

      HAL_UARTEx_ReceiveToIdle_IT(
          &hcom_uart[COM1], (uint8_t *)rxMsg.payload, sizeof(rxMsg.payload));
      osMessageQueuePut(COMRxQueueHandle, &rxMsg, 0, osWaitForever);
    }

    if (flags & COM_TX_COMPLETE) {
      COMMessage_t txMsg;

      osMessageQueueGet(COMRxQueueHandle, &txMsg, 0, osWaitForever);
      HAL_UART_Transmit_IT(
          &hcom_uart[COM1], (uint8_t *)txMsg.payload, sizeof(txMsg.payload));
    }

    osDelay(1);
  }
  /* USER CODE END StartCOMTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
