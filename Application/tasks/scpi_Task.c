//
// Created by luks on 29.09.26.
//

#include "scpi_Task.h"

#include "cmsis_os2.h"
#include "osDefinitions.h"
#include "scpi-def.h"
#include "scpi/scpi.h"

#include <stdio.h>

char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];

static COMEvent_t rxMsg;

osStatus_t ParserTaskInit(void) {
  SCPI_Init(
      &scpi_context,
      scpi_commands,
      &scpi_interface,
      scpi_units_def,
      SCPI_IDN1,
      SCPI_IDN2,
      SCPI_IDN3,
      SCPI_IDN4,
      scpi_input_buffer,
      SCPI_INPUT_BUFFER_LENGTH,
      scpi_error_queue_data,
      SCPI_ERROR_QUEUE_SIZE);
  return osOK;
}

osStatus_t ParserTaskLoop(void) {

  osMessageQueueGet(COMRxQueueHandle, &rxMsg, 0, osWaitForever);
  volatile scpi_bool_t result =
      SCPI_Parse(&scpi_context, rxMsg.payload, (int)rxMsg.length);
  if (result == 0) {
    return osError;
  }
  // osDelay(1);
  return osOK;
}

size_t SCPI_Write(scpi_t *scpi, const char *data, size_t len) {
  (void)scpi;
  const COMEvent_t message = {
      .type = COM_TX_MESSAGE, .payload = {*data}, .length = len};
  return osMessageQueuePut(COMEventQueueHandle, &message, 0, osWaitForever);
}

scpi_result_t SCPI_Flush(scpi_t *context) {
  (void)context;

  return SCPI_RES_OK;
}

int SCPI_Error(scpi_t *context, int_fast16_t err) {
  (void)context;

  fprintf(
      stderr,
      "**ERROR: %d, \"%s\"\r\n",
      (int16_t)err,
      SCPI_ErrorTranslate(err));
  return 0;
}

scpi_result_t
SCPI_Control(scpi_t *context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
  (void)context;

  if (SCPI_CTRL_SRQ == ctrl) {
    fprintf(stderr, "**SRQ: 0x%X (%d)\r\n", val, val);
  } else {
    fprintf(stderr, "**CTRL %02x: 0x%X (%d)\r\n", ctrl, val, val);
  }
  return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t *context) {
  (void)context;

  fprintf(stderr, "**Reset\r\n");
  return SCPI_RES_OK;
}

scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t *context) {
  (void)context;

  return SCPI_RES_ERR;
}