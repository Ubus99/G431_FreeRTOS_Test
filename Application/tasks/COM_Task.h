//
// Created by luks on 29.09.26.
//

#ifndef NUCLEOINSTRUMENT_COM_TASK_H
#define NUCLEOINSTRUMENT_COM_TASK_H
#include "cmsis_os2.h"

osStatus_t COMTaskInit(void);
osStatus_t COMTaskLoop(void);

#endif // NUCLEOINSTRUMENT_COM_TASK_H
