//
// Created by luks on 29.09.26.
//

#ifndef NUCLEOINSTRUMENT_OSDEFINITIONS_H
#define NUCLEOINSTRUMENT_OSDEFINITIONS_H

#include "cmsis_os2.h"

#define COM_EVENT_PAYLOAD_MAX_LENGTH 32

typedef enum {
  COM_RX_COMPLETE = 0,
  COM_RX_MESSAGE,
  COM_TX_MESSAGE
} COMEventType_t;

typedef struct {
  COMEventType_t type;
  char           payload[COM_EVENT_PAYLOAD_MAX_LENGTH];
  size_t         length;
} COMEvent_t;

extern osMessageQueueId_t COMRxQueueHandle;
extern osMessageQueueId_t COMEventQueueHandle;

extern osThreadId_t COMTaskHandle;
extern osThreadId_t ParserTaskHandle;

#endif // NUCLEOINSTRUMENT_OSDEFINITIONS_H
