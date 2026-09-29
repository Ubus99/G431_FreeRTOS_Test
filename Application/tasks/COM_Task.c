//
// Created by luks on 29.09.26.
//

#include "COM_Task.h"
#include "osDefinitions.h"
#include "usart.h"

static COMEvent_t event;

// Hardware Rx Buffer
static COMEvent_t hardwareEvent = {.type = COM_RX_COMPLETE};

osStatus_t COMTaskInit(void) {
  // kick off UART loop
  if (HAL_UARTEx_ReceiveToIdle_IT(
          &hlpuart1,
          (uint8_t *)hardwareEvent.payload,
          COM_EVENT_PAYLOAD_MAX_LENGTH) != HAL_OK)
    return osError;
  return osOK;
}

osStatus_t COMTaskLoop(void) {
  osMessageQueueGet(COMEventQueueHandle, &event, 0, osWaitForever);
  switch (event.type) {
  case COM_RX_COMPLETE:
    // act as gateway or watchdog
    event.type = COM_RX_MESSAGE;
    osMessageQueuePut(COMRxQueueHandle, &event, 0, osWaitForever);
    break;

  case COM_TX_MESSAGE:
    HAL_UART_Transmit(
        &hlpuart1, (uint8_t *)event.payload, event.length, HAL_MAX_DELAY);
    break;

  default:
    break;
  }

  //osDelay(1);
  return osOK;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
  hardwareEvent.length = size;
  osMessageQueuePut(
      COMEventQueueHandle,
      &hardwareEvent,
      0,
      0); // pass raw message to IO task for processing, it will
  // pass them on appropriately
  HAL_UARTEx_ReceiveToIdle_IT(
      &hlpuart1,
      (uint8_t *)hardwareEvent.payload,
      COM_EVENT_PAYLOAD_MAX_LENGTH); // rearm UART
}