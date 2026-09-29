//
// Created by luks on 29.09.26.
//

#ifndef NUCLEOINSTRUMENT_SCPI_TASK_H
#define NUCLEOINSTRUMENT_SCPI_TASK_H
#include "cmsis_os2.h"

osStatus_t ParserTaskInit(void);
osStatus_t ParserTaskLoop(void);

#endif // NUCLEOINSTRUMENT_SCPI_TASK_H
